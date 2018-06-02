//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/URIEncoding.h"
#include "ofx/IO/ByteBuffer.h"
#include "Poco/URI.h"


namespace ofx {
namespace IO {


URIEncoding::URIEncoding()
{
}


URIEncoding::~URIEncoding()
{
}


std::size_t URIEncoding::encode(const ByteBuffer& buffer,
                                ByteBuffer& encodedBuffer)
{
    std::string encoded;
    Poco::URI::encode(buffer.toString(), "", encoded);
    encodedBuffer = ByteBuffer(encoded);
    return encodedBuffer.size();
}


std::size_t URIEncoding::decode(const ByteBuffer& buffer,
                                ByteBuffer& decodedBuffer)
{
    std::string decoded;
    Poco::URI::decode(buffer.toString(), decoded);
    decodedBuffer = ByteBuffer(decoded);
    return decodedBuffer.size();
}


std::string URIEncoding::encode(const std::string& buffer,
                                const std::string& reserved)
{
    std::string encoded;
    Poco::URI::encode(buffer, reserved, encoded);
    return encoded;
}


std::string URIEncoding::decode(const std::string& buffer, bool plusAsSpace)
{
    std::string decoded;
    Poco::URI::decode(buffer, decoded, plusAsSpace);
    return decoded;
}


} }  // namespace ofx::IO
