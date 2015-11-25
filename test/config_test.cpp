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
	Configuration config("frconfig.cfg");
	config.parse();
	config.dump();

	return 0;
}

