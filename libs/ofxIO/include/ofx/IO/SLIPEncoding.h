//
// Copyright (c) 2015 Christopher Baker <https://christopherbaker.net>
//
// Portions:
//  Copyright (c) 2015 Jean-Pierre Mouilleseaux <jpm@chordedconstructions.com>
//
// SPDX-License-Identifier:    MIT
//

#pragma once


#include <stdint.h>
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/ByteBuffer.h"


namespace ofx {
namespace IO {


/// \brief A Serial Line IP (SLIP) Encoder.
///
/// Serial Line IP (SLIP) is a packet framing protocol: SLIP defines a
/// sequence of characters that frame IP packets on a serial line and
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

    std::size_t encode(const ByteBuffer& buffer,
                       ByteBuffer& encodedBuffer) override;

    std::size_t decode(const ByteBuffer& buffer,
                ByteBuffer& decodedBuffer) override;

    /// \brief Encode a byte buffer with the SLIP encoder.
    /// \param buffer The buffer to encode.
    /// \param size The size of the buffer to encode.
    /// \param encodedBuffer The target buffer for the encoded bytes.
    /// \returns The number of bytes in the encoded buffer.
    /// \warning encodedBuffer must have a minimum capacity of (2 * size + 2).
    static std::size_t encode(const uint8_t* buffer,
                              std::size_t size,
                              uint8_t* encodedBuffer);


    /// \brief Decode a SLIP-encoded buffer.
    /// \param buffer The SLIP-encoded buffer to decode.
    /// \param size The size of the SLIP-encoded buffer.
    /// \param decodedBuffer The target buffer for the decoded bytes.
    /// \returns The number of bytes in the decoded buffer.
    /// \warning decodedBuffer must have a minimum capacity of (size - 1).
    static std::size_t decode(const uint8_t* buffer,
                              std::size_t size,
                              uint8_t* decodedBuffer);

    /// \brief A collection of key values for SLIP encoding.
    enum
    {
        END = 0300,
        ESC = 0333,
        ESC_END = 0334,
        ESC_ESC = 0335
    };

};


} } // namespace ofx::IO
