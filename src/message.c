//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include <stdarg.h>
#include <stdio.h>
#include <config.h>
#include "message.h"

/// Verbosity level
static enum message_verbosity_t verbosity = V_NORMAL;

void
message_verbosity_increase(void)
{
	if (verbosity < V_VERBOSE)
		verbosity++;
}

void
message_verbosity_decrease(void)
{
	if (verbosity > V_SILENT)
		verbosity--;
}

void
message(enum message_verbosity_t ver, const char *format, ...)
{
	if (ver > verbosity)
		return;

	va_list ap;

	va_start(ap, format);
	vprintf(format, ap);
	putchar('\n');
	va_end(ap);
}

void
message_version(void)
{
	puts(PACKAGE_NAME " version " PACKAGE_VERSION);
	puts("Copyright (c) 2010 Ilya Kaliman");
	puts("See file COPYING for conditions of distribution and use");

	lib_exit(E_SUCCESS);
}

static void
message_short_help(void)
{
	puts("Usage: wham -b beta -m min -M max -n bins -e tol -I iter");
	puts("            -s step -p period -i input -qhHvV");
}

static void
message_long_help(void)
{
	puts(
"Usage: wham [OPTION]\n"
"\n"
"  Input source:\n"
"\n"
"    -i, --input=FILE       Name of the input file. Input is read from\n"
"                           standard input if you do not specify input file.\n"
"\n"
"  Main control options:\n"
"\n"
"    -b, --beta=BETA        1 / (k * T), where k is Boltzmann constant and T\n"
"                           is temperature. Energy units used here will be\n"
"                           used for final PMF.\n"
"    -m, --min=MIN          Lower bound of histogram.\n"
"    -M, --max=MAX          Upper bound of histogram.\n"
"    -p, --period=PERIOD    Period for periodic coordinates.\n"
"    -n, --bins=BINS        Number of bins in final PMF.\n"
"    -e, --tol=TOL          Convergence tolerance.\n"
"    -s, --print-step=STEP  Current progress will be printed every STEP\n"
"                           iterations.\n"
"    -I, --max-iter=ITER    Maximum number of iterations to perform.\n"
"\n"
"  Other options:\n"
"\n"
"    -q, --quiet            Print only final PMF.\n"
"    -v, --verbose          Print all messages.\n"
"    -h, --help             Show help.\n"
"    -H, --long-help        Show this help message.\n"
"    -V, --version          Print program version.");
}

void
message_help(bool long_help)
{
	if (long_help)
		message_long_help();
	else
		message_short_help();

	lib_exit(E_SUCCESS);
}

void
message_fatal(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	putc('\n', stderr);
	va_end(ap);

	lib_exit(E_ERROR);
}
