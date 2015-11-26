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

#include <Singleton.h>
#include <ConfigSection.h>

class Configuration : public Singleton<Configuration>
{
	friend class Singleton<Configuration>;

private:
	Configuration(void);
	Configuration(std::string file_name);
	~Configuration(void);

public:
	void file_name(std::string file_name);
	//void file_name(char *file_name);
	std::string& file_name(void);

	bool parse(void);
	void add(std::string section_name, std::string key, std::string value);

	std::string get(std::string section_name, std::string key);

	void dump(void);

private:
	std::string file_name_;
	std::list<ConfigSection> sections_;
};

#endif /* _CONFIGURATION_H_ */

