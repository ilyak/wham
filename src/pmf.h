//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_PMF_H
#define WHAM_PMF_H

/// Sets number of bins
void set_bin_count(int value);

/// Sets print step
void set_print_step(int value);

/// Sets maximum number of iterations to perform
void set_max_iter(int value);

/// Sets input file name
void set_input_filename(const char *value);

/// Sets the value of beta
void set_beta(double value);

/// Sets minimum coordinate value for the histogram
void set_hist_min(double value);

/// Sets maximum coordinate value for the histogram
void set_hist_max(double value);

/// Sets accuracy for the PMF computation
void set_tolerance(double value);

/// Sets period for periodic coordinates
void set_period(double value);

/// Reads input data
void read_input(void);

/// Performs PMF computation
void compute_pmf(void);

/// Deallocates used memory
void cleanup(void);

#endif /* WHAM_PMF_H */
