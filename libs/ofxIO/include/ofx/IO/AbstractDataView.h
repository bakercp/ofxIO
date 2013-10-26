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


#include <stdint.h>


namespace ofx {
namespace IO {


class AbstractDataView
{
public:
    AbstractDataView()
    {
    }

    virtual ~AbstractDataView()
    {
    }

    virtual std::size_t write(uint8_t data) = 0;
    virtual std::size_t write(uint16_t data) = 0;
    virtual std::size_t write(uint32_t data) = 0;
    virtual std::size_t write(uint64_t data) = 0;

    virtual std::size_t write(int8_t data) = 0;
    virtual std::size_t write(int16_t data) = 0;
    virtual std::size_t write(int32_t data) = 0;
    virtual std::size_t write(int64_t data) = 0;

    virtual std::size_t write(const uint8_t* data, std::size_t size) = 0;
    virtual std::size_t write(const uint16_t* data, std::size_t size) = 0;
    virtual std::size_t write(const uint32_t* data, std::size_t size) = 0;
    virtual std::size_t write(const uint64_t* data, std::size_t size) = 0;

    virtual std::size_t write(const int8_t* data, std::size_t size) = 0;
    virtual std::size_t write(const int16_t* data, std::size_t size) = 0;
    virtual std::size_t write(const int32_t* data, std::size_t size) = 0;
    virtual std::size_t write(const int64_t* data, std::size_t size) = 0;

    bool readUInt8(uint8_t& value) const = 0;
    bool readUInt16(uint16_t& value) const = 0;
    bool readUInt32(uint32_t& value) const = 0;
    bool readUInt64(uint64_t& value) const = 0;

    bool readInt8(int8_t& value) const = 0;
    bool readInt16(int16_t& value) const = 0;
    bool readInt32(int32_t& value) const = 0;
    bool readInt64(int64_t& value) const = 0;

    bool readUInt8(uint8_t* destination, std::size_t size) const = 0;
    bool readUInt16(uint16_t* destination, std::size_t size) const = 0;
    bool readUInt32(uint32_t* destination, std::size_t size) const = 0;
    bool readUInt64(uint64_t* destination, std::size_t size) const = 0;

    bool readInt8(int8_t* destination, std::size_t size) const = 0;
    bool readInt16(int16_t* destination, std::size_t size) const = 0;
    bool readInt32(int32_t* destination, std::size_t size) const = 0;
    bool readInt64(int64_t* destination, std::size_t size) const = 0;

};


} } // namespace ofx::IO
