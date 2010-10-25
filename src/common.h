//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_COMMON_H
#define WHAM_COMMON_H

#define lib_attr_noreturn __attribute__((__noreturn__))

/// Exit status
enum exit_status_t {
	E_SUCCESS  = 0,
	E_ERROR    = 1,
	E_WARNING  = 2
};

/// Terminates the program by calling exit
extern void lib_exit(enum exit_status_t status) lib_attr_noreturn;

#endif /* WHAM_COMMON_H */
