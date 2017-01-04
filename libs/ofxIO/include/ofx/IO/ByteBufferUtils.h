//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <iostream>
#include <stdint.h>


namespace ofx {
namespace IO {


class ByteBuffer;


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
    ///
	/// Files are always opened in binary mode, a text mode with CR-LF
    /// translation is not supported. Thus, the file is always opened as if the
    /// std::ios::binary flag was specified. Use a
    /// Poco::InputLineEndingConverter if you require CR-LF translation.
    ///
    /// \param path The absolute path of the file to load.
    /// \param buffer the target ByteBuffer to fill.
    /// \param appendBuffer false if the ByteBuffer should be cleared.
    /// \param openMode the std::ios::in is always set.
    /// \returns The total number of bytes loaded.
    /// \throws A Poco::FileNotFoundException (or a similar exception) if the
    ///         file does not exist or is not accessible for other reasons.
    static std::streamsize loadFromFile(const std::string& path,
                                        ByteBuffer& buffer,
                                        bool appendBuffer = false,
                                        std::ios::openmode openMode = std::ios::in);


    /// \brief Save a ByteBuffer as a file.
    /// \param buffer the target ByteBuffer to save.
    /// \param path The absolute path of the file to save.
    /// \param mode The std::ios::out is always set, regardless of the
    ///        actual value specified for mode.
    /// \returns True iff the file was saved successfully.
    /// \throws A Poco::FileNotFoundException (or a similar exception) if the
    ///         file does not exist or is not accessible for other reasons.
    static bool saveToFile(const ByteBuffer& buffer,
                           const std::string& path,
                           std::ios::openmode mode = std::ios::out | std::ios::trunc);

    enum
    {
        /// \brief The default buffer size for use during buffered copies.
        DEFAULT_BUFFER_SIZE = 8192
    };

};


} } // ofx::IO
