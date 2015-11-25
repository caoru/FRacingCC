#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_
/*
 *  FRacing/lib/framebuffer/FrameBuffer.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Frame buffer library interface definitions.
 */

#include <string>

class FrameBuffer
{
public:
	FrameBuffer(void);
	~FrameBuffer(void);

private:
	std::string fbdevice_;
};

#endif /* _FRAMEBUFFER_H_ */

