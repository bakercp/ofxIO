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


/// \brief Encodes and decodes bytes using Base64 encoding.
/// \sa http://en.wikipedia.org/wiki/Base64
class Base64Encoding: public AbstractByteEncoderDecoder
{
public:
    /// \brief Create a Base64 Encoding.
    /// \param urlSafe Use URL safe en/de coding. Replace `+` with `-` and `/` with `_`.
    /// \param isChunked When encoding, output line breaks.
    /// \param paddedOutput When encoding, pad the output with = to align to byte boundaries.
    Base64Encoding(bool urlSafe = false,
                   bool isChunked = false,
                   bool paddedOutput = false);

    /// \brief Destroy the Base64 Encoding.
    virtual ~Base64Encoding();

    std::size_t encode(const ByteBuffer& buffer,
                       ByteBuffer& encodedBuffer) override;

    std::size_t decode(const ByteBuffer& buffer,
                       ByteBuffer& decodedBuffer) override;

    /// \brief A base64 encoder for strings.
    /// \param buffer The UTF8 encoded string to be encoded.
    /// \param isUrlSafe Make URL safe by replacing `+` with `-` and `/` with `_`.
    /// \param isChunked Will wrap encoded output by adding line breaks.
    /// \param isPadded Pad the output with = to align to byte boundaries.
    /// \returns a base64 encoded UTF-8 std::string.
    static std::string encode(const std::string& buffer,
                              bool isUrlSafe = false,
                              bool isChunked = false,
                              bool isPadded = false);

    /// \brief A base64 encoder for byte buffers.
    /// \param buffer The Byte buffer to be encoded.
    /// \param isUrlSafe Make URL safe by replacing `+` with `-` and `/` with `_`.
    /// \param isChunked Will wrap encoded output by adding line breaks.
    /// \param isPadded Pad the output with = to align to byte boundaries.
    /// \returns a base64 encoded UTF-8 std::string.
    static std::string encode(const ByteBuffer& buffer,
                              bool isUrlSafe = false,
                              bool isChunked = false,
                              bool isPadded = false);

    /// \brief A base64 decoder for strings.
    ///
    /// Will pad with `=` if needed and remove chunking.
    ///
    /// \param buffer The string to decoded.
    /// \param isUrlSafe Decode URL safe by replacing `-` with `+` and `_` with `/`.
    /// \returns a base64 decoded UTF-8 std::string.
    static std::string decode(const std::string& buffer,
                              bool isUrlSafe = false);


    /// \returns true if the en/decoding is URL safe.
    bool isUrlSafe() const;

    /// \returns true if the output is chunked.
    bool isChunked() const;

    /// \returns true if the output is padded with = to align to byte boundaries.
    bool isPadded() const;

private:
    /// \brief Use URL safe en/decoding. Replace `+` with `-` and `/` with `_`.
    bool _isUrlSafe = false;

    /// \brief When encoding, output line breaks.
    bool _isChunked = false;

    /// \brief When encoding, pad the output with = to align to byte boundaries.
    bool _isPadded = false;

};


} } // namespace ofx::IO
