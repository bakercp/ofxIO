//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


/// \brief Encodes and decodes bytes using Hexadecimal Binary encoding.
/// \sa http://en.wikipedia.org/wiki/Hexadecimal
class HexBinaryEncoding: public AbstractByteEncoderDecoder
{
public:
    /// \brief Create a HexBinary Encoding.
    HexBinaryEncoding();

    /// \brief Destroy a HexBinary Encoding.
    virtual ~HexBinaryEncoding();

    std::size_t encode(const ByteBuffer& buffer,
                       ByteBuffer& encodedBuffer) override;

    std::size_t decode(const ByteBuffer& buffer,
                       ByteBuffer& decodedBuffer) override;
    
};


} } // namespace ofx::IO
