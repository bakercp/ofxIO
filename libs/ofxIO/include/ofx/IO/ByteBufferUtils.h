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


#include "ofx/IO/ByteBuffer.h"


namespace ofx {
namespace IO {


/// \brief Utilities for use with ByteBuffer.
class ByteBufferUtils
{
public:
    /// \brief Create a ByteBuffer from two bytes.
    /// \param d0 is the first byte.
    /// \param d1 is the second byte.
    /// \returns a new ByteBuffer.
    static ByteBuffer makeBuffer(uint8_t d0,
                                 uint8_t d1);

    /// \brief Create a ByteBuffer from three bytes.
    /// \param d0 is the first byte.
    /// \param d1 is the second byte.
    /// \param d2 is the third byte.
    /// \returns a new ByteBuffer.
    static ByteBuffer makeBuffer(uint8_t d0,
                                 uint8_t d1,
                                 uint8_t d2);

    /// \brief Create a ByteBuffer from four bytes.
    /// \param d0 is the first byte.
    /// \param d1 is the second byte.
    /// \param d2 is the third byte.
    /// \param d3 is the fouth byte.
    /// \returns a new ByteBuffer.
    static ByteBuffer makeBuffer(uint8_t d0,
                                 uint8_t d1,
                                 uint8_t d2,
                                 uint8_t d3);

    /// \brief Create a ByteBuffer from five bytes.
    /// \param d0 is the first byte.
    /// \param d1 is the second byte.
    /// \param d2 is the third byte.
    /// \param d3 is the fouth byte.
    /// \param d4 is the fifth byte.
    /// \returns a new ByteBuffer.
    static ByteBuffer makeBuffer(uint8_t d0,
                                 uint8_t d1,
                                 uint8_t d2,
                                 uint8_t d3,
                                 uint8_t d4);

    /// \brief Create a ByteBuffer from an input stream.
    /// \param istr The std::istream input stream.
    /// \param bufferSize The size of the buffer used during copy.
    /// \returns A new ByteBuffer with the contents of the input stream.
    static ByteBuffer makeBuffer(std::istream& istr,
                                 std::size_t bufferSize = DEFAULT_BUFFER_SIZE);

    /// \brief Copy an input stream to a ByteBuffer.
    /// \param istr The std::istream input stream.
    /// \param byteBuffer the target ByteBuffer.
    /// \param bufferSize The size of the buffer used during copy.
    /// \returns The total number of bytes copied into the ByteBuffer.
    static std::streamsize copyStreamToBuffer(std::istream& istr,
                                              ByteBuffer& byteBuffer,
                                              std::size_t bufferSize = DEFAULT_BUFFER_SIZE);

    /// \brief Copy a ByteBuffer to an output stream.
    /// \param byteBuffer the ByteBuffer to copy.
    /// \param ostr the target output stream.
    /// \returns The passed output stream.
    static std::ostream& copyBufferToStream(const ByteBuffer& byteBuffer,
                                            std::ostream& ostr);

    /// \brief Load a ByteBuffer from a file.
    /// \path The absolute path of the file to load.
    /// \param byteBuffer the target ByteBuffer to fill.
    /// \param append false if the ByteBuffer should be cleared.
    /// \returns The total number of bytes loaded.
    /// \throws A Poco::FileNotFoundException (or a similar exception) if the
    ///         file does not exist or is not accessible for other reasons.
    static std::streamsize loadFromFile(const std::string& path,
                                        ByteBuffer& buffer,
                                        bool appendBuffer = false);

    /// \brief Save a ByteBuffer as a file.
    /// \param byteBuffer the target ByteBuffer to save.
    /// \path The absolute path of the file to save.
    /// \param append false if the ByteBuffer should be cleared.
    /// \returns True iff the file was saved successfully.
    /// \throws A Poco::FileNotFoundException (or a similar exception) if the
    ///         file does not exist or is not accessible for other reasons.
    static bool saveToFile(const ByteBuffer& buffer,
                           const std::string& path);

    enum
    {
        /// \brief The default buffer size for use during buffered copies.
        DEFAULT_BUFFER_SIZE = 8192
    };

};


} } // ofx::IO
