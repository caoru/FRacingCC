/*
 *  FRacing/lib/gps/GPS.cpp
 *
 *  Copyright (C) 2015 Ikhyun Kim.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 *
 * GPS library interface implementtion.
 */

#include "config.h"

#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <GPS.h>

void io_handler(int status);

GPS::GPS(void)
	: device_()
{
    fd_ = -1;
    memset(&tio_, 0x00, sizeof(tio_));
}

GPS::GPS(std::string device, std::string baudrate)
    : device_(device),
    baudrate_str_(baudrate)

{
    fd_ = -1;
    memset(&tio_, 0x00, sizeof(tio_));

    this->baudrate(baudrate);
}

GPS::~GPS(void)
{
}

void GPS::device(std::string device)
{
    device_ = device;
}

std::string& GPS::device(void)
{
    return device_;
}

void GPS::baudrate(std::string baudrate)
{
    if (baudrate.empty())
        baudrate_ = B115200;
    else if (baudrate.compare("115200"))
        baudrate_ = B115200;
    else if (baudrate.compare("57600"))
        baudrate_ = B57600;
    else if (baudrate.compare("38400"))
        baudrate_ = B38400;
    else if (baudrate.compare("19200"))
        baudrate_ = B19200;
    else if (baudrate.compare("9600"))
        baudrate_ = B9600;
    else
        baudrate_ = B115200;
}

bool GPS::open(void)
{
    if (device_.empty())
            return false;

    fd_ = ::open(device_.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd_ == -1)
	{
		perror("open GPS device");
		return false;
	}

    saio_.sa_handler = io_handler;
    saio_.sa_flags = 0;
    saio_.sa_restorer = NULL; 
    sigaction(SIGIO, &saio_, NULL);

    fcntl(fd_, F_SETFL, FNDELAY);
    fcntl(fd_, F_SETOWN, getpid());
    fcntl(fd_, F_SETFL,  O_ASYNC );

    tcgetattr(fd_, &tio_);
    cfsetispeed(&tio_, baudrate_);
    cfsetospeed(&tio_, baudrate_);
    tio_.c_cflag &= ~PARENB;
    tio_.c_cflag &= ~CSTOPB;
    tio_.c_cflag &= ~CSIZE;
    tio_.c_cflag |= CS8;
    tio_.c_cflag |= (CLOCAL | CREAD);
    tio_.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tio_.c_iflag &= ~(IXON | IXOFF | IXANY);
    tio_.c_oflag &= ~OPOST;

    tcflush(fd_, TCIFLUSH);
    if (tcsetattr(fd_, TCSANOW, &tio_) < 0)
    {
		perror("tcsetattr");
        ::close(fd_);
        return false;
    }

    return true;
}

void GPS::close(void)
{
    ::close(fd_);
}

void io_handler(int status)
{
}

