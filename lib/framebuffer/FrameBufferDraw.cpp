/*
 *  FRacing/lib/framebuffer/FrameBufferDraw.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Frame buffer drawing library interface implementation.
 */

#include "config.h"

#include <string.h>
#include <sys/ioctl.h>

#include <font.h>
#include <FrameBufferDraw.h>

#define XORMODE 0x80000000

FrameBufferDraw::FrameBufferDraw(void)
	: FrameBufferBase()
{
}

FrameBufferDraw::~FrameBufferDraw(void)
{
}

void FrameBufferDraw::put_cross(int x, int y, unsigned int colidx)
{
	line(x - 10, y, x - 2, y, colidx);
	line(x + 2, y, x + 10, y, colidx);
	line(x, y - 10, x, y - 2, colidx);
	line(x, y + 2, x, y + 10, colidx);

#if 1
	line(x - 6, y - 9, x - 9, y - 9, colidx + 1);
	line(x - 9, y - 8, x - 9, y - 6, colidx + 1);
	line(x - 9, y + 6, x - 9, y + 9, colidx + 1);
	line(x - 8, y + 9, x - 6, y + 9, colidx + 1);
	line(x + 6, y + 9, x + 9, y + 9, colidx + 1);
	line(x + 9, y + 8, x + 9, y + 6, colidx + 1);
	line(x + 9, y - 6, x + 9, y - 9, colidx + 1);
	line(x + 8, y - 9, x + 6, y - 9, colidx + 1);
#else
	line(x - 7, y - 7, x - 4, y - 4, colidx + 1);
	line(x - 7, y + 7, x - 4, y + 4, colidx + 1);
	line(x + 4, y - 4, x + 7, y - 7, colidx + 1);
	line(x + 4, y + 4, x + 7, y + 7, colidx + 1);
#endif
}

void FrameBufferDraw::put_char(int x, int y, int c, int colidx)
{
	int i, j, bits;

	for (i = 0; i < font_vga_8x8.height; i++)
	{
		bits = font_vga_8x8.data[font_vga_8x8.height * c + i];
		for (j = 0; j < font_vga_8x8.width; j++, bits <<= 1)
		{
			if (bits & 0x80)
			{
				pixel(x + j, y + i, colidx);
			}
		}
	}
}

void FrameBufferDraw::put_string(int x, int y, char *s, unsigned int colidx)
{
	int i;

	for (i = 0; *s; i++, x += font_vga_8x8.width, s++)
	{
		put_char(x, y, *s, colidx);
	}
}

void FrameBufferDraw::put_string_center(int x, int y, char *s, unsigned int colidx)
{
	size_t sl = strlen(s);
	put_string(x - (sl / 2) * font_vga_8x8.width,
			   y - font_vga_8x8.height / 2, s, colidx);
}

void FrameBufferDraw::set_color(unsigned int colidx, unsigned value)
{
	unsigned int res;
	unsigned short red, green, blue;
	struct fb_cmap cmap;

#ifdef DEBUG
	if (colidx > 255)
	{
		fprintf(stderr, "WARNING: color index = %u, must be <256\n", colidx);
		return;
	}
#endif

	switch (bytes_per_pixel_)
	{
		default:
		case 1:
			res = colidx;
			red = (value >> 8) & 0xff00;;
			green = value & 0xff00;
			blue = (value << 8) & 0xff00;;
			cmap.start = colidx;
			cmap.len = 1;
			cmap.red = &red;
			cmap.green = &green;
			cmap.blue = &blue;
			cmap.transp = NULL;

			if (ioctl(fb_fd_, FBIOPUTCMAP, &cmap) < 0)
			{
				perror("ioctl FBIOPUTCMAP");
			}

			break;

		case 2:
		case 3:
		case 4:
			red = (value >> 16) & 0xff;
			green = (value >> 8) & 0xff;
			blue = value & 0xff;
			res = 
				((red >> (8 - var_screen_info_.red.length)) << var_screen_info_.red.offset) |
				((green >> (8 - var_screen_info_.green.length)) << var_screen_info_.green.offset) |
				((blue >> (8 - var_screen_info_.blue.length)) << var_screen_info_.blue.offset);
	}

	color_map_[colidx] = res;
}

