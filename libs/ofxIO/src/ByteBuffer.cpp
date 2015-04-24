// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/IO/ByteBuffer.h"


#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif


namespace ofx {
namespace IO {

    
ByteBuffer::ByteBuffer()
{
}


ByteBuffer::ByteBuffer(uint8_t data)
{
    writeByte(data);
}


ByteBuffer::ByteBuffer(const uint8_t* buffer, std::size_t size)
{
    writeBytes(buffer, size);
}


ByteBuffer::ByteBuffer(const std::vector<uint8_t>& buffer)
{
    writeBytes(buffer);
}


ByteBuffer::ByteBuffer(const std::string& buffer)
{
    writeBytes(buffer);
}

    
ByteBuffer::~ByteBuffer()
{
}


std::size_t ByteBuffer::readBytes(uint8_t* buffer, std::size_t size) const
{
    std::size_t numBytesToCopy = std::min(size, _buffer.size());
    std::copy(_buffer.begin(), _buffer.begin() + numBytesToCopy, buffer);
    return numBytesToCopy;
}


std::size_t ByteBuffer::readBytes(std::vector<uint8_t>& buffer) const
{
    buffer.resize(_buffer.size());
    buffer.insert(buffer.begin(), _buffer.begin(), _buffer.end());
    return buffer.size();
}


std::size_t ByteBuffer::readBytes(std::string& buffer) const
{
    buffer.resize(_buffer.size());
    buffer.insert(buffer.begin(), _buffer.begin(), _buffer.end());
    return buffer.size();
}


std::size_t ByteBuffer::readBytes(AbstractByteSink& buffer) const
{
    return buffer.writeBytes(_buffer);
}


std::vector<uint8_t> ByteBuffer::readBytes() const
{
    return _buffer;
}


std::size_t ByteBuffer::writeByte(uint8_t data)
{
    _buffer.push_back(data);
    return 1;
}


std::size_t ByteBuffer::writeBytes(const uint8_t* buffer, std::size_t size)
{
    _buffer.reserve(_buffer.size() + size);
    _buffer.insert(_buffer.end(), buffer, buffer + size);
    return size;
}


std::size_t ByteBuffer::writeBytes(const std::vector<uint8_t>& buffer)
{
    _buffer.reserve(_buffer.size() + buffer.size());
    _buffer.insert(_buffer.end(), buffer.begin(), buffer.end());
    return buffer.size();
}


std::size_t ByteBuffer::writeBytes(const std::string& buffer)
{
    _buffer.reserve(_buffer.size() + buffer.size());
    _buffer.insert(_buffer.end(), buffer.begin(), buffer.end());
    return buffer.size();
}


std::size_t ByteBuffer::writeBytes(const AbstractByteSource& buffer)
{
    return writeBytes(buffer.readBytes());
}


std::size_t ByteBuffer::size() const
{
    return _buffer.size();
}


std::size_t ByteBuffer::capacity() const
{
    return _buffer.capacity();
}


void ByteBuffer::clear()
{
    _buffer.clear();
}


bool ByteBuffer::empty() const
{
    return _buffer.empty();
}


std::size_t ByteBuffer::resize(std::size_t size, uint8_t fillByte)
{
    _buffer.resize(size, fillByte);
    return _buffer.size();
}


std::size_t ByteBuffer::reserve(std::size_t capacity)
{
    _buffer.reserve(capacity);
    return _buffer.capacity();
}

    
const std::vector<uint8_t>& ByteBuffer::getData() const
{
    return _buffer;
}


uint8_t& ByteBuffer::operator [] (std::size_t n)
{
    return _buffer[n];
}


uint8_t ByteBuffer::operator [] (std::size_t n) const
{
    return _buffer[n];
}
    

const uint8_t* ByteBuffer::getPtr() const
{
    if (!_buffer.empty())
    {
        return &_buffer[0];
    }
    else
    {
        return 0;
    }
}


uint8_t* ByteBuffer::getPtr()
{
    if (!_buffer.empty())
    {
        return &_buffer[0];
    }
    else
    {
        return 0;
    }
}


const char* ByteBuffer::getCharPtr() const
{
    if (!_buffer.empty())
    {
        return reinterpret_cast<const char*>(&_buffer[0]);
    }
    else
    {
        return 0;
    }
}


char* ByteBuffer::getCharPtr()
{
    if (!_buffer.empty())
    {
        return reinterpret_cast<char*>(&_buffer[0]);
    }
    else
    {
        return 0;
    }
}

std::string ByteBuffer::toString() const
{
    std::stringstream ss;
    ss << (*this);
    return ss.str();
}



} }  // namespace ofx::IO
