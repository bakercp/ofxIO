//
// Copyright (c) 2010 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <type_traits>
#include "ofx/IO/ByteBuffer.h"


namespace ofx {
namespace IO {


/// \brief An interface for writing data of various byte widths.
class ByteBufferWriter
{
public:
    /// \brief Create a ByteBufferWriter.
    /// \param buffer A reference to a ByteBuffer to write into.
    /// \param offset The offset to write from.
    ByteBufferWriter(ByteBuffer& buffer, std::size_t offset = 0);

    /// \brief Write a single data into the ByteBuffer.
    ///
    /// This function accepts "Plain Old Data" types and uses the sizeof()
    /// function to determine how many raw bytes should be written into the
    /// ByteBuffer.
    ///
    /// Will return 0 on write error (e.g. no room available in the ByteBuffer).
    ///
    /// \param data The data to write.
    /// \returns The number of bytes written.
    /// \tparam Type The data type to write.
    template <typename Type>
    std::size_t write(const Type& data);

    /// \brief Write a data array into the ByteBuffer.
    ///
    /// This function accepts "Plain Old Data" types and uses the sizeof()
    /// function to determine how many raw bytes should be written into the
    /// ByteBuffer.
    ///
    /// Will return 0 on write error (e.g. no room available in the ByteBuffer).
    ///
    /// \param data The data array to write.
    /// \param size The length of the array.
    /// \returns The number of bytes written.
    /// \tparam Type The data type to write.
    template <typename Type>
    std::size_t write(const Type* data, std::size_t size);

    /// \brief Set the write offset to a given byte.
    ///
    /// Will set the offset past the end of the buffer.
    ///
    /// \offset The byte offset to set.
    void setOffset(std::size_t offset);

    /// \returns Get the current write offset.
    std::size_t getOffset() const;

    /// \returns The size of the buffer (i.e. buffer.size()).
    std::size_t size() const;

    /// \returns the number of bytes remaining (i.e. buffer.size() - getOffset()).
    std::size_t remaining() const;

private:
    ByteBufferWriter(const ByteBufferWriter& that) = delete;
    ByteBufferWriter& operator = (const ByteBufferWriter& that) = delete;

    /// \brief The proxy writer function.
    /// \param source The byte source.
    /// \param size The number of bytes to write.
    /// \returns The number of bytes written.
    std::size_t _write(const void* source, std::size_t size);

    /// \brief A reference to the target buffer.
    ByteBuffer& _buffer;

    /// \brief The current write offset.
    std::size_t _offset;
    
};


template <typename Type>
std::size_t ByteBufferWriter::write(const Type& data)
{
    static_assert(std::is_pod<Type>::value, "Type must be POD.");
    return _write(&data, sizeof(Type));
}


template <typename Type>
std::size_t ByteBufferWriter::write(const Type* data, std::size_t size)
{
    static_assert(std::is_pod<Type>::value, "Type must be POD.");
    return _write(data, sizeof(Type) * size);
}


} } // namespace ofx::IO
