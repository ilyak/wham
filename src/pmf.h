//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_PMF_H
#define WHAM_PMF_H

///
extern void read_input();

///
extern void compute_pmf(double *pmf);

///
extern double hist_x(int i);

///
extern void cleanup();

#endif /* WHAM_PMF_H */
