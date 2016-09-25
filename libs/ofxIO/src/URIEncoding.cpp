// =============================================================================
//
// Copyright (c) 2013-2016 Christopher Baker <http://christopherbaker.net>
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
