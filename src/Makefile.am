#
#  FRacing/src/Makefile.am
#
#  Copyright (C) 2015 Ikhyun Kim.
#
# This file is placed under the GPL.  Please see the file
# COPYING for more details.
#
#

bin_PROGRAMS = fracing
fracing_SOURCES = main.cpp
fracing_CXXFLAGS = -I$(top_srcdir)/lib/utillity
fracing_CXXFLAGS += -I$(top_srcdir)/lib/configuration
fracing_CXXFLAGS += -I$(top_srcdir)/lib/framebuffer
fracing_LDADD = $(builddir)/../lib/utillity/libfrutillity.la
fracing_LDADD += $(builddir)/../lib/configuration/libfrconfiguration.la
fracing_LDADD += $(builddir)/../lib/framebuffer/libfrframebuffer.la

