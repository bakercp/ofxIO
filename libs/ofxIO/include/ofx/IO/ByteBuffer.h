// =============================================================================
//
// Copyright (c) 2013-2016 Christopher Baker <http://christopherbaker.net>
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
#include <sstream>
#include <iostream>
#include <algorithm>
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/ByteBufferUtils.h"


namespace ofx {
namespace IO {


/// \brief A flexible byte buffer.
///
/// The ByteBuffer is a backed by a std::vector of bytes.
class ByteBuffer: public AbstractByteSource, public AbstractByteSink
{
public:
    /// \brief Construct an empty ByteBuffer.
    ByteBuffer();

    /// \brief Construct a ByteBuffer a repeated byte.
    /// \param n The number of times to repeat the byte.
    /// \param data The a single byte to repeat.
    explicit ByteBuffer(std::size_t n, uint8_t data);

    /// \brief Construct a ByteBuffer with a single byte.
    /// \param data is a single inital byte.
    explicit ByteBuffer(uint8_t data);

    /// \brief Construct a ByteBuffer from a byte array.
    /// \param buffer is an array of bytes.
    /// \param size is the number of bytes in the buffer.
    explicit ByteBuffer(const char* buffer, std::size_t size);

    /// \brief Construct a ByteBuffer from a byte array.
    /// \param buffer is an array of bytes.
    /// \param size is the number of bytes in the buffer.
    explicit ByteBuffer(const uint8_t* buffer, std::size_t size);

    /// \brief Construct a ByteBuffer from a byte vector.
    /// \param buffer is a vector of bytes.
    explicit ByteBuffer(const std::vector<uint8_t>& buffer);

    /// \brief Construct a ByteBuffer from a string.
    /// \param buffer will be interpreted as raw bytes.
    explicit ByteBuffer(const std::string& buffer);

    /// \brief Construct a ByteBuffer from a byte source.
    /// \param buffer is a source of bytes.
    explicit ByteBuffer(const AbstractByteSource& buffer);

    /// \brief Destroy the ByteBuffer.
    virtual ~ByteBuffer();

    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size) const override;
    virtual std::size_t readBytes(std::vector<uint8_t>& buffer) const override;
    virtual std::size_t readBytes(std::string& buffer) const override;
    virtual std::size_t readBytes(AbstractByteSink& buffer) const override;
    virtual std::vector<uint8_t> readBytes() const override;

    virtual std::size_t writeByte(uint8_t data) override;
    virtual std::size_t writeBytes(const uint8_t* buffer, std::size_t size) override;
    virtual std::size_t writeBytes(const std::vector<uint8_t>& buffer) override;
    virtual std::size_t writeBytes(const std::string& buffer) override;
    virtual std::size_t writeBytes(const AbstractByteSource& buffer) override;

    /// \brief Query the number of bytes in the ByteBuffer.
    /// \returns the number of bytes in the ByteBuffer.
    std::size_t size() const override;

    /// \brief Query the capacity of the backing data vector.
    /// \returns the capacity of the backing data vector.
    std::size_t capacity() const;

    /// \brief Determine if the ByteBuffer is empty.
    /// \returns true iff the number of bytes in the ByteBuffer is 0.
    bool empty() const;

    /// \brief Clears all bytes from the ByteBuffer.
    void clear();

    /// \brief Resizes the ByteBuffer.
    /// \param size is the new size. If size is less than size(), the
    /// content is reduced to the first size elements.  If size is greater
    /// than size(), the new entries are filled with fillByte.
    /// \param fillByte is the value used to fill expanded buffer elements.
    /// \returns the new size of the ByteBuffer.
    std::size_t resize(std::size_t size, uint8_t fillByte = 0);

    /// \brief Ensures that the backing vector has allocated bytes.
    ///
    /// This simply pre-allocates needed bytes, which can speed up the copy
    /// process by reducing the number of reallocations and copies during large
    /// byte inserts or copies.
    ///
    /// \param capacity is the new capacity.
    /// \returns the new capacity of the ByteBuffer.
    std::size_t reserve(std::size_t capacity);

