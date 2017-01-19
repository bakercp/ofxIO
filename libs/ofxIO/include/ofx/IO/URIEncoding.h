//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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
