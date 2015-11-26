/*
 *  FRacing/lib/framebuffer/FrameBuffer.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Frame buffer library interface implementtion.
 */

#include "config.h"

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/vt.h>
#include <linux/kd.h>

#include <FrameBuffer.h>

FrameBuffer::FrameBuffer(void)
	: FrameBufferBase()
{
}

FrameBuffer::FrameBuffer(std::string fb_device, std::string console_device)
	: FrameBuffer()
{
	fb_device_ = fb_device;
	console_device_ = console_device;
}

FrameBuffer::~FrameBuffer(void)
{
}

FrameBufferWindow& FrameBuffer::window(void)
{
	return window_;
}

bool FrameBuffer::open(void)
{
	if (!open_framebuffer())
		return false;

	if (!open_console())
		return false;

	return true;
}

bool FrameBuffer::open_framebuffer(void)
{
	unsigned int addr;
	unsigned int y;

	fb_fd_ = ::open(fb_device_.c_str(), O_RDWR);
	if (fb_fd_ == -1)
	{
		perror("open fbdevice");
		return false;
	}

	if (ioctl(fb_fd_, FBIOGET_FSCREENINFO, &fix_screen_info_) < 0)
	{
		perror("ioctl FBIOGET_FSCREENINFO");
		::close(fb_fd_);
		return false;
	}

	if (ioctl(fb_fd_, FBIOGET_VSCREENINFO, &var_screen_info_) < 0)
	{
		perror("ioctl FBIOGET_VSCREENINFO");
		::close(fb_fd_);
		return false;
	}

	fb_buffer_ = (unsigned char *)mmap(NULL, fix_screen_info_.smem_len,
									   PROT_READ | PROT_WRITE,
									   MAP_FILE | MAP_SHARED,
									   fb_fd_, 0);
	if (fb_buffer_ == (unsigned char *)-1)
	{
		perror("mmap frame buffer");
		::close(fb_fd_);
		return false;
	}
	memset(fb_buffer_, 0x00, fix_screen_info_.smem_len);

	bytes_per_pixel_ = (var_screen_info_.bits_per_pixel + 7) / 8;
	line_addr_ = (unsigned char **)malloc(sizeof(void *) * var_screen_info_.yres_virtual);
	addr = 0;
	for (y = 0; y < var_screen_info_.yres_virtual; y++, addr += fix_screen_info_.line_length)
	{
		line_addr_[y] = fb_buffer_ + addr;
	}

	return true;
}

bool FrameBuffer::open_console(void)
{
	struct vt_stat vts;
	char vtname[128];
	int fd;
	int nr;

	if (console_device_.compare("none") != 0)
	{
		sprintf(vtname, "%s%d", console_device_.c_str(), 1);
		fd = ::open(vtname, O_WRONLY);
		if (fd < 0)
		{
			perror("open console device");
			return false;
		}

		if (ioctl(fd, VT_OPENQRY, &nr) < 0)
		{
			perror("ioctl VT_OPENQRY");
			::close(fd);
			return false;
		}
		::close(fd);

		sprintf(vtname, "%s%d", console_device_.c_str(), nr);

		con_fd_ = ::open(vtname, O_RDWR | O_NDELAY);
		if (con_fd_ < 0)
		{
			perror("open tty");
			return false;
		}

		if (ioctl(con_fd_, VT_GETSTATE, &vts) == 0)
		{
			last_vt_ = vts.v_active;
		}

		if (ioctl(con_fd_, VT_ACTIVATE, nr) < 0)
		{
			perror("ioctl VT_ACTIVATE");
			::close(con_fd_);
			return false;
		}

#ifndef TSLIB_NO_VT_WAITACTIVE
		if (ioctl(con_fd_, VT_WAITACTIVE, nr) < 0)
		{
			perror("ioctl VT_WAITACTIVE");
			::close(con_fd_);
			return false;
		}
#endif

		if (ioctl(con_fd_, KDSETMODE, KD_GRAPHICS) < 0)
		{
			perror("ioctl KDSETMOCE");
			::close(con_fd_);
			return false;
		}
	}

	return true;
}


void FrameBuffer::close(void)
{
	close_framebuffer();
	close_console();
}

void FrameBuffer::close_framebuffer(void)
{
	munmap(fb_buffer_, fix_screen_info_.smem_len);
	::close(fb_fd_);

	free(line_addr_);
}

void FrameBuffer::close_console(void)
{
	if (console_device_.compare("none") != 0)
	{
		if (ioctl(con_fd_, KDSETMODE, KD_TEXT) < 0)
		{
			perror("ioctl KDSETMODE");
		}

		if (last_vt_ >= 0)
		{
			if (ioctl(con_fd_, VT_ACTIVATE, last_vt_) < 0)
			{
				perror("ioctl VT_ACTIVATE");
			}
		}

		::close(con_fd_);
	}
}

void FrameBuffer::create_window(std::string name)
{
	FrameBufferBase *src = dynamic_cast<FrameBufferBase *>(this);
	FrameBufferBase *dst = dynamic_cast<FrameBufferBase *>(&window_);

	*dst = *src;

	window_.name(name);
}

int FrameBuffer::get_xres(void)
{
	return var_screen_info_.xres;
}

int FrameBuffer::get_yres(void)
{
	return var_screen_info_.yres;
}

