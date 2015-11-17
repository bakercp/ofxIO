// =============================================================================
//
// Copyright (c) 2015 Jean-Pierre Mouilleseaux <jpm@chordedconstructions.com>
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

/// \brief A Serial Line IP (SLIP) Encoder.
///
/// Serial Line IP (SLIP) is a packet framing protocol: SLIP defines a
/// sequence of characters that frame IP packets on a serial line, and
/// nothing more. It provides no addressing, packet type identification,
/// error detection/correction or compression mechanisms.  Because the
/// protocol does so little, though, it is usually very easy to
/// implement.
///
/// \sa http://tools.ietf.org/html/rfc1055
class SLIPEncoding: public AbstractByteEncoderDecoder
{
public:
    /// \brief Create a SLIPEncoding.
    SLIPEncoding();

    /// \brief Destroy a SLIPEncoding.
    virtual ~SLIPEncoding();

    bool encode(const AbstractByteSource& buffer,
                AbstractByteSink& encodedBuffer);

    bool decode(const AbstractByteSource& buffer,
                AbstractByteSink& decodedBuffer);

    /// \brief Encode a byte buffer with the SLIP encoder.
    /// \param buffer The buffer to encode.
    /// \param size The size of the buffer to encode.
    /// \param encodedBuffer The target buffer for the encoded bytes.
    /// \returns The number of bytes in the encoded buffer.
    /// \warning encodedBuffer must have a minimum capacity of
    ///     (2 * size + 2).
    static std::size_t encode(const uint8_t* buffer,
                              std::size_t size,
                              uint8_t* encodedBuffer);


    /// \brief Decode a SLIP-encoded buffer.
    /// \param buffer The SLIP-encoded buffer to decode.
    /// \param size The size of the SLIP-encoded buffer.
    /// \param decodedBuffer The target buffer for the decoded bytes.
    /// \returns The number of bytes in the decoded buffer.
    /// \warning decodedBuffer must have a minimum capacity of
    ///     (size - 1).
    static std::size_t decode(const uint8_t* buffer,
                              std::size_t size,
                              uint8_t* decodedBuffer);
    
};


} } // namespace ofx::IO
