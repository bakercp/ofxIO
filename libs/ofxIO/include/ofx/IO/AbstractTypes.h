//
// Copyright (c) 2010 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <stdint.h>
#include <vector>
#include <string>
#include "Poco/File.h"


namespace ofx {
namespace IO {


class AbstractByteSink;
class AbstractBufferedByteSource;
class ByteBuffer;


/// \brief Represents the abstract notion of a byte source.
///
/// An AbstractByteSource has bytes that can be read.
class AbstractByteSource
{
public:
    /// \brief Destroys the byte source.
    virtual ~AbstractByteSource()
    {
    }

    /// \brief Read bytes from this source into a target buffer.
    /// \param buffer is the target buffer to be filled with bytes.
    /// \param size is the number of bytes to be written into the
    ///        target buffer.
    /// \returns the number of bytes that were successfully
    ///        written into the target buffer.
    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size) const = 0;

    /// \brief Read bytes from this source into a target buffer.
    /// \param buffer is the target buffer to be filled with bytes.
    /// \returns the number of bytes that were successfully
    ///        written into the target buffer.
    virtual std::size_t readBytes(std::vector<uint8_t>& buffer) const = 0;

    /// \brief Read bytes from this source into a target buffer.
    /// \param buffer is the target buffer to be filled with bytes.
    /// \returns the number of bytes that were successfully
    ///        written into the target buffer.
    virtual std::size_t readBytes(std::string& buffer) const = 0;

    /// \brief Read bytes from this source into a target buffer.
    /// \param buffer is the target buffer to be filled with bytes.
    /// \returns the number of bytes that were successfully
    ///        written into the target buffer.
    virtual std::size_t readBytes(AbstractByteSink& buffer) const = 0;

    /// \brief Return a copy of all bytes from this source.
    /// \returns the contents of the byte source as a vector of bytes.
    virtual std::vector<uint8_t> readBytes() const = 0;

    /// \returns the number of bytes available to read.
    virtual std::size_t size() const = 0;

};


/// \brief Represents the abstract notion of a byte sink.
///
/// An AbstractByteSink can receive bytes written from various sources.
class AbstractByteSink
{
public:
    /// \brief Destroys the byte sink.
    virtual ~AbstractByteSink()
    {
    }

    /// \brief Write a single byte into this byte sink.
    /// \param data is the single byte to be written into this byte sink.
    /// \returns the number of bytes that were successfully
    ///        written into this byte sink.
    virtual std::size_t writeByte(uint8_t data) = 0;

    /// \brief Write the contents of the buffer into this byte sink.
    /// \param buffer is the array of bytes to be written to this byte sink.
    /// \param size is the number of bytes in the buffer.
    /// \returns the number of bytes that were successfully
    ///        written into this byte sink.
    virtual std::size_t writeBytes(const uint8_t* buffer, std::size_t size) = 0;

    /// \brief Write the contents of the buffer into this byte sink.
    /// \param buffer is the array of bytes to be written to this byte sink.
    /// \returns the number of bytes that were successfully
    ///        written into this byte sink.
    virtual std::size_t writeBytes(const std::vector<uint8_t>& buffer) = 0;

    /// \brief Write the contents of the buffer into this byte sink.
    /// \param buffer is the array of bytes to be written to this byte sink.
    /// \returns the number of bytes that were successfully
    ///        written into this byte sink.
    virtual std::size_t writeBytes(const std::string& buffer) = 0;

    /// \brief Write the contents of the buffer into this byte sink.
    /// \param buffer is the array of bytes to be written to this byte sink.
    /// \returns the number of bytes that were successfully
    ///        written into this byte sink.
    virtual std::size_t writeBytes(const AbstractByteSource& buffer) = 0;

};


/// \brief Represents the abstract notion a buffered byte source.
///
/// An AbstractBufferedByteSource is consumed as it is read.
class AbstractBufferedByteSource
{
public:
    /// \brief Destroys the buffered byte source.
    virtual ~AbstractBufferedByteSource()
    {
    }

    /// \brief Read a single byte from this source into the
    ///        referenced variable.
    /// \param data is referenced variable to be filled.
    /// \returns the number of bytes that were successfully
    ///        written into the referenced data variable.  The maxium
    ///        return value is 1.
    virtual std::size_t readByte(uint8_t& data) = 0;

    /// \brief Read bytes from this source into a target buffer.
    /// \param buffer is the target buffer to be filled with bytes.
    /// \param size is the number of bytes to be written into the
    ///        target buffer.
    /// \returns the number of bytes that were successfully
    ///        written into the target buffer.
    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size) = 0;

    /// \brief Query the number of buffered bytes.
    /// \returns the number of bytes available to be read.
    virtual std::size_t available() const = 0;

};


/// \brief Represents the abstract notion of a byte encoder.
///
/// Subclasses implementing this interface can a collection of bytes and return
/// the encoded version of those bytes.
class AbstractByteEncoder
{
public:
    /// \brief Destroys the byte encoder.
    virtual ~AbstractByteEncoder()
    {
    }

    /// \brief Encode the contents of the buffer.
    /// \param buffer is the array of bytes to be encoded.
    /// \param encodedBuffer the target buffer.
    /// \returns the number of encoded bytes or 0 if error.
    virtual std::size_t encode(const ByteBuffer& buffer,
                               ByteBuffer& encodedBuffer) = 0;

};


/// \brief Represents the abstract notion of a byte decoder.
///
/// Subclasses implementing this interface can a collection of encoded bytes and
/// return the decoded version of those bytes.
class AbstractByteDecoder
{
public:
    /// \brief Destroys the byte decoder.
    virtual ~AbstractByteDecoder()
    {
    }

    /// \brief Decode the contents of the buffer.
    /// \param buffer is the array of bytes to be decoded.
    /// \param decodedBuffer the target buffer.
    /// \returns the number of decoded bytes or 0 if error.
    virtual std::size_t decode(const ByteBuffer& buffer,
                               ByteBuffer& decodedBuffer) = 0;
                        
};


/// \brief Represents the abstract notion of a byte encoder / decoder.
class AbstractByteEncoderDecoder:
    virtual public AbstractByteDecoder,
    virtual public AbstractByteEncoder
{
public:
    /// \brief Destroys the byte encoder / decoder.
    virtual ~AbstractByteEncoderDecoder()
    {
    }

};


/// \brief Represents the abstract notion of a path filter.
///
/// Subclasses implementing this interface can accept files based on a criteria
/// defined in the accept() method.
class AbstractPathFilter
{
public:
    /// \brief Destroys the path filter.
    virtual ~AbstractPathFilter()
    {
    }
    
    /// \brief Accept a path based on a defined criteria.
    /// \returns true iff the path is accepted by the path filter.
    virtual bool accept(const Poco::Path& path) const = 0;
    
};


/// \brief Represents the abstract notion of a search path.
class AbstractSearchPath
{
public:
    /// \brief Destroys the resource.
    virtual ~AbstractSearchPath()
    {
    }

    /// \brief Get true if the search path is recursive.
    /// \returns true iff this search path should be searched recursively.
    virtual bool isRecursive() const = 0;

    /// \brief Get the path for this search path.
    /// \returns the search path.
    virtual Poco::Path getPath() const = 0;

};


class AbstractInputStreamFilter
{
public:
    virtual ~AbstractInputStreamFilter()
    {
    }

    virtual std::istream& filter(std::istream& stream) = 0;
};


class AbstractOutputStreamFilter
{
public:
    virtual ~AbstractOutputStreamFilter()
    {
    }

    virtual std::ostream& filter(std::ostream& stream) = 0;
};


} } // namespace ofx::IO
