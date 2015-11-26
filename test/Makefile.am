#
#  FRacing/test/Makefile.am
#
#  Copyright (C) 2015 Ikhyun Kim.
#
# This file is placed under the GPL.  Please see the file
# COPYING for more details.
#
#

bin_PROGRAMS = config_test fb_test

config_test_SOURCES = config_test.cpp
config_test_CXXFLAGS = -I$(top_srcdir)/lib/utillity
config_test_CXXFLAGS += -I$(top_srcdir)/lib/configuration
#config_test_LDADD = $(builddir)/../lib/utillity/libfrutillity.la
config_test_LDADD = $(builddir)/../lib/configuration/libfrconfiguration.la

fb_test_SOURCES = fb_test.cpp
fb_test_CXXFLAGS = -I$(top_srcdir)/lib/utillity
fb_test_CXXFLAGS += -I$(top_srcdir)/lib/framebuffer
fb_test_CXXFLAGS += -I$(top_srcdir)/lib/configuration
#fb_test_LDADD = $(builddir)/../lib/utillity/libfrutillity.la
fb_test_LDADD = $(builddir)/../lib/configuration/libfrconfiguration.la
fb_test_LDADD += $(builddir)/../lib/framebuffer/libfrframebuffer.la

