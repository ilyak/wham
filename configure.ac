AC_PREREQ([2.64])
AC_COPYRIGHT([Copyright (c) 2010 Ilya Kaliman])
AC_INIT([wham], [2.0.0], [ilya.kaliman@gmail.com])
AC_CONFIG_SRCDIR([src/pmf.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11.1 dist-xz -Wall -Werror])

AC_LANG([C])
AC_PROG_CC
AC_PROG_CC_C99
if test "x$ac_cv_prog_cc_c99" = xno ; then
	AC_MSG_ERROR([No C99 compiler was found.])
fi
AC_PROG_CPP

DEVELOPER_CFLAGS="-Wall -Wextra -Wstrict-prototypes -Wmissing-prototypes \
-Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wshadow \
-Wcast-align -Wunused-parameter -Wchar-subscripts -Winline -Wnested-externs \
-Wredundant-decls -Wformat=2 -Winit-self -Wmissing-include-dirs \
-Wstrict-aliasing -Wfloat-equal -Wundef -Wbad-function-cast -Wlogical-op \
-Waggregate-return -Wold-style-definition -Wmissing-declarations \
-Wmissing-noreturn"

AC_ARG_ENABLE([developer-warnings],
	AS_HELP_STRING([--enable-developer-warnings],
		[enable strict warnings (default is NO)]),
	CFLAGS="${CFLAGS} ${DEVELOPER_CFLAGS}")

AC_ARG_ENABLE([werror],
	AS_HELP_STRING([--enable-werror], [use -Werror (default is NO)]),
	CFLAGS="${CFLAGS} -Werror")

AC_ARG_ENABLE([debugging-symbols],
	AS_HELP_STRING([--enable-debugging-symbols],
		[enable debugging symbols (default is NO)]),
	CFLAGS="${CFLAGS} -O0 -g -fno-inline")

AC_ARG_ENABLE([stack-protector],
	AS_HELP_STRING([--enable-stack-protector],
		[enable stack protector (default is NO)]),
	CFLAGS="${CFLAGS} -fstack-protector-all")

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT
