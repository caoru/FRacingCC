/*
 *  FRacing/test/fb_test.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Test program for Frame buffer.
 */

#include "config.h"

#include <iostream>

#include <Configuration.h>
#include <FrameBuffer.h>

int main(int argc, char **argv)
{
	Configuration::instance()->file_name("frconfig.cfg");
	Configuration::instance()->parse();

	FrameBuffer::instance()->fb_device(Configuration::instance()->get("framebuffer", "device"));
	FrameBuffer::instance()->console_device(Configuration::instance()->get("console", "device"));
	if (!FrameBuffer::instance()->open())
	{
		fprintf(stderr, "open frame buffer failed\n");
		return 1;
	}

	FrameBuffer::instance()->close();

	return 0;
}

