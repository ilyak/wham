//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include <config.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "common.h"

///
int bin_count = 100;

///
int sim_count;

///
int max_iter = 200;

///
int print_step = 10;

///
bool verbose = false;

///
const char *input;

///
double beta;

///
double hist_min;

///
double hist_max;

///
double tol = 1.0e-6;

///
double period;


static void
message_version()
{
	puts(PACKAGE_NAME " version " PACKAGE_VERSION);
	puts("Copyright (c) 2010 Ilya Kaliman");
	puts("See file COPYING for conditions of distribution and use");

	lib_exit(E_SUCCESS);
}


static void
message_help(bool long_help)
{
	puts("Usage: wham OPTIONS");

	if (long_help) {
		puts("more help");
	}

	lib_exit(E_SUCCESS);
}


extern void
parse_args(int argc, char **argv)
{
	static const char short_opts[] =
			"b:f:t:n:e:r:l:p:i:hHvV";

	static const struct option long_opts[] = {
		{ "beta",         required_argument,  NULL,  'b' },
		{ "min",          required_argument,  NULL,  'f' },
		{ "max",          required_argument,  NULL,  't' },
		{ "bins",         required_argument,  NULL,  'n' },
		{ "tol",          required_argument,  NULL,  'e' },
		{ "max-iter",     required_argument,  NULL,  'r' },
		{ "print-step",   required_argument,  NULL,  'l' },
		{ "period",       required_argument,  NULL,  'p' },
		{ "input",        required_argument,  NULL,  'i' },

		{ "help",         no_argument,        NULL,  'h' },
		{ "long-help",    no_argument,        NULL,  'H' },
		{ "verbose",      no_argument,        NULL,  'v' },
		{ "version",      no_argument,        NULL,  'V' },

		{ NULL,           0,                  NULL,   0  }
	};

	int c;

	while ((c = getopt_long(argc, argv, short_opts, long_opts, NULL))
			!= -1) {
		switch (c) {
		case 'b':
			beta = strtod(optarg, NULL);
			break;

		case 'f':
			hist_min = strtod(optarg, NULL);
			break;

		case 't':
			hist_max = strtod(optarg, NULL);
			break;

		case 'n':
			bin_count = strtoul(optarg, NULL, 0);
			break;

		case 'e':
			tol = strtod(optarg, NULL);
			break;

		case 'l':
			print_step = strtoul(optarg, NULL, 0);
			break;

		case 'r':
			max_iter = strtoul(optarg, NULL, 0);
			break;

		case 'p':
			period = strtod(optarg, NULL);
			break;

		case 'i':
			input = optarg;
			break;

		case 'v':
			verbose = true;
			break;

		case 'V':
			message_version();
			/* Does not return */

		case 'H':
			message_help(true);
			/* Does not return */

		case 'h':
			message_help(false);
			/* Does not return */

		default:
			lib_exit(E_ERROR);
		}
	}
}
