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

#if __cplusplus>=201103L
#include <type_traits>
#else
#include <tr1/type_traits>
namespace std {
	using std::tr1::is_pod;
}
#endif
// http://stackoverflow.com/questions/19154080/restricting-c-template-usage-to-pod-types


#include "ofx/IO/ByteBuffer.h"


namespace ofx {
namespace IO {


/// \brief An interface for reading and writing data of various byte widths.
class ByteBufferWriter
{
public:
    ByteBufferWriter(ByteBuffer& buffer, std::size_t offset = 0);

    template <typename Type>
    std::size_t write(const Type& data);

    template <typename Type>
    std::size_t write(const Type* data, std::size_t size);

    void setOffset(std::size_t offset);
    std::size_t getOffset() const;

    std::size_t size() const;

    std::size_t remaining() const;

private:
    ByteBufferWriter(const ByteBufferWriter& that);
    ByteBufferWriter& operator = (const ByteBufferWriter& that);

    std::size_t _write(const void* source, std::size_t size);

    ByteBuffer& _buffer;

    std::size_t _offset;
    
};


template <typename Type>
std::size_t ByteBufferWriter::write(const Type& data)
{
    static char Type_must_be_pod[std::is_pod<Type>::value ? 1 : -1];
    return _write(&data, sizeof(Type));
}


template <typename Type>
std::size_t ByteBufferWriter::write(const Type* data, std::size_t size)
{
    static char Type_must_be_pod[std::is_pod<Type>::value ? 1 : -1];
    return _write(data, sizeof(Type) * size);
}


} } // namespace ofx::IO
