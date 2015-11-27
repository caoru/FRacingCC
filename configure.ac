#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FRacing], [0.1], [frag@frag.kr])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])

#AM_INIT_AUTOMAKE([foreign])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.
AC_ARG_WITH([libts],
	[AS_HELP_STRING([--without-libts],
		[Disable library for touch screen support @<:@default=yes@:>@])],
	[:],
	[with_libts=yes])

AS_IF([test "$with_libts" != "no"],
	[AC_CHECK_LIB([ts],
		[ts_open],
		[AS_IF([test "$with_libts" != "no"],
			[AC_CHECK_HEADER([tslib.h],
				[with_libts=yes],
				[with_libts=no])])],
		[with_libts=no])])

if test "$with_libts" = "yes"; then
	AC_DEFINE([HAVE_LIBTS], [1], [Define if libts exist.])
	LIBTS_CXXFLAGS=""
	LIBTS_LDADD="-lts"
else
	LIBTS_CXXFLAGS=""
	LIBTS_LDADD=""
fi
AC_SUBST(LIBTS_CXXFLAGS)
AC_SUBST(LIBTS_LDADD)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_SIZEOF([void *])

AX_CHECK_COMPILE_FLAG([-std=c++11], [CXXFLAGS="$CXXFLAGS -std=c++11"])
AX_CHECK_COMPILE_FLAG([-Wall], [CXXFLAGS="$CXXFLAGS -Wall"])
AX_CHECK_COMPILE_FLAG([-Werror], [CXXFLAGS="$CXXFLAGS -Werror"])


AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 lib/utillity/Makefile
                 lib/configuration/Makefile
                 lib/framebuffer/Makefile
                 lib/gps/Makefile
                 test/Makefile
                 src/Makefile])
AC_OUTPUT
