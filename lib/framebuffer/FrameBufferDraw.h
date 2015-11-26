#ifndef _FRAME_DRAW_H_
#define _FRAME_DRAW_H_
/*
 *  FRacing/lib/framebuffer/FrameBufferDraw.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * Frame buffer drawing library interface definitions.
 */

#include "config.h"

#include <string>

#include <FrameBufferBase.h>

union multiptr
{
	__u8 *p8;
	__u16 *p16;
	__u32 *p32;
};

class FrameBufferDraw : public FrameBufferBase
{
public:
	FrameBufferDraw(void);
	~FrameBufferDraw(void);

	void put_cross(int x, int y, unsigned int colidx);
	void put_char(int x, int y, int c, int colidx);
	void put_string(int x, int y, char *s, unsigned int colidx);
	void put_string_center(int x, int y, char *s, unsigned int colidx);

	void set_color(unsigned int colidx, unsigned value);
	void __set_pixel(union multiptr loc, unsigned int xormode, unsigned int color);
	void pixel(int x, int y, unsigned int colidx);
	void line(int x1, int y1, int x2, int y2, unsigned int colidx);

	void fill_rect(int x1, int y1, int x2, int y2, unsigned int colidx);
private:
	unsigned int color_map_[256];
};

#endif /* _FRAME_DRAW_H_ */

