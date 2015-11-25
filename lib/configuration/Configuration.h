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

#include <ConfigSection.h>

class Configuration
{
public:
	Configuration(void);
	Configuration(std::string file_name);
	~Configuration(void);

	void file_name(std::string file_name);
	void file_name(char *file_name);
	std::string& file_name(void);

	bool parse(void);
	void add(std::string section_name, std::string key, std::string value);

	void dump(void);

private:
	std::string file_name_;
	std::list<ConfigSection> sections_;
};

#endif /* _CONFIGURATION_H_ */

