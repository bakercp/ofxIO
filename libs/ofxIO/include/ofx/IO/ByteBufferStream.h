// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


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
