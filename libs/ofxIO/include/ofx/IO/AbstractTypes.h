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


#include <stdint.h>
#include <vector>
#include <string>
#include "Poco/File.h"


namespace ofx {
namespace IO {


class AbstractByteSink;
class AbstractBufferedByteSource;
class ByteBuffer;


class AbstractByteSource
{
public:
    AbstractByteSource()
    {
    }

    virtual ~AbstractByteSource()
    {
    }

    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size) const = 0;
    virtual std::size_t readBytes(std::vector<uint8_t>& buffer) const = 0;
    virtual std::size_t readBytes(std::string& buffer) const = 0;
    virtual std::size_t readBytes(ByteBuffer& buffer) const = 0;

};



class AbstractByteSink
{
public:
    AbstractByteSink()
    {
    }

    virtual ~AbstractByteSink()
    {
    }

    virtual std::size_t writeByte(uint8_t data) = 0;
    virtual std::size_t writeBytes(const uint8_t* buffer, std::size_t size) = 0;
    virtual std::size_t writeBytes(const std::vector<uint8_t>& buffer) = 0;
    virtual std::size_t writeBytes(const std::string& buffer) = 0;

};


class AbstractBufferedByteSource
{
public:
    AbstractBufferedByteSource()
    {
    }
    
    virtual ~AbstractBufferedByteSource()
    {
    }

    virtual std::size_t readByte(uint8_t& data) = 0;
    virtual std::size_t readBytes(uint8_t* buffer, std::size_t size) = 0;

    virtual std::size_t available() const = 0;
    
};


class AbstractFileFilter {
public:
    virtual ~AbstractFileFilter()
    {
    }
    
    virtual bool accept(const Poco::File& file) const = 0;
class AbstractSearchPath
    /// \brief Represents the abstract notion of a search path.
{
public:
    virtual ~AbstractSearchPath()
        ///< Destroys the resource.
    {
    }

    virtual bool isRecursive() const = 0;
        ///< \returns true iff this search path should be searched recursively.

    virtual Poco::Path getPath() const = 0;
        ///< \returns the base search path.
    
};


} } // namespace ofx::IO
