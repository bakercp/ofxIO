//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


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


ByteBuffer::ByteBuffer(std::initializer_list<uint8_t> data)
{
    reserve(data.size());

    for (auto& byte: data)
    {
        writeByte(byte);
    }
}


ByteBuffer::ByteBuffer(std::size_t n, uint8_t data)
{
    reserve(n);
    
    for (std::size_t i = 0; i < n; ++i)
    {
        writeByte(data);
    }
}


ByteBuffer::ByteBuffer(uint8_t data)
{
    writeByte(data);
}


ByteBuffer::ByteBuffer(const char* buffer, std::size_t size)
{
    writeBytes(reinterpret_cast<const uint8_t*>(buffer), size);
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


ByteBuffer::ByteBuffer(std::istream& istr, std::size_t bufferSize)
{
    ByteBufferUtils::copyStreamToBuffer(istr, *this, bufferSize);
}

    
ByteBuffer::~ByteBuffer()
{
}


std::size_t ByteBuffer::readBytes(uint8_t* buffer, std::size_t size) const
{
    std::size_t numBytesToCopy = std::min(size, _buffer.size());
    std::copy(_buffer.begin(), _buffer.begin() + static_cast<ptrdiff_t>(numBytesToCopy), buffer);
    return numBytesToCopy;
}


std::size_t ByteBuffer::readBytes(std::vector<uint8_t>& buffer) const
{
    buffer.clear();
    buffer.insert(buffer.begin(), _buffer.begin(), _buffer.end());
    return buffer.size();
}


std::size_t ByteBuffer::readBytes(std::string& buffer) const
{
    buffer.clear();
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


std::size_t ByteBuffer::writeBytes(std::initializer_list<uint8_t> bytes)
{
    std::vector<uint8_t> buffer = bytes;
    return writeBytes(buffer);
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


std::size_t ByteBuffer::writeBytes(std::istream& istr, std::size_t bufferSize)
{
    return ByteBufferUtils::copyStreamToBuffer(istr, *this, bufferSize);
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

    
const std::vector<uint8_t>& ByteBuffer::getBuffer() const
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
        return nullptr;
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
        return nullptr;
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
        return nullptr;
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
        return nullptr;
    }
}


const char* ByteBuffer::getData() const
{
    return getCharPtr();
}


char* ByteBuffer::getData()
{
    return getCharPtr();
}


std::string ByteBuffer::toString() const
{
    std::string s;
    readBytes(s);
    return s;
}


std::string ByteBuffer::getText() const
{
    return toString();
}


std::vector<uint8_t>::iterator ByteBuffer::begin()
{
    return _buffer.begin();
}


std::vector<uint8_t>::const_iterator ByteBuffer::begin() const
{
    return _buffer.begin();
}


std::vector<uint8_t>::iterator ByteBuffer::end()
{
    return _buffer.end();
}


std::vector<uint8_t>::const_iterator ByteBuffer::end() const
{
    return _buffer.end();
}


std::vector<uint8_t>::reverse_iterator ByteBuffer::rbegin()
{
    return _buffer.rbegin();
}


std::vector<uint8_t>::const_reverse_iterator ByteBuffer::rbegin() const
{
    return _buffer.rbegin();
}


std::vector<uint8_t>::reverse_iterator ByteBuffer::rend()
{
    return _buffer.rend();
}


std::vector<uint8_t>::const_reverse_iterator ByteBuffer::rend() const
{
    return _buffer.rend();
}


void ByteBuffer::remove(uint8_t data)
{
    _buffer.erase(std::remove(_buffer.begin(),
                              _buffer.end(),
                              data),
                  _buffer.end());
}


void ByteBuffer::replace(uint8_t data, uint8_t replacement)
{
    std::replace(_buffer.begin(), _buffer.end(), data, replacement);
}


} }  // namespace ofx::IO
