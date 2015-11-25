/*
 *  FRacing/lib/configuration/ConfigItem.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Configuration item implementation.
 */

#include "config.h"

#include <iostream>

#include <ConfigItem.h>

ConfigItem::ConfigItem(void)
	: key_(),
	  value_()
{
}

ConfigItem::ConfigItem(std::string key, std::string value)
	: key_(key),
	  value_(value)
{
}

ConfigItem::~ConfigItem(void)
{
}

void ConfigItem::key(std::string key)
{
	key_ = key;
}

std::string& ConfigItem::key(void)
{
	return key_;
}

void ConfigItem::value(std::string value)
{
	value_ = value;
}

std::string& ConfigItem::value(void)
{
	return value_;
}


void ConfigItem::set(std::string key, std::string value)
{
	key_ = key;
	value_ = value;
}

void ConfigItem::dump(void)
{
	std::cout << "key: " << key_ << ", value: " << value_ << std::endl;
}

