#ifndef _GPS_H_
#define _GPS_H_
/*
 *  FRacing/lib/gps/GPS.h
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * GPS library interface definitions.
 */

#include "config.h"

#include <iostream>
#include <signal.h>

class GPS
{
public:
	GPS(void);
    GPS(std::string device, std::string baudrate);
	~GPS(void);

	void device(std::string device);
	std::string& device(void);

    void baudrate(std::string baudrate);

    bool open(void);
    void close(void);

private:
    std::string device_;
    int fd_;
    struct termios tio_;
    std::string baudrate_str_;
    speed_t baudrate_;
    struct sigaction saio_;

};

#endif /* _GPS_H */

