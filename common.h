//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_COMMON_H
#define WHAM_COMMON_H

#include <stdlib.h>

/// Exit status
enum exit_status_t {
	E_SUCCESS = 0,
	E_ERROR   = 1,
};

/// Safe malloc
void *xmalloc(size_t size);

#endif /* WHAM_COMMON_H */
