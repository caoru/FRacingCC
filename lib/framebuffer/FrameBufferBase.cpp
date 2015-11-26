/*
 *  FRacing/lib/framebuffer/FrameBufferBase.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Frame buffer base class implementtion.
 */

#include "config.h"

#include <string.h>

#include <FrameBufferBase.h>

FrameBufferBase::FrameBufferBase(void)
	: fb_device_(),
	  console_device_()
{
	fb_fd_ = -1;
	con_fd_ = -1;
	last_vt_ = -1;
	fb_buffer_ = NULL;
	line_addr_ = NULL;
}

FrameBufferBase::~FrameBufferBase(void)
{
}

void FrameBufferBase::operator=(const FrameBufferBase& obj)
{
	(*this).fb_device_ = obj.fb_device_;
	(*this).console_device_ = obj.console_device_;
	(*this).fb_fd_ = obj.fb_fd_;
	(*this).con_fd_ = obj.con_fd_;
	(*this).last_vt_ = obj.last_vt_;
	(*this).fb_buffer_ = obj.fb_buffer_;
	(*this).line_addr_ = obj.line_addr_;
	(*this).bytes_per_pixel_ = obj.bytes_per_pixel_;
	memcpy(&(*this).fix_screen_info_, &obj.fix_screen_info_,
		   sizeof(struct fb_fix_screeninfo));
	memcpy(&(*this).var_screen_info_, &obj.var_screen_info_,
		   sizeof(struct fb_var_screeninfo));
}

void FrameBufferBase::fb_device(std::string fb_device)
{
	fb_device_ = fb_device;
}

std::string& FrameBufferBase::fb_device(void)
{
	return fb_device_;
}

void FrameBufferBase::console_device(std::string console_device)
{
	console_device_ = console_device;
}

std::string& FrameBufferBase::console_device(void)
{
	return console_device_;
}

void FrameBufferBase::fb_fd(int fd)
{
	fb_fd_ = fd;
}

int FrameBufferBase::fb_fd(void)
{
	return fb_fd_;
}

void FrameBufferBase::con_fd(int fd)
{
	con_fd_ = fd;
}

int FrameBufferBase::con_fd(void)
{
	return con_fd_;
}

struct fb_fix_screeninfo& FrameBufferBase::fix_screen_info(void)
{
	return fix_screen_info_;
}

struct fb_var_screeninfo& FrameBufferBase::var_screen_info(void)
{
	return var_screen_info_;
}

void FrameBufferBase::fb_buffer(unsigned char *buffer)
{
	fb_buffer_ = buffer;
}

unsigned char* FrameBufferBase::fb_buffer(void)
{
	return fb_buffer_;
}

void FrameBufferBase::line_addr(unsigned char **addr)
{
	line_addr_ = addr;
}

unsigned char** FrameBufferBase::line_addr(void)
{
	return line_addr_;
}

void FrameBufferBase::bytes_per_pixel(int value)
{
	bytes_per_pixel_ = value;
}

int FrameBufferBase::bytes_per_pixel(void)
{
	return bytes_per_pixel_;
}

void FrameBufferBase::last_vt(int value)
{
	last_vt_ = value;
}

int FrameBufferBase::last_vt(void)
{
	return last_vt_;
}

