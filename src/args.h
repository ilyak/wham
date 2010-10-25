//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_ARGS_H
#define WHAM_ARGS_H

#include <stdbool.h>

///
extern int bin_count;

///
extern int sim_count;

///
extern int max_iter;

///
extern int print_step;

///
extern bool verbose;

///
extern const char *input;

///
extern double beta;

///
extern double hist_min;

///
extern double hist_max;

///
extern double tol;

///
extern double period;

///
extern void parse_args(int argc, char **argv);

#endif /* WHAM_ARGS_H */
