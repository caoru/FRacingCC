/*
 *  FRacing/test/config_test.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Test program for Configuration.
 */

#include "config.h"

#include <iostream>

#include <Configuration.h>

int main(int argc, char **argv)
{
	//Configuration config("frconfig.cfg");
	//config.parse();
	//config.dump();

	//Configuration::instance("frconfig.cfg");

	Configuration::instance()->file_name("frconfig.cfg");
	Configuration::instance()->parse();
	Configuration::instance()->dump();

	std::cout << "framebuffer:device = " << Configuration::instance()->get("framebuffer", "device") << std::endl;

	return 0;
}

