//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#include "common.h"
#include "message.h"

void *xmalloc(size_t size)
{
	void *ptr;

	if (size == 0)
		message_fatal("Unsupported request for zero byte allocation");
	if ((ptr = malloc(size)) == NULL)
		message_fatal("Unable to allocate memory");
	return ptr;
}
