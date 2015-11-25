#
#  FRacing/test/Makefile.am
#
#  Copyright (C) 2015 Ikhyun Kim.
#
# This file is placed under the GPL.  Please see the file
# COPYING for more details.
#
#

bin_PROGRAMS = config_test
config_test_SOURCES = config_test.cpp
config_test_CXXFLAGS = -I$(top_srcdir)/lib/configuration
config_test_LDADD = $(builddir)/../lib/utillity/libfrutillity.la
config_test_LDADD += $(builddir)/../lib/configuration/libfrconfiguration.la

AM_CFLAGS=-Wall -Werror
AM_CXXFLAGS=-Wall -Werror

