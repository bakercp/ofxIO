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
    /// \brief create a byte buffer from two bytes.
    /// \param d0 is the first byte.
    /// \param d1 is the second byte.
    /// \returns a new ByteBuffer.
    static ByteBuffer makeBuffer(uint8_t d0,
                                 uint8_t d1);

    /// \brief create a byte buffer from three bytes.
    /// \param d0 is the first byte.
    /// \param d1 is the second byte.
    /// \param d2 is the third byte.
    /// \returns a new ByteBuffer.
    static ByteBuffer makeBuffer(uint8_t d0,
                                 uint8_t d1,
                                 uint8_t d2);

    /// \brief create a byte buffer from four bytes.
    /// \param d0 is the first byte.
    /// \param d1 is the second byte.
    /// \param d2 is the third byte.
    /// \param d3 is the fouth byte.
    /// \returns a new ByteBuffer.
    static ByteBuffer makeBuffer(uint8_t d0,
                                 uint8_t d1,
                                 uint8_t d2,
                                 uint8_t d3);

    /// \brief create a byte buffer from five bytes.
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

};


} } // ofx::IO
