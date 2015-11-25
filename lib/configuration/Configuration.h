#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_
/*
 *  FRacing/lib/configuration/Configuration.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Configuration library interface definitions.
 */

#include <string>

class Configuration
{
public:
	Configuration(void);
	~Configuration(void);

private:
	std::string filename_;
};

#endif /* _CONFIGURATION_H_ */

