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

extern void
message_verbosity_increase(void)
{
	if (verbosity < V_VERBOSE)
		verbosity++;
}

extern void
message_verbosity_decrease(void)
{
	if (verbosity > V_SILENT)
		verbosity--;
}

extern void
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

extern void
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
	puts("Usage: wham OPTIONS");
}

extern void
message_help(bool long_help)
{
	if (long_help)
		message_long_help();
	else
		message_short_help();

	lib_exit(E_SUCCESS);
}

extern void
message_fatal(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	putc('\n', stderr);
	va_end(ap);

	lib_exit(E_ERROR);
}
