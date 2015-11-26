#ifndef _SINGLETON_H_
#define _SINGLETON_H_
/*
 *  FRacing/lib/utillity/Singleton.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Singleton library interface definitions.
 */

#if 1

#include <iostream>

template <class T>
class Singleton
{
public:
	template <typename... Args>
	static
	T* instance(Args... args)
	{
		if (!instance_)
		{
			instance_ = new T(std::forward<Args>(args)...);
		}

		return instance_;
	}

	static
	void destroy()
	{
		if (instance_)
		{
			delete instance_;
		}

		instance_ = nullptr;
	}

private:
	static T* instance_;

};

template <class T> T* Singleton<T>::instance_ = nullptr;

#else
template <typename T>
class Singleton
{
public:
	static T& instance();

protected:
	virtual ~Singleton();
	inline explicit Singleton();

private:
	static T* instance_;
	static T* create_instance();
};

template <typename T>
T* Singleton<T>::instance_ = NULL;
#endif

#endif /* _SINGLETON_H_ */

