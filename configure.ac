AC_PREREQ([2.64])
AC_INIT([wham], [1.3], [ilya.kaliman@gmail.com])
AC_CONFIG_SRCDIR([src/pmf.c])
AM_INIT_AUTOMAKE([-Wall -Werror])

AC_MSG_CHECKING([if debugging code should be compiled])
AC_ARG_ENABLE([debug], AC_HELP_STRING(
	[--enable-debug], [Enable debugging code.]), [], enable_debug=no)
if test "x$enable_debug" = xyes; then
	AC_MSG_RESULT([yes])
else
	AC_DEFINE([NDEBUG], [1], [Define to 1 to disable debugging code.])
	AC_MSG_RESULT([no])
fi

AC_LANG([C])
AC_PROG_CC
AC_PROG_CC_C99
if test x$ac_cv_prog_cc_c99 = xno ; then
	AC_MSG_ERROR([No C99 compiler was found.])
fi

if test "$GCC" = yes ; then
	for NEW_FLAG in -Wall \
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

	AC_ARG_ENABLE([werror],
		AC_HELP_STRING([--enable-werror], [Enable -Werror to abort
			compilation on all compiler warnings.]),
		[], [enable_werror=no])
	if test "x$enable_werror" = "xyes"; then
		AM_CFLAGS="$AM_CFLAGS -Werror"
	fi
fi

AC_CHECK_LIB([m], [log])
AC_CONFIG_HEADERS([config.h])
AC_SUBST([AM_CFLAGS])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_OUTPUT
