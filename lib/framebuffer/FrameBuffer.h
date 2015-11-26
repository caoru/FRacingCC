#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_
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
#include <linux/fb.h>

#include <Singleton.h>
#include <FrameBufferBase.h>
#include <FrameBufferWindow.h>

class FrameBuffer : public FrameBufferBase, public Singleton<FrameBuffer>
{
	friend class Singleton<FrameBuffer>;
public:
	FrameBuffer(void);
	FrameBuffer(std::string fb_device, std::string console_device);
	~FrameBuffer(void);

	FrameBufferWindow& window(void);

	bool open(void);
	bool open_framebuffer(void);
	bool open_console(void);

	void close(void);
	void close_framebuffer(void);
	void close_console(void);

	void create_window(std::string name);

	int get_xres(void);
	int get_yres(void);

private:
	FrameBufferWindow window_;
};

#endif /* _FRAME_BUFFER_H_ */

