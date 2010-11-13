//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include "args.h"
#include "common.h"
#include "message.h"
#include "pmf.h"

/// Maximum number of iterations
static int max_iter = 400;

/// Print info every n iterations
static int print_step = 20;

/// Input file name
static const char *input;

/// Convergence tolerance
static double tol = 1.0e-5;

/// Coordinate period
static double period;

/// Number of bins in histogram
static int bin_count = 50;

/// Number of simulations from input file
static int sim_count;

/// Beta = 1 / (k * T), where k - Boltzmann constant, T - temperature
/// Default value is in 1 / (kcal/mol) for 300K
static double beta = 1.6773963842;

/// Lower histogram limit
static double hist_min = 0.0;

/// Upper histogram limit
static double hist_max = 1.0;

/// Array of biasing potential x0 points
static double *bias_x;

/// Array of biasing potential constants
static double *bias_k;

/// Log of number of points in bin
static double *log_nbin;

/// Log of number of points in simulation
static double *log_nsim;

void
set_bin_count(int value)
{
	bin_count = value;
}

void
set_print_step(int value)
{
	print_step = value;
}

void
set_max_iter(int value)
{
	max_iter = value;
}

void
set_input_filename(const char *value)
{
	input = value;
}

void
set_beta(double value)
{
	if (value < 0.0)
		message_fatal("Beta must be positive");

	beta = value;
}

void
set_hist_min(double value)
{
	if (period > 0)
		message_fatal("Incompatible options -m and -p");

	if (value > hist_max)
		message_fatal("Histogram minimum must be less than maximum");

	hist_min = value;
}

void
set_hist_max(double value)
{
	if (period > 0)
		message_fatal("Incompatible options -M and -p");

	if (value < hist_min)
		message_fatal("Histogram minimum must be less than maximum");

	hist_max = value;
}

void
set_tolerance(double value)
{
	if (value < 0.0)
		message_fatal("Tolerance must be positive");

	tol = value;
}

void
set_period(double value)
{
	if (value < 0.0)
		message_fatal("Period must be positive");

	period = value;
	hist_min = 0.0;
	hist_max = period;
}

static double
hist_x(int i)
{
	return hist_min + (hist_max - hist_min) / bin_count * i;
}

static int
bin_index(double x)
{
	return (int)((x - hist_min) / (hist_max - hist_min) * bin_count);
}

static double
find_min(const double *v, int n)
{
	double rv = *v++;

	for (int i = 1; i < n; i++, v++)
		if (*v < rv)
			rv = *v;

	return rv;
}

static double
find_max(const double *v, int n)
{
	double rv = *v++;

	for (int i = 1; i < n; i++, v++)
		if (*v > rv)
			rv = *v;

	return rv;
}

static double
log_sum(const double *v, int n)
{
	double sum = 0.0;
	double max = find_max(v, n);

	for (int i = 0; i < n; i++, v++)
		sum += exp(*v - max);

	return log(sum) + max;
}

static void
pmf_iteration(double *f, double *log_r)
{
	double work_sims[sim_count], work_bins[bin_count];

	for (int i = 0; i < bin_count; i++) {
		for (int j = 0; j < sim_count; j++) {
			double bias, dx;

			if (period > 0) {
				dx = fabs(hist_x(i) - bias_x[j]);

				while (dx > 0.5 * period)
					dx -= period;

				bias = 0.5 * bias_k[j] * dx * dx;
			}
			else {
				dx = hist_x(i) - bias_x[j];
				bias = 0.5 * bias_k[j] * dx * dx;
			}

			work_sims[j] = log_nsim[j] + f[j] - beta * bias;
		}

		double log_den = log_sum(work_sims, sim_count);
		log_r[i] = log_nbin[i] - log_den;
	}

	for (int j = 0; j < sim_count; j++) {
		for (int i = 0; i < bin_count; i++) {
			double bias, dx;

			if (period > 0) {
				dx = fabs(hist_x(i) - bias_x[j]);

				while (dx > 0.5 * period)
					dx -= period;

				bias = 0.5 * bias_k[j] * dx * dx;
			}
			else {
				dx = hist_x(i) - bias_x[j];
				bias = 0.5 * bias_k[j] * dx * dx;
			}

			work_bins[i] = log_r[i] - beta * bias;
		}

		f[j] = -log_sum(work_bins, bin_count);
	}
}

