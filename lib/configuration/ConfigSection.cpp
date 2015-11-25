/*
 *  FRacing/lib/configuration/ConfigSection.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Configuration section implementation.
 */

#include "config.h"

#include <iostream>

#include <ConfigSection.h>

ConfigSection::ConfigSection(void)
	:section_name_()
{
}

ConfigSection::ConfigSection(std::string section_name)
	: section_name_(section_name)
{
}

ConfigSection::~ConfigSection(void)
{
}

void ConfigSection::section_name(std::string section_name)
{
	section_name_ = section_name;
}

std::string& ConfigSection::section_name(void)
{
	return section_name_;
}

void ConfigSection::add(std::string key, std::string value)
{
	items_.push_back(ConfigItem(key, value));
}

std::string ConfigSection::get(std::string key)
{
	std::list<ConfigItem>::iterator iter = items_.begin();

	while (iter != items_.end())
	{
		if (key.compare((*iter).key()) == 0)
			return (*iter).value();
		iter++;
	}

	return std::string("");
}

void ConfigSection::dump(void)
{
	std::list<ConfigItem>::iterator iter = items_.begin();

	std::cout << "====================================================" << std::endl;
	std::cout << "Section: " << section_name_ << std::endl;
	std::cout << "Item count is " << items_.size() << std::endl;

	while (iter != items_.end())
	{
		(*iter).dump();
		iter++;
	}
}

