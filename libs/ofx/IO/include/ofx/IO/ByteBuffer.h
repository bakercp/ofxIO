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


#pragma once


#include <vector>
#include <string>
#include <iostream>
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


class ByteBuffer: public AbstractByteSource, public AbstractByteSink
{
public:
    ByteBuffer();
    explicit ByteBuffer(const std::string& buffer);
    explicit ByteBuffer(const AbstractByteSource& buffer);
    explicit ByteBuffer(const std::vector<uint8_t>& buffer);
    explicit ByteBuffer(const uint8_t* buffer, std::size_t size);

    virtual ~ByteBuffer();

    std::size_t readBytes(std::string& buffer) const;
    std::size_t readBytes(AbstractByteSink& buffer) const;
    std::size_t readBytes(std::vector<uint8_t>& buffer) const;
    std::size_t readBytes(uint8_t* buffer, std::size_t size) const;
    std::vector<uint8_t> readBytes() const;

    std::size_t writeByte(uint8_t data);
    std::size_t writeBytes(const std::string& buffer);
    std::size_t writeBytes(const AbstractByteSource& buffer);
    std::size_t writeBytes(const std::vector<uint8_t>& buffer);
    std::size_t writeBytes(const uint8_t* buffer, std::size_t size);

    std::size_t size() const;
    bool empty() const;
    void clear();

    std::size_t resize(std::size_t size);

	uint8_t& operator [] (std::size_t n);
	uint8_t operator [] (std::size_t n) const;

    const std::vector<uint8_t>& getDataRef() const;
    const uint8_t* getDataPtr() const;

    friend std::ostream& operator << (std::ostream& os, const ByteBuffer& vec);

private:
    std::vector<uint8_t> _buffer;

};


inline std::ostream& operator << (std::ostream& os, const ByteBuffer& buffer)
{
    std::vector<uint8_t>::const_iterator iter = buffer._buffer.begin();
    while(iter != buffer._buffer.end())
    {
        os << (int)*iter; // cast to int so interpreted as numbers, not chars
        ++iter;
        if(iter != buffer._buffer.end())
        {
            os << " ";
        }
    }
    return os;
}


} }  // namespace ofx::IO
