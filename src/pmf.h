//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_PMF_H
#define WHAM_PMF_H

/// Sets number of bins
extern void set_bin_count(int value);

/// Sets print step
extern void set_print_step(int value);

/// Sets maximum number of iterations to perform
extern void set_max_iter(int value);

/// Sets input file name
extern void set_input_filename(const char *value);

/// Sets the value of beta
extern void set_beta(double value);

/// Sets minimum coordinate value for the histogram
extern void set_hist_min(double value);

/// Sets maximum coordinate value for the histogram
extern void set_hist_max(double value);

/// Sets accuracy for the PMF computation
extern void set_tolerance(double value);

/// Sets period for periodic coordinates
extern void set_period(double value);

/// Reads input data
extern void read_input();

/// Performs PMF computation
extern void compute_pmf();

/// Deallocates used memory
extern void cleanup();

#endif /* WHAM_PMF_H */
