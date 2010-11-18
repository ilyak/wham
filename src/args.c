//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include <getopt.h>
#include <stdlib.h>
#include "args.h"
#include "common.h"
#include "message.h"
#include "pmf.h"

extern void
parse_args(int argc, char **argv)
{
	static const char short_opts[] =
			"b:m:M:n:e:I:s:p:i:qhHvV";

	static const struct option long_opts[] = {
		{ "beta",         required_argument,  NULL,  'b' },
		{ "min",          required_argument,  NULL,  'm' },
		{ "max",          required_argument,  NULL,  'M' },
		{ "bins",         required_argument,  NULL,  'n' },
		{ "tol",          required_argument,  NULL,  'e' },
		{ "max-iter",     required_argument,  NULL,  'I' },
		{ "print-step",   required_argument,  NULL,  's' },
		{ "period",       required_argument,  NULL,  'p' },
		{ "input",        required_argument,  NULL,  'i' },

		{ "quiet",        no_argument,        NULL,  'q' },
		{ "usage",        no_argument,        NULL,  'h' },
		{ "help",         no_argument,        NULL,  'H' },
		{ "verbose",      no_argument,        NULL,  'v' },
		{ "version",      no_argument,        NULL,  'V' },

		{  NULL,          0,                  NULL,   0  }
	};

	int c;

	while ((c = getopt_long(argc, argv, short_opts, long_opts, NULL))
			!= -1) {
		switch (c) {
		case 'b':
			set_beta(strtod(optarg, NULL));
			break;

		case 'm':
			set_hist_min(strtod(optarg, NULL));
			break;

		case 'M':
			set_hist_max(strtod(optarg, NULL));
			break;

		case 'n':
			set_bin_count(strtoul(optarg, NULL, 0));
			break;

		case 'e':
			set_tolerance(strtod(optarg, NULL));
			break;

		case 's':
			set_print_step(strtoul(optarg, NULL, 0));
			break;

		case 'I':
			set_max_iter(strtoul(optarg, NULL, 0));
			break;

		case 'p':
			set_period(strtod(optarg, NULL));
			break;

		case 'i':
			set_input_filename(optarg);
			break;

		case 'q':
			message_verbosity_decrease();
			break;

		case 'v':
			message_verbosity_increase();
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
