/*
 *  FRacing/test/gps_test.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Test program for GPS.
 */

#include "config.h"

#include <iostream>

#include <Configuration.h>
#include <FrameBuffer.h>

int main(int argc, char **argv)
{
	Configuration *config = Configuration::instance("frconfig.cfg");
	config->parse();

	FrameBuffer *fb = FrameBuffer::instance(
			config->get("framebuffer", "device"),
			config->get("console", "device"));

	if (!fb->open())
	{
		fprintf(stderr, "open frame buffer failed\n");
		return 1;
	}

	char msg[] = "Frame Buffer test program";

	fb->create_window("main");

	fb->window().set_color(0, 0x000000);
	fb->window().set_color(1, 0xffe080);
	fb->window().fill_rect(0, 0, fb->get_xres() - 1, fb->get_yres() - 1, 0);
	fb->window().put_string_center(fb->get_xres()/2, fb->get_yres()/2, msg, 1);

	fb->close();

	return 0;
}

