// =============================================================================
//
// Copyright (c) 2010-2016 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


/// \brief Encodes and decodes bytes using URI encoding.
///
/// URI encoding is also known as URL encoding or "percent" encoding.
///
/// \sa http://www.w3schools.com/tags/ref_urlencode.asp
class URIEncoding: public AbstractByteEncoderDecoder
{
public:
    /// \brief Create a URI Encoding.
    URIEncoding();

    /// \brief Destroy the URI Encoding.
    virtual ~URIEncoding();

    std::size_t encode(const ByteBuffer& buffer,
                       ByteBuffer& encodedBuffer) override;

    std::size_t decode(const ByteBuffer& buffer,
                       ByteBuffer& decodedBuffer) override;

    /// \brief A URI encoder for strings.
    /// \param buffer The string to encoded.
    /// \param reserved Reserved charachters that will also be encoded.
    /// \returns a URI encoded std::string.
    static std::string encode(const std::string& buffer,
                              const std::string& reserved = "");

    /// \brief A URI decoder for strings.
    /// \param buffer The string to decoded.
    /// \param plusAsSpace When true, non-encoded plus signs in the query are
    ///        decoded as spaces.
    /// \returns a URI decoded std::string.
    /// \sa http://www.w3.org/TR/html401/interact/forms.html#h-17.13.4.1
    static std::string decode(const std::string& buffer,
                              bool plusAsSpace = false);

};


} } // namespace ofx::IO
