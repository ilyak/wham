//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_PMF_H
#define WHAM_PMF_H

/// Reads input data
extern void read_input();

/// Performs PMF computation
extern void compute_pmf(double *pmf);

///
extern void set_hist_min(double v);

///
extern void set_hist_max(double v);

/// Returns x value of the center of specified bin
extern double hist_x(int i);

/// Deallocates used memory
extern void cleanup();

#endif /* WHAM_PMF_H */
