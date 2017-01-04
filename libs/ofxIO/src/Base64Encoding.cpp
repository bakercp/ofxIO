//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/Base64Encoding.h"
#include <stdint.h>
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/String.h"
#include "Poco/StreamCopier.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/IO/ByteBufferStream.h"


namespace ofx {
namespace IO {


Base64Encoding::Base64Encoding(bool isUrlSafe,
                               bool isChunked,
                               bool isPadded):
    _isUrlSafe(isUrlSafe),
    _isChunked(isChunked),
    _isPadded(isPadded)
{
}


Base64Encoding::~Base64Encoding()
{
}


std::size_t Base64Encoding::encode(const ByteBuffer& buffer,
                                   ByteBuffer& encodedBuffer)
{
    encodedBuffer.clear();
    ByteBufferOutputStream os(encodedBuffer);
    Poco::Base64Encoder _encoder(os);

    ByteBufferUtils::copyBufferToStream(buffer, _encoder);

    _encoder.close(); // Flush bytes.

    if (!_isPadded)
    {
        encodedBuffer.remove('=');
    }

    if (!_isChunked)
    {
        encodedBuffer.remove('\r');
        encodedBuffer.remove('\n');
    }

    if (_isUrlSafe)
    {
        encodedBuffer.replace('+', '-');
        encodedBuffer.replace('/', '_');
    }

    return encodedBuffer.size();
}

std::size_t Base64Encoding::decode(const ByteBuffer& buffer,
                                   ByteBuffer& decodedBuffer)
{
    ByteBuffer _buffer(buffer);
    decodedBuffer.clear();

    if (_isUrlSafe)
    {
        _buffer.replace('-', '+');
        _buffer.replace('_', '/');
    }

    std::size_t m4 = (_buffer.size() % 4);

    if (m4 != 0)
    {
        _buffer.writeBytes(ByteBuffer(4 - m4, '='));
    }

    ByteBufferInputStream is(_buffer);

    Poco::Base64Decoder _decoder(is);

    return ByteBufferUtils::copyStreamToBuffer(_decoder, decodedBuffer);
}


std::string Base64Encoding::encode(const std::string& buffer,
                                   bool isUrlSafe,
                                   bool isChunked,
                                   bool isPadded)
{
    return encode(ByteBuffer(buffer), isUrlSafe, isChunked, isPadded);
}


std::string Base64Encoding::encode(const ByteBuffer& buffer,
                                   bool isUrlSafe,
                                   bool isChunked,
                                   bool isPadded)
{
    Base64Encoding encoder(isUrlSafe, isChunked, isPadded);
    ByteBuffer _output;
    encoder.encode(buffer, _output);
    return _output.toString();
}



std::string Base64Encoding::decode(const std::string& buffer, bool isUrlSafe)
{
    ByteBuffer _buffer(buffer);
    ByteBuffer output;
    Base64Encoding decoder(isUrlSafe);
    decoder.decode(_buffer, output);
    return output.toString();
}


bool Base64Encoding::isUrlSafe() const
{
    return _isUrlSafe;
}


bool Base64Encoding::isChunked() const
{
    return _isChunked;
}


bool Base64Encoding::isPadded() const
{
    return _isPadded;
}


} }  // namespace ofx::IO
