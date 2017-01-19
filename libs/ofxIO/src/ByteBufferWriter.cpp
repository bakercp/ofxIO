//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/ByteBufferWriter.h"
#include <cstring>
#include <string.h>


namespace ofx {
namespace IO {


ByteBufferWriter::ByteBufferWriter(ByteBuffer& buffer, std::size_t offset):
    _buffer(buffer),
    _offset(offset)
{
}


std::size_t ByteBufferWriter::_write(const void* source, std::size_t size)
{
    if (_offset + size <= _buffer.size())
    {
        std::memcpy(_buffer.getPtr() + _offset, source, size);
        _offset += size;
        return size;
    }
    else
    {
        return 0;
    }
}


void ByteBufferWriter::setOffset(size_t offset)
{
    if (offset < _buffer.size()) _offset = offset;
}


std::size_t ByteBufferWriter::getOffset() const
{
    return _offset;
}


std::size_t ByteBufferWriter::size() const
{
    return _buffer.size();
}


std::size_t ByteBufferWriter::remaining() const
{
    return _buffer.size() - _offset;
}


} }  // namespace ofx::IO
