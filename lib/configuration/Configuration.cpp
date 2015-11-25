/*
 *  FRacing/lib/configuration/Configuration.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Configuration library interface implementation.
 */

#include "config.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <frstring.h>
#include <Configuration.h>

Configuration::Configuration(void)
	:file_name_()
{
}

Configuration::Configuration(std::string file_name)
	: file_name_(file_name)
{
}

Configuration::~Configuration(void)
{
}

void Configuration::file_name(std::string file_name)
{
	file_name_ = file_name;
}

void Configuration::file_name(char *file_name)
{
	file_name_ = file_name;
}

std::string& Configuration::file_name(void)
{
	return file_name_;
}

bool Configuration::parse(void)
{
	std::ifstream ifs;
	std::string line;
	std::string data;
	std::string section_name;

	try
	{
		ifs.open(file_name_.c_str());

		while (!ifs.eof())
		{
			getline(ifs, line);
			data = frstring::trim(line);

			if (data.compare(0, 1, "[") == 0)
			{ // Section name
				section_name = data.substr(1, data.length() - 2);
			}
			else if (data.length() > 0)
			{
				std::istringstream iss(data);
				std::string token;
				std::string key;
				std::string value;

				std::getline(iss, key, '=');
				std::getline(iss, value, '=');

				add(section_name, frstring::trim(key), frstring::trim(value));
			}
		}

		ifs.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "Exception opening/reading/closing file" << std::endl;
		return false;
	}

	return true;
}

void Configuration::add(std::string section_name, std::string key, std::string value)
{
	std::list<ConfigSection>::iterator iter = sections_.begin();

	while (iter != sections_.end())
	{
		if (section_name.compare((*iter).section_name()) == 0)
		{
			(*iter).add(key, value);
			return;
		}
		iter++;
	}

	ConfigSection section(section_name);
	section.add(key, value);

	sections_.push_back(section);

	return;
}

void Configuration::dump(void)
{
	std::list<ConfigSection>::iterator iter = sections_.begin();

	std::cout << "====================================================" << std::endl;
	std::cout << "Section count is " << sections_.size() << std::endl;

	while (iter != sections_.end())
	{
		(*iter).dump();
		iter++;
	}

	std::cout << "====================================================" << std::endl;
}

