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

/// \brief A Consistent Overhead Byte Stuffing (COBS) Encoder.
///
/// Consistent Overhead Byte Stuffing (COBS) is an encoding that removes all 0
/// bytes from arbitrary binary data. The encoded data consists only of bytes
/// with values from 0x01 to 0xFF. This is useful for preparing data for
/// transmission over a serial link (RS-232 or RS-485 for example), as the 0
/// byte can be used to unambiguously indicate packet boundaries. COBS also has
/// the advantage of adding very little overhead (at least 1 byte, plus up to an
/// additional byte per 254 bytes of data). For messages smaller than 254 bytes,
/// the overhead is constant.
///
/// (via http://www.jacquesf.com/2011/03/consistent-overhead-byte-stuffing/)
///
/// \sa http://conferences.sigcomm.org/sigcomm/1997/papers/p062.pdf
/// \sa http://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing
/// \sa https://github.com/jacquesf/COBS-Consistent-Overhead-Byte-Stuffing
/// \sa http://www.jacquesf.com/2011/03/consistent-overhead-byte-stuffing/
class COBSEncoding: public AbstractByteEncoderDecoder
{
public:
    /// \brief Create a COBSEncoding.
    COBSEncoding();

    /// \brief Destroy a COBSEncoding.
    virtual ~COBSEncoding();

    bool encode(const AbstractByteSource& buffer,
                AbstractByteSink& encodedBuffer);

    bool decode(const AbstractByteSource& buffer,
                AbstractByteSink& decodedBuffer);

    /// \brief Encode a byte buffer with the COBS encoder.
    /// \param buffer The buffer to encode.
    /// \param size The size of the buffer to encode.
    /// \param encodedBuffer The target buffer for the encoded bytes.
    /// \returns The number of bytes in the encoded buffer.
    /// \warning encodedBuffer must have a minimum capacity of
    ///     (size + size / 254 + 1).
    static std::size_t encode(const uint8_t* buffer,
                              std::size_t size,
                              uint8_t* encodedBuffer);


    /// \brief Decode a COBS-encoded buffer.
    /// \param buffer The COBS-encoded buffer to decode.
    /// \param size The size of the COBS-encoded buffer.
    /// \param decodedBuffer The target buffer for the decoded bytes.
    /// \returns The number of bytes in the decoded buffer.
    /// \warning decodedBuffer must have a minimum capacity of
    ///     size
    static std::size_t decode(const uint8_t* buffer,
                              std::size_t size,
                              uint8_t* decodedBuffer);

};


} } // namespace ofx::IO
