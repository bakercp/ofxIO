// =============================================================================
//
// Copyright (c) 2010-2014 Christopher Baker <http://christopherbaker.net>
//
// Portions:
//  Copyright (c) 2011, Jacques Fortier. All rights reserved.
//  https://github.com/jacquesf/COBS-Consistent-Overhead-Byte-Stuffing
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
#include "ByteBuffer.h"


namespace ofx {
namespace IO {

/// COBS guarantees in the worst case to add no more than one byte in 254
/// to any packet.
/// \sa https://github.com/jacquesf/COBS-Consistent-Overhead-Byte-Stuffing
/// \sa http://www.jacquesf.com/2011/03/consistent-overhead-byte-stuffing/
class COBSEncoding: public AbstractByteEncoderDecoder
{
public:
    COBSEncoding();

    virtual ~COBSEncoding();

    bool encode(const AbstractByteSource& buffer,
                AbstractByteSink& encodedBuffer);

    bool decode(const AbstractByteSource& buffer,
                AbstractByteSink& decodedBuffer);
                
    /// Stuffs "size" bytes of data at the location pointed to by
    /// "src", writing the output to the location pointed to by
    /// "dest". Returns the number of bytes written to "dest".
    static std::size_t encode(const uint8_t* buffer,
                              std::size_t size,
                              uint8_t* encodedBuffer);


    /// Unstuffs "size" bytes of data at the location pointed to by
    /// "src", writing the output * to the location pointed to by
    /// "dest". Returns the number of bytes written to "dest" if
    /// "src" was successfully unstuffed, and 0 if there was an
    /// error unstuffing "src".
    static std::size_t decode(const uint8_t* buffer,
                              std::size_t size,
                              uint8_t* decodedBuffer);

};


} } // namespace ofx::IO
