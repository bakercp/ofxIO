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
    /// \brief A flexible byte buffer.
    /// \details The ByteBuffer is a backed by a std::vector of bytes.
{
public:
    ByteBuffer();
        ///< \brief Construct an empty ByteBuffer.

    explicit ByteBuffer(uint8_t data);
        ///< \brief Construct a ByteBuffer with a single byte.
        ///< \param data is a single inital byte.

    explicit ByteBuffer(const uint8_t* buffer, std::size_t size);
        ///< \brief Construct a ByteBuffer from a byte array.
        ///< \param buffer is an array of bytes.
        ///< \param size is the number of bytes in the buffer.

    explicit ByteBuffer(const std::vector<uint8_t>& buffer);
        ///< \brief Construct a ByteBuffer from a byte vector.
        ///< \param buffer is a vector of bytes.

    explicit ByteBuffer(const std::string& buffer);
        ///< \brief Construct a ByteBuffer from a string.
        ///< \param buffer will be interpreted as raw bytes.

    explicit ByteBuffer(const AbstractByteSource& buffer);
        ///< \brief Construct a ByteBuffer from a byte source.
        ///< \param buffer is a source of bytes.

    virtual ~ByteBuffer();
        ///< \brief Destroy a ByteBuffer.

    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size) const;
    virtual std::size_t readBytes(std::vector<uint8_t>& buffer) const;
    virtual std::size_t readBytes(std::string& buffer) const;
    virtual std::size_t readBytes(AbstractByteSink& buffer) const;
    virtual std::vector<uint8_t> readBytes() const;

    virtual std::size_t writeByte(uint8_t data);
    virtual std::size_t writeBytes(const uint8_t* buffer, std::size_t size);
    virtual std::size_t writeBytes(const std::vector<uint8_t>& buffer);
    virtual std::size_t writeBytes(const std::string& buffer);
    virtual std::size_t writeBytes(const AbstractByteSource& buffer);

    std::size_t size() const;
        ///< \returns the number of bytes in the ByteBuffer.

    bool empty() const;
        ///< \returns true iff the number of bytes in the ByteBuffer is 0.

    void clear();
        ///< \brief Clears all bytes from the ByteBuffer.

    std::size_t resize(std::size_t size, uint8_t fillByte = 0);
        ///< \brief Resizes the ByteBuffer.
        ///< \param size is the new size. If size is less than size(), the
        ///< content is reduced to the first size elements.  If size is greater
        ///< than size(), the new entries are filled with fillByte.
        ///< \param fillByte is the value used to fill expanded buffer elements.
        ///< \returns the new size of the ByteBuffer.

    // slice();

	uint8_t& operator [] (std::size_t n);
        ///< \param n is the element index in the ByteBuffer.
        ///< The value of n should not exceed size() - 1.
        ///< \returns a reference to the byte at position n in the ByteBuffer.
        ///< \note The first element has a position of 0 (not 1).

	uint8_t operator [] (std::size_t n) const;
        ///< \param n is the element index in the ByteBuffer.
        ///< The value of n should not exceed size() - 1.
        ///< \returns a copy of the byte at position n in the ByteBuffer.
        ///< \note The first element has a position of 0 (not 1).

    const std::vector<uint8_t>& getDataRef() const;
        ///< \returns a const reference to the backing data vector.

    const uint8_t* getDataPtr() const;
        ///< \returns a const pointer to the backing data vector.

    friend std::ostream& operator << (std::ostream& os, const ByteBuffer& buffer);

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
