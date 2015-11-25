#ifndef _FRSTRING_H
#define _FRSTRING_H
/*
 *  FRacing/lib/configuration/Configuration.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * String library interface definitions.
 */

#include <string>

#define TRIM_SPACE	"\t\n\v "

namespace frstring
{
	inline std::string trim(std::string& s, const std::string& drop = TRIM_SPACE)
	{
		std::string r = s.erase(s.find_last_not_of(drop) + 1);
		return r.erase(0, r.find_first_not_of(drop));
	}

	inline std::string rtrim(std::string s, const std::string& drop = TRIM_SPACE)
	{
		return s.erase(s.find_last_not_of(drop) + 1);
	}

	inline std::string ltrim(std::string s,const std::string& drop = TRIM_SPACE)
	{
		return s.erase(0, s.find_first_not_of(drop));
	}
}

#endif /* _FRSTRING_H */

