// =============================================================================
//
// Copyright (c) 2013-2015 Christopher Baker <http://christopherbaker.net>
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
