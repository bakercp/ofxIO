//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <ostream>
#include <cctype>
#include "Poco/UnbufferedStreamBuf.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/IO/ByteBufferReader.h"
#include "ofx/IO/ByteBufferWriter.h"


namespace ofx {
namespace IO {


class ByteBufferInputStreamBuf: public Poco::UnbufferedStreamBuf
{
public:
    ByteBufferInputStreamBuf(const ByteBuffer& buffer, std::size_t offset = 0);
    
    virtual ~ByteBufferInputStreamBuf();

protected:
    int readFromDevice() override;

private:
    ByteBufferReader _bufferReader;

};


class ByteBufferInputIOS: public virtual std::ios
{
public:
    ByteBufferInputIOS(const ByteBuffer& buffer, std::size_t offset = 0):
        _buf(buffer, offset)
    {
        poco_ios_init(&_buf);
    }

protected:
    ByteBufferInputStreamBuf _buf;

};


class ByteBufferInputStream: public ByteBufferInputIOS, public std::istream
{
public:
    ByteBufferInputStream(const ByteBuffer& buffer, std::size_t offset = 0):
        ByteBufferInputIOS(buffer, offset),
        std::istream(&_buf)
    {
    }
};


class ByteBufferOutputStreamBuf: public Poco::UnbufferedStreamBuf
{
public:
    ByteBufferOutputStreamBuf(ByteBuffer& buffer);

    virtual ~ByteBufferOutputStreamBuf();

protected:
    int writeToDevice(char byte) override;

private:
    ByteBuffer& _buffer;
    
};


class ByteBufferOutputIOS: public virtual std::ios
{
public:
    ByteBufferOutputIOS(ByteBuffer& buffer): _buf(buffer)
    {
        poco_ios_init(&_buf);
    }

protected:
    ByteBufferOutputStreamBuf _buf;

};


class ByteBufferOutputStream: public ByteBufferOutputIOS, public std::ostream
{
public:
    ByteBufferOutputStream(ByteBuffer& buffer):
        ByteBufferOutputIOS(buffer),
        std::ostream(&_buf)
    {
    }
};


} } // namespace ofx::IO
