#ifndef _FRAME_BUFFER_WINDOW_H_
#define _FRAME_BUFFER_WINDOW_H_
/*
 *  FRacing/lib/framebuffer/FrameBuffer.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Frame buffer window library interface definitions.
 */

#include "config.h"

#include <string>

#include <FrameBufferDraw.h>

class FrameBufferWindow : public FrameBufferDraw
{
public:
	FrameBufferWindow(void);
	~FrameBufferWindow(void);

	void name(std::string& name);
	std::string& name(void);

private:
	std::string name_;
};

#endif /* _FRAME_BUFFER_WINDOW_H_ */

