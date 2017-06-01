//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include "args.h"
#include "common.h"
#include "pmf.h"

int main(int argc, char **argv)
{
	parse_args(argc, argv);
	read_input();
	compute_pmf();
	cleanup();
	return 0;
}