    /// \param n is the element index in the ByteBuffer.
    ///
    /// The value of n should not exceed size() - 1.
    ///
    /// \returns a reference to the byte at position n in the ByteBuffer.
    /// \note The first element has a position of 0 (not 1).
	uint8_t& operator [] (std::size_t n);

    /// \param n is the element index in the ByteBuffer.
    ///
    /// The value of n should not exceed size() - 1.
    ///
    /// \returns a copy of the byte at position n in the ByteBuffer.
    /// \note The first element has a position of 0 (not 1).
	uint8_t operator [] (std::size_t n) const;

    /// \brief Get a const reference to the backing data vector.
    /// \returns a const reference to the backing data vector.
    const std::vector<uint8_t>& getData() const;

    /// \brief Get a const pointer to the backing unsigned char data vector.
    /// \returns a const pointer to the backing data vector.
    const uint8_t* getPtr() const;

    /// \brief Get a pointer to the backing unsigned char data vector.
    /// \returns a pointer to the backing data vector.
    uint8_t* getPtr();

    /// \brief Get a const pointer to the char data vector.
    /// \returns a const pointer to the backing data vector.
    const char* getCharPtr() const;

    /// \brief Get a pointer to the char data vector.
    /// \returns a pointer to the backing data vector.
    char* getCharPtr();

    /// \brief get the ByteBuffer as a std::string with UTF-8 encoding.
    /// \returns the UTF-8-encoded std::string representation of the ByteBuffer.
    std::string toString() const;

    /// \brief get the ByteBuffer as a std::string UTF-8 encoding.
    /// \returns the UTF-8-encoded std::string representation of the ByteBuffer.
    std::string getText() const;

    /// \returns an iterator to the buffer.
    std::vector<uint8_t>::iterator begin();

    /// \returns a const iterator to the buffer.
    std::vector<uint8_t>::const_iterator begin() const;

    /// \returns an end iterator to the buffer.
    std::vector<uint8_t>::iterator end();

    /// \returns a const end iterator to the buffer.
    std::vector<uint8_t>::const_iterator end() const;

    /// \returns a reverse iterator to the buffer.
    std::vector<uint8_t>::reverse_iterator rbegin();

    /// \returns a const reverse iterator to the buffer.
    std::vector<uint8_t>::const_reverse_iterator rbegin() const;

    /// \returns a reverse end iterator to the buffer.
    std::vector<uint8_t>::reverse_iterator rend();

    /// \returns a const reverse end iterator to the buffer.
    std::vector<uint8_t>::const_reverse_iterator rend() const;

    /// \brief Remove all instances of the given byte.
    /// \param data The byte to remove.
    /// \returns the number of bytes replaced.
    void remove(uint8_t data);

    /// \brief Replace all instances of the given byte \data with \replacement.
    /// \param data The byte to replace.
    /// \param replacement The byte to use during replacement.
    /// \returns the number of bytes replaced.
    void replace(uint8_t data, uint8_t replacement);

    /// \brief Write the buffer to an output stream.
    /// \param ostr The std::ostream to write to.
    /// \param byteBuffer the ByteBuffer to write.
    /// \returns the std::ostream that was written to.
    friend std::ostream& operator << (std::ostream& ostr,
                                      const ByteBuffer& byteBuffer);

    /// \brief Read into the buffer from an input stream.
    /// \param istr The std::istream to read from.
    /// \param byteBuffer the ByteBuffer to read into.
    /// \returns the std::istream that was read from.
	friend std::istream& operator >> (std::istream& istr,
                                      ByteBuffer& byteBuffer);


private:
    /// \brief The backing byte buffer.
    std::vector<uint8_t> _buffer;

};


inline std::ostream& operator << (std::ostream& ostr,
                                  const ByteBuffer& byteBuffer)
{
    return ByteBufferUtils::copyBufferToStream(byteBuffer, ostr);
}


inline std::istream& operator >> (std::istream& istr, ByteBuffer& byteBuffer)
{
    ByteBufferUtils::copyStreamToBuffer(istr, byteBuffer);

    return istr;
}


} }  // namespace ofx::IO
