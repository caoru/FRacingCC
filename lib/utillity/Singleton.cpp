/*
 *  FRacing/lib/utillity/Singleton.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Singleton library interface implementation.
 */

#include "config.h"

#include <cstdlib>

#include <Singleton.h>

#if 0
template <typename T>
Singleton<T>::Singleton()
{
	assert(Singleton::instance_ == 0);
	Singleton::instance_ = static_cast<T*>(this);
}

template <typename T>
T& Singleton<T>::instance()
{
	if (Singleton::instance_ == NULL)
	{
		Singleton::instance_ = create_instance();
	}

	return *(Singleton::instance_);
}

template <typename T>
T* Singleton<T>::create_instance()
{
	return new T();
}

template <typename T>
Singleton<T>::~Singleton()
{
	if (Singleton::instance_ != NULL)
	{
		delete Singleton::instance_;
	}

	Singleton::instance_ = NULL;
}
#endif

