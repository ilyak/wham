//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "common.h"
#include "message.h"
#include "pmf.h"

/// Maximum number of iterations
static int max_iter = 200;

/// Print info every n iterations
static int print_step = 10;

/// Input file name
static const char *input;

/// Computation tolerance
static double tol = 1.0e-6;

/// Coordinate period
static double period;

/// Number of bins in histogram
static int bin_count = 100;

/// Number of simulations from input file
static int sim_count;

/// Beta = k * T, where k - Boltzman constant, T - temperature
/// Default value is in kcal/mol at 300K
static double beta;

/// Lower histogram limit
static double hist_min;

/// Upper histogram limit
static double hist_max;

/// Array of biasing potential x0 points
static double *bias_x;

/// Array of biasing potential constants
static double *bias_k;

/// Log of number of points in bin
static double *log_nbin;

/// Log of number of points in simulation
static double *log_nsim;

extern void
set_bin_count(int value)
{
	bin_count = value;
}

extern void
set_print_step(int value)
{
	print_step = value;
}

extern void
set_max_iter(int value)
{
	max_iter = value;
}

extern void
set_input_filename(const char *value)
{
	input = value;
}

extern void
set_beta(double value)
{
	if (value < 0.0)
		message_fatal("Beta value must be positive");

	beta = value;
}

extern void
set_hist_min(double value)
{
	if (value > hist_max)
		message_fatal("Histogram minimum must be less than maximum");

	hist_min = value;
}

extern void
set_hist_max(double value)
{
	if (value < hist_min)
		message_fatal("Histogram minimum must be less than maximum");

	hist_max = value;
}

extern void
set_tolerance(double value)
{
	if (value < 0.0)
		message_fatal("Tolerance must be positive");

	tol = value;
}

extern void
set_period(double value)
{
	if (value < 0.0)
		message_fatal("Period must be positive");

	period = value;
}

static double
hist_x(int i)
{
	return hist_min + (hist_max - hist_min) / bin_count * (0.5 + i);
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

extern void
compute_pmf(void)
{
	double f[sim_count], old_f[sim_count], log_r[bin_count];

	for (int i = 0; i < sim_count; i++)
		f[i] = 0.0;

	int iter;

	for (iter = 0; iter < max_iter; iter++) {
		for (int i = 0; i < sim_count; i++)
			old_f[i] = f[i];

		pmf_iteration(f, log_r);

		double f0 = f[0];

		for (int i = 0; i < sim_count; i++)
			f[i] -= f0;

		double delta = 0.0;

		for (int i = 0; i < sim_count; i++) {
			double df = fabs(f[i] - old_f[i]);
			if (df > delta)
				delta = df;
		}

		if (delta < tol)
			break;

		if (iter % print_step == 0)
			printf("Iteration %d, delta is %.8E\n", iter, delta);
	}

	static const char msg1[] = "Procedure converged";
	static const char msg2[] = "Procedure didn't converge";

	puts(iter < max_iter ? msg1 : msg2);

	double pmf[bin_count];

	for (int i = 0; i < bin_count; i++)
		pmf[i] = -log_r[i] / beta;

	double min = find_min(pmf, bin_count);

	for (int i = 0; i < bin_count; i++)
		pmf[i] -= min;

	puts("Printing PMF...\n");

	for (int i = 0; i < bin_count; i++)
		printf("%12.6lf %12.6lf\n", hist_x(i), pmf[i]);

	puts("\nComputation completed.");
}

extern void
read_input(void)
{
	FILE *in = input ? fopen(input, "r") : stdin;

	if (in == NULL)
		message_fatal("Unable to open input file\n");

	if (fscanf(in, "%d", &sim_count) != 1)
		message_fatal("Unable to read number of simulations\n");

	size_t size_sim = sizeof(double) * sim_count;
	size_t size_bin = sizeof(double) * bin_count;

	bias_x = malloc(size_sim);
	bias_k = malloc(size_sim);
	log_nbin = malloc(size_bin);
	log_nsim = malloc(size_sim);

	int nbin[bin_count], nsim[sim_count];

	for (int i = 0; i < sim_count; i++) {
		int npt;
		double x;

		if (fscanf(in, "%lf %lf", &bias_x[i], &bias_k[i]) != 2)
			message_fatal("Error reading bias info\n");

		if (fscanf(in, "%d", &npt) != 1)
			message_fatal("");

		for (int j = 0; j < npt; j++) {
			if (fscanf(in, "%lf", &x) != 1)
				message_fatal("");

			if (x > hist_min && x < hist_max) {
				nbin[bin_index(x)]++;
				nsim[i]++;
			}
		}

		printf("%d of total %d points in sim %d, x = %lf, k = %lf\n",
			nsim[i], npt, i + 1, bias_x[i], bias_k[i]);
	}

	for (int i = 0; i < bin_count; i++)
		log_nbin[i] = log(nbin[i]);

	for (int i = 0; i < sim_count; i++)
		log_nsim[i] = log(nsim[i]);

	if (in != stdin)
		fclose(in);
}

extern void
cleanup(void)
{
	free(bias_x);
	free(bias_k);
	free(log_nsim);
	free(log_nbin);
}
