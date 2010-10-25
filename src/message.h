//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_MESSAGE_H
#define WHAM_MESSAGE_H

#include <stdbool.h>

/// Message verbosity level
enum message_verbosity_t {
	V_SILENT,
	V_NORMAL,
	V_VERBOSE
};

/// Increases verbosity level
extern void message_verbosity_increase();

/// Decreases verbosity level
extern void message_verbosity_decrease();

/// Prints help message
extern void message_help(bool long_help);

/// Prints version info
extern void message_version();

/// Prints a message taking into account current verbosity level
extern void message(enum message_verbosity_t ver, const char *format, ...);

/// Prints a message and terminates the program with an error
extern void message_fatal(const char *format, ...);

#endif /* WHAM_MESSAGE_H */
