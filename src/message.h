//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_MESSAGE_H
#define WHAM_MESSAGE_H

#include <stdbool.h>
#include "common.h"

/// Message verbosity level
enum message_verbosity_t {
	V_SILENT,
	V_NORMAL,
	V_VERBOSE
};

/// Increases verbosity level
extern void message_verbosity_increase(void);

/// Decreases verbosity level
extern void message_verbosity_decrease(void);

/// Prints help message
extern void message_help(bool long_help) lib_attr_noreturn;

/// Prints version info
extern void message_version(void) lib_attr_noreturn;

/// Prints a message taking into account current verbosity level
extern void message(enum message_verbosity_t ver, const char *format, ...);

/// Prints a message and terminates the program with an error
extern void message_fatal(const char *format, ...) lib_attr_noreturn;

#endif /* WHAM_MESSAGE_H */
