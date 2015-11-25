#ifndef _CONFIG_ITEM_H_
#define _CONFIG_ITEM_H_
/*
 *  FRacing/lib/configuration/ConfigItem.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Configuration item definitions.
 */

#include <string>

class ConfigItem
{
public:
	ConfigItem(void);
	ConfigItem(std::string key, std::string value);
	~ConfigItem(void);

	void key(std::string key);
	std::string& key(void);
	void value(std::string value);
	std::string& value(void);

	void set(std::string key, std::string value);
	void dump(void);

private:
	std::string key_;
	std::string value_;
};

#endif /* _CONFIG_ITEM_H_ */

