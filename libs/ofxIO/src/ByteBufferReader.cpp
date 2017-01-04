//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/ByteBufferReader.h"
#include <cstring>
#include <string.h>


namespace ofx {
namespace IO {


ByteBufferReader::ByteBufferReader(const ByteBuffer& buffer, std::size_t offset):
    _buffer(buffer),
    _offset(offset)
{
}


std::size_t ByteBufferReader::_read(void* destination, std::size_t size) const
{
    if (_offset + size <= _buffer.size())
    {
        std::memcpy(destination, _buffer.getPtr() + _offset, size);
        _offset += size;
        return size;
    }
    else
    {
        return 0;
    }
}


void ByteBufferReader::setOffset(std::size_t offset)
{
    if (offset < _buffer.size()) _offset = offset;
}


void ByteBufferReader::skip(std::size_t offset)
{
    if (_offset + offset < _buffer.size()) _offset += offset;
}


std::size_t ByteBufferReader::getOffset() const
{
    return _offset;
}


std::size_t ByteBufferReader::size() const
{
    return _buffer.size();
}


std::size_t ByteBufferReader::remaining() const
{
    return _buffer.size() - _offset;
}


} }  // namespace ofx::IO
