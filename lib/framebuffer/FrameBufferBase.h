#ifndef _FRAME_BUFFER_BASE_H_
#define _FRAME_BUFFER_BASE_H_
/*
 *  FRacing/lib/framebuffer/FrameBufferBase.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Frame buffer base class definitions.
 */

#include <string>
#include <linux/fb.h>

class FrameBufferBase
{
public:
	FrameBufferBase(void);
	~FrameBufferBase(void);

	void operator=(const FrameBufferBase& obj);

	void fb_device(std::string fb_device);
	std::string& fb_device(void);

	void console_device(std::string console_device);
	std::string& console_device(void);

	void fb_fd(int fd);
	int fb_fd(void);

	void con_fd(int fd);
	int con_fd(void);

	struct fb_fix_screeninfo& fix_screen_info(void);
	struct fb_var_screeninfo& var_screen_info(void);

	void fb_buffer(unsigned char *buffer);
	unsigned char* fb_buffer(void);

	void line_addr(unsigned char **addr);
	unsigned char** line_addr(void);

	void bytes_per_pixel(int value);
	int bytes_per_pixel(void);

	void last_vt(int value);
	int last_vt(void);

protected:
	std::string fb_device_;
	int fb_fd_;
	unsigned char *fb_buffer_;
	unsigned char **line_addr_;
	int bytes_per_pixel_;

	struct fb_fix_screeninfo fix_screen_info_;
	struct fb_var_screeninfo var_screen_info_;

	std::string console_device_;
	int con_fd_;
	int last_vt_;

};

#endif /* _FRAME_BUFFER_BASE_H_ */

