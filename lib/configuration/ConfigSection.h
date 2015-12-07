#ifndef _CONFIG_SECTION_H_
#define _CONFIG_SECTION_H_
/*
 *  FRacing/lib/configuration/ConfigSection.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Configuration section definitions.
 */

#include "config.h"

#include <string>
#include <list>

#include <ConfigItem.h>

class ConfigSection
{
public:
	ConfigSection(void);
	ConfigSection(std::string section_name);
	~ConfigSection(void);

	void section_name(std::string section_name);
	std::string& section_name(void);

	void add(std::string key, std::string value);
	std::string get(std::string key);

	void dump(void);

private:
	std::string section_name_;
	std::list<ConfigItem> items_;
};

#endif /* _CONFIG_SECTION_H_ */