void FrameBufferDraw::__set_pixel(union multiptr loc, unsigned int xormode, unsigned int color)
{
	switch (bytes_per_pixel_)
	{
		case 1:
		default:
			if (xormode)
				*loc.p8 ^= color;
			else
				*loc.p8 = color;
			break;

		case 2:
			if (xormode)
				*loc.p16 ^= color;
			else
				*loc.p16 = color;
			break;

		case 3:
			if (xormode)
			{
				*loc.p8++ ^= (color >> 16) & 0xff;
				*loc.p8++ ^= (color >> 8) & 0xff;
				*loc.p8 ^= color & 0xff;
			}
			else
			{
				*loc.p8++ = (color >> 16) & 0xff;
				*loc.p8++ = (color >> 8) & 0xff;
				*loc.p8 = color & 0xff;
			}
			break;

		case 4:
			if (xormode)
				*loc.p32 ^= color;
			else
				*loc.p32 = color;
	}
}

void FrameBufferDraw::pixel(int x, int y, unsigned int colidx)
{
	unsigned int xormode;
	union multiptr loc;

	if ((x < 0) || ((__u32)x >= var_screen_info_.xres_virtual) ||
		(y < 0) || ((__u32)y >= var_screen_info_.yres_virtual))
	{
		return;
	}

	xormode = colidx & XORMODE;
	colidx &= ~XORMODE;

#ifdef DEBUG
	if (colidx > 255)
	{
		fprintf(stderr, "WARNING: color value = %u, must be <256\n"), colidx);
		return ;
	}
#endif

	loc.p8 = line_addr_[y] + x * bytes_per_pixel_;
	__set_pixel(loc, xormode, color_map_[colidx]);
}

void FrameBufferDraw::line(int x1, int y1, int x2, int y2, unsigned int colidx)
{
	int tmp;
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (abs(dx) < abs(dy))
	{
		if (y1 > y2)
		{
			tmp = x1; x1 = x2; x2 = tmp;
			tmp = y1; y1 = y2; y2 = tmp;
			dx = -dx; dy = -dy;
		}
		x1 <<= 16;
		/* dy is apriori >0 */
		dx = (dx << 16) / dy;
		while (y1 <= y2)
		{
			pixel(x1 >> 16, y1, colidx);
			x1 += dx;
			y1++;
		}
	}
	else
	{
		if (x1 > x2)
		{
			tmp = x1; x1 = x2; x2 = tmp;
			tmp = y1; y1 = y2; y2 = tmp;
			dx = -dx; dy = -dy;
		}
		y1 <<= 16;
		dy = dx ? (dy << 16) / dx : 0;
		while (x1 <= x2)
		{
			pixel(x1, y1 >> 16, colidx);
			y1 += dy;
			x1++;
		}
	}
}

void FrameBufferDraw::fill_rect(int x1, int y1, int x2, int y2, unsigned int colidx)
{
	int tmp;
	unsigned int xormode;
	union multiptr loc;

	/* Clipping and sanity checking */
	if (x1 > x2) { tmp = x1; x1 = x2; x2 = tmp; }
	if (y1 > y2) { tmp = y1; y1 = y2; y2 = tmp; }

	if (x1 < 0) x1 = 0;
	if ((__u32)x1 >= var_screen_info_.xres) x1 = var_screen_info_.xres - 1;
	if (x2 < 0) x2 = 0;
	if ((__u32)x2 >= var_screen_info_.xres) x2 = var_screen_info_.xres - 1;

	if (y1 < 0) y1 = 0;
	if ((__u32)y1 >= var_screen_info_.yres) y1 = var_screen_info_.yres - 1;
	if (y2 < 0) y2 = 0;
	if ((__u32)y2 >= var_screen_info_.yres) y2 = var_screen_info_.yres - 1;

	if ((x1 > x2) || (y1 > y2))
		return;

	xormode = colidx &XORMODE;
	colidx &= ~XORMODE;

#ifdef DEBUG
	if (colidx > 255)
	{
		fprintf(stderr, "WARNING: color index = %u, must be <256\n", colidx);
		return;
	}
#endif

	colidx = color_map_[colidx];

	for (; y1 <= y2; y1++)
	{
		loc.p8 = line_addr_[y1] + x1 * bytes_per_pixel_;
		for (tmp = x1; tmp <= x2; tmp++)
		{
			__set_pixel(loc, xormode, colidx);
			loc.p8 += bytes_per_pixel_;
		}
	}
}

