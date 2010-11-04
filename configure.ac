AC_PREREQ([2.64])
AC_INIT([wham], [2.0], [ilya.kaliman@gmail.com])
AC_CONFIG_SRCDIR([src/pmf.c])
AM_INIT_AUTOMAKE([-Wall -Werror])

AC_LANG([C])
AC_PROG_CC
AC_PROG_CC_C99
if test "x$ac_cv_prog_cc_c99" = xno ; then
	AC_MSG_ERROR([No C99 compiler was found.])
fi

if test "$GCC" = yes ; then
	for NEW_FLAG in \
			-Wall \
			-Wextra \
			-Wformat=2 \
			-Winit-self \
			-Wmissing-include-dirs \
			-Wstrict-aliasing \
			-Wfloat-equal \
			-Wundef \
			-Wshadow \
			-Wpointer-arith \
			-Wbad-function-cast \
			-Wwrite-strings \
			-Wlogical-op \
			-Waggregate-return \
			-Wstrict-prototypes \
			-Wold-style-definition \
			-Wmissing-prototypes \
			-Wmissing-declarations \
			-Wmissing-noreturn \
			-Wredundant-decls
	do
		AC_MSG_CHECKING([if $CC accepts $NEW_FLAG])
		OLD_CFLAGS="$CFLAGS"
		CFLAGS="$CFLAGS $NEW_FLAG"
		AC_COMPILE_IFELSE([AC_LANG_SOURCE([void foo(void) { }])], [
			AM_CFLAGS="$AM_CFLAGS $NEW_FLAG"
			AC_MSG_RESULT([yes])
		], [
			AC_MSG_RESULT([no])
		])
		CFLAGS="$OLD_CFLAGS"
	done
fi

AC_ARG_ENABLE([debugging-symbols],
	AS_HELP_STRING([--enable-debugging-symbols],
		[enable debugging symbols (default is NO)]),
	AM_CFLAGS="${AM_CFLAGS} -O0 -g -fno-inline")

AC_ARG_ENABLE([werror],
	AS_HELP_STRING([--enable-werror], [use -Werror (default is NO)]),
	AM_CFLAGS="${AM_CFLAGS} -Werror")

AC_CHECK_LIB([m], [log])
AC_CONFIG_HEADERS([config.h])
AC_SUBST([AM_CFLAGS])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT
