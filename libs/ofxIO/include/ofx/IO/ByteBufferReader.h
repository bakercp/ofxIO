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


#if (_MSC_VER) || defined(__EMSCRIPTEN__)
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


class ByteBufferReader
{
public:
    ByteBufferReader(const ByteBuffer& buffer, std::size_t offset = 0);

    template <typename Type>
    std::size_t read(Type& value) const;

    template <typename Type>
    std::size_t read(Type* destination, std::size_t size) const;

    void setOffset(std::size_t offset);

    std::size_t getOffset() const;

    std::size_t size() const;

    std::size_t remaining() const;

private:
    ByteBufferReader(const ByteBufferReader& that);
    ByteBufferReader& operator = (const ByteBufferReader& that);

    std::size_t _read(void* destination, size_t size) const;

    const ByteBuffer& _buffer;

    mutable std::size_t _offset;

};


template <typename Type>
std::size_t ByteBufferReader::read(Type& value) const
{
    static char Type_must_be_pod[std::is_pod<Type>::value ? 1 : -1];
    return _read(&value, sizeof(Type));
}


template <typename Type>
std::size_t ByteBufferReader::read(Type* destination, std::size_t size) const
{   
    static char Type_must_be_pod[std::is_pod<Type>::value ? 1 : -1];
    return _read(destination, sizeof(Type) * size);
}


} } // namespace ofx::IO
