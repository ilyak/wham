//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include "common.h"
#include "message.h"

void *
xalloc(size_t size)
{
	if (size == 0)
		message_fatal("Unsupported request for zero byte allocation");

	void *ptr = malloc(size);

	if (ptr == NULL)
		message_fatal("Unable to allocate memory");

	return ptr;
}

void
lib_exit(enum exit_status_t status)
{
	exit(status);
}
