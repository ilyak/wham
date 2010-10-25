//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include <stdio.h>
#include "args.h"
#include "common.h"
#include "pmf.h"


int
main(int argc, char **argv)
{
	parse_args(argc, argv);

	double pmf[bin_count];

	read_input();
	compute_pmf(pmf);

	puts("Printing PMF...\n");

	for (int i = 0; i < bin_count; i++)
		printf("%12.6lf %12.6lf\n", hist_x(i), pmf[i]);

	puts("\nComputation completed.");

	cleanup();
	lib_exit(E_SUCCESS);
}
