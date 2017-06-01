//
// Copyright (c) 2010 Ilya Kaliman
//
// This code is released under the GNU General Public License.
// See file COPYING for conditions of distribution and use.
//

#ifndef WHAM_MESSAGE_H
#define WHAM_MESSAGE_H

#include "common.h"

/// Message verbosity level
enum message_verbosity_t {
	V_SILENT  = 0,
	V_NORMAL  = 1,
	V_VERBOSE = 2,
};

/// Increases verbosity level
void message_verbosity_increase(void);

/// Decreases verbosity level
void message_verbosity_decrease(void);

/// Prints help message
void message_help(int long_help);

/// Prints version info
void message_version(void);

/// Prints a message taking into account current verbosity level
void message(enum message_verbosity_t ver, const char *format, ...);

/// Prints a message and terminates the program with an error
void message_fatal(const char *format, ...);

#endif /* WHAM_MESSAGE_H */
