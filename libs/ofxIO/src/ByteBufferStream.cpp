//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/ByteBufferStream.h"


namespace ofx {
namespace IO {


ByteBufferInputStreamBuf::ByteBufferInputStreamBuf(const ByteBuffer& buffer,
                                                   std::size_t offset):
    _bufferReader(buffer, offset)
{
}


ByteBufferInputStreamBuf::~ByteBufferInputStreamBuf()
{
}


int ByteBufferInputStreamBuf::readFromDevice()
{
    char byte;

    if (_bufferReader.read(byte) > 0)
    {
        return charToInt(byte);
    }
    else
    {
        return char_traits::eof();
    }
}


ByteBufferOutputStreamBuf::ByteBufferOutputStreamBuf(ByteBuffer& buffer):
    _buffer(buffer)
{
}


ByteBufferOutputStreamBuf::~ByteBufferOutputStreamBuf()
{
}


int ByteBufferOutputStreamBuf::writeToDevice(char byte)
{
    if (_buffer.writeByte(byte) > 0)
    {
        return charToInt(byte);
    }
    else
    {
        return char_traits::eof();
    }
}


} }  // namespace ofx::IO
