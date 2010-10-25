//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_PMF_H
#define WHAM_PMF_H

///
extern void set_bin_count(int value);

///
extern void set_print_step(int value);

///
extern void set_max_iter(int value);

///
extern void set_input_filename(const char *value);

///
extern void set_beta(double value);

///
extern void set_hist_min(double value);

///
extern void set_hist_max(double value);

///
extern void set_tolerance(double value);

///
extern void set_period(double value);

/// Reads input data
extern void read_input();

/// Performs PMF computation
extern void compute_pmf();

/// Deallocates used memory
extern void cleanup();

#endif /* WHAM_PMF_H */