void
compute_pmf(void)
{
	double f[sim_count], old_f[sim_count], log_r[bin_count];

	for (int i = 0; i < sim_count; i++)
		f[i] = 0.0;

	double delta = 0.0;

	for (int iter = 0; iter < max_iter; iter++) {
		for (int i = 0; i < sim_count; i++)
			old_f[i] = f[i];

		pmf_iteration(f, log_r);

		double f0 = f[0];

		for (int i = 0; i < sim_count; i++)
			f[i] -= f0;

		delta = 0.0;

		for (int i = 0; i < sim_count; i++) {
			double df = fabs(f[i] - old_f[i]);
			if (df > delta)
				delta = df;
		}

		if (delta < tol)
			break;

		if (iter % print_step == 0)
			message(V_VERBOSE, "Iteration %d, delta is %.8E",
					iter, delta);
	}

	static const char msg1[] = "Procedure converged";
	static const char msg2[] = "Procedure didn't converge";

	message(V_NORMAL, delta < tol ? msg1 : msg2);
	message(V_NORMAL, "Last delta is %.8E", delta);

	double pmf[bin_count];

	for (int i = 0; i < bin_count; i++)
		pmf[i] = -log_r[i] / beta;

	double min = find_min(pmf, bin_count);

	for (int i = 0; i < bin_count; i++)
		pmf[i] -= min;

	message(V_NORMAL, "Printing PMF...\n");
	message(V_NORMAL, "%9s %13s\n", "x", "pmf");

	for (int i = 0; i < bin_count; i++)
		message(V_SILENT, "%12.6lf %12.6lf", hist_x(i), pmf[i]);

	message(V_NORMAL, "\nComputation completed.");
}

/// Skips empty lines and lines starting with '#' symbol
static void
skip_comment(FILE *stream)
{
	int c;

	while ((c = fgetc(stream)) != EOF && (c == '#' || c == '\n'))
		while (c != '\n' && (c = fgetc(stream)) != EOF);

	ungetc(c, stream);
}

void
read_input(void)
{
	FILE *in = input ? fopen(input, "r") : stdin;

	if (in == NULL)
		message_fatal("Unable to open input file");

	skip_comment(in);

	if (fscanf(in, "%d", &sim_count) != 1)
		message_fatal("Unable to read number of simulations");

	if (sim_count <= 0)
		message_fatal("Expected positive number of simulations");

	size_t size_sim = sizeof(double) * sim_count;
	size_t size_bin = sizeof(double) * bin_count;

	bias_x = xalloc(size_sim);
	bias_k = xalloc(size_sim);
	log_nbin = xalloc(size_bin);
	log_nsim = xalloc(size_sim);

	int nbin[bin_count], nsim[sim_count];

	for (int i = 0; i < bin_count; i++)
		nbin[i] = 0;

	for (int i = 0; i < sim_count; i++) {
		int npt;
		double x;

		if (fscanf(in, "%lf %lf", &bias_x[i], &bias_k[i]) != 2)
			message_fatal("Error reading bias info");

		if (fscanf(in, "%d", &npt) != 1)
			message_fatal("Error reading point count");

		if (npt <= 0)
			message_fatal("Expected positive number of points");

		nsim[i] = 0;

		for (int j = 0; j < npt; j++) {
			if (fscanf(in, "%lf", &x) != 1)
				message_fatal("Error reading data points");

			if (period > 0) {
				if (x > 0)
					while (x > period)
						x -= period;
				else
					while (x < 0)
						x += period;
			}

			if (x > hist_min && x < hist_max) {
				nbin[bin_index(x)]++;
				nsim[i]++;
			}
		}

		message(V_VERBOSE, "Added %d of %d points from set %d",
					nsim[i], npt, i + 1);
	}

	for (int i = 0; i < bin_count; i++)
		log_nbin[i] = log(nbin[i]);

	for (int i = 0; i < sim_count; i++)
		log_nsim[i] = log(nsim[i]);

	if (in != stdin)
		fclose(in);
}

void
cleanup(void)
{
	free(bias_x);
	free(bias_k);
	free(log_nsim);
	free(log_nbin);
}
