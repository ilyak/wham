//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"


extern void
lib_exit(enum exit_status_t status)
{
	exit(status);
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
