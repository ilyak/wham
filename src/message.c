//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include <stdarg.h>
#include <stdio.h>
#include <config.h>
#include "common.h"
#include "message.h"

/// Verbosity level
static enum message_verbosity_t verbosity = V_NORMAL;

extern void
message_verbosity_increase()
{
	if (verbosity < V_VERBOSE)
		verbosity++;
}

extern void
message_verbosity_decrease()
{
	if (verbosity > V_SILENT)
		verbosity--;
}

extern void
message_version()
{
	puts(PACKAGE_NAME " version " PACKAGE_VERSION);
	puts("Copyright (c) 2010 Ilya Kaliman");
	puts("See file COPYING for conditions of distribution and use");

	lib_exit(E_SUCCESS);
}

extern void
message_help(bool long_help)
{
	puts("Usage: wham OPTIONS");

	if (long_help) {
		puts("more help");
	}

	lib_exit(E_SUCCESS);
}

extern void
message_fatal(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);

	lib_exit(E_ERROR);
}
