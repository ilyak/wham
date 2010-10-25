//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_COMMON_H
#define WHAM_COMMON_H

///
enum exit_status_t {
	E_SUCCESS  = 0,
	E_ERROR    = 1,
	E_WARNING  = 2
};

///
extern void lib_exit(enum exit_status_t status);

///
extern void message_fatal(const char *format, ...);

#endif /* WHAM_COMMON_H */
