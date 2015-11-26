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
AC_CHECK_LIB([ts], [ts_open], [], [AC_MSG_ERROR([ts_open was not fount in libts])])

# Checks for header files.
AC_CHECK_HEADER([tslib.h], [], [AC_MSG_ERROR([tslib.h was not fount in libts])])

# Checks for typedefs, structures, and compiler characteristics.
AX_CHECK_COMPILE_FLAG([-std=c++11], [CXXFLAGS="$CXXFLAGS -std=c++11"])
AX_CHECK_COMPILE_FLAG([-Wall], [CXXFLAGS="$CXXFLAGS -Wall"])
AX_CHECK_COMPILE_FLAG([-Werror], [CXXFLAGS="$CXXFLAGS -Werror"])

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 lib/utillity/Makefile
                 lib/configuration/Makefile
                 lib/framebuffer/Makefile
                 test/Makefile
                 src/Makefile])
AC_OUTPUT
