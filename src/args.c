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
			"b:f:t:n:e:r:l:p:i:qhHvV";

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

		{ "quiet",        no_argument,        NULL,  'q' },
		{ "help",         no_argument,        NULL,  'h' },
		{ "long-help",    no_argument,        NULL,  'H' },
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

		case 'f':
			set_hist_min(strtod(optarg, NULL));
			break;

		case 't':
			set_hist_max(strtod(optarg, NULL));
			break;

		case 'n':
			set_bin_count(strtoul(optarg, NULL, 0));
			break;

		case 'e':
			set_tolerance(strtod(optarg, NULL));
			break;

		case 'l':
			set_print_step(strtoul(optarg, NULL, 0));
			break;

		case 'r':
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
