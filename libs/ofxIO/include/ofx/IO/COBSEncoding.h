//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// Portions:
//  Copyright (c) 2011, Jacques Fortier. All rights reserved.
//  https://github.com/jacquesf/COBS-Consistent-Overhead-Byte-Stuffing
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <stdint.h>
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/ByteBuffer.h"


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
    virtual ~COBSEncoding() override;

    std::size_t encode(const ByteBuffer& buffer,
                       ByteBuffer& encodedBuffer) override;

    std::size_t decode(const ByteBuffer& buffer,
                       ByteBuffer& decodedBuffer) override;

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
    ///     size.
    static std::size_t decode(const uint8_t* buffer,
                              std::size_t size,
                              uint8_t* decodedBuffer);

};


} } // namespace ofx::IO
