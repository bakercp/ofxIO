//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/HexBinaryEncoding.h"
#include <stdint.h>
#include "Poco/HexBinaryEncoder.h"
#include "Poco/HexBinaryDecoder.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/IO/ByteBufferStream.h"


namespace ofx {
namespace IO {


HexBinaryEncoding::HexBinaryEncoding()
{
}


HexBinaryEncoding::~HexBinaryEncoding()
{
}


std::size_t HexBinaryEncoding::encode(const ByteBuffer& buffer,
                                      ByteBuffer& encodedBuffer)
{
    encodedBuffer.clear();
    ByteBufferOutputStream os(encodedBuffer);
    Poco::HexBinaryEncoder _encoder(os);
    ByteBufferUtils::copyBufferToStream(buffer, _encoder);
    _encoder.close(); // Flush bytes.
    return encodedBuffer.size();
}

std::size_t HexBinaryEncoding::decode(const ByteBuffer& buffer,
                                      ByteBuffer& decodedBuffer)
{
    decodedBuffer.clear();
    ByteBufferInputStream is(buffer);
    Poco::HexBinaryDecoder _decoder(is);
    return ByteBufferUtils::copyStreamToBuffer(_decoder, decodedBuffer);
}


} }  // namespace ofx::IO
