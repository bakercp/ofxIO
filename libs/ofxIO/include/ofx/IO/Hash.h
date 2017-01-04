//
// Copyright (c) 2009 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <functional>
#include <string>
#include "Poco/DigestStream.h"
#include "Poco/Exception.h"
#include "Poco/MD5Engine.h"
#include "Poco/SHA1Engine.h"
#include "Poco/Crypto/RSAKey.h"
#include "Poco/Crypto/RSADigestEngine.h"
#include "ofFileUtils.h"

#include "ofx/IO/ByteBuffer.h"

namespace ofx {
namespace IO {


class Hash
{
public:
    /// \brief Combine multiple hashes.
    ///
    /// The order of combining hases will affect the final hash value. This uses
    /// std::hash to hash the value, so it is good for being a unique key for
    /// hash tables, but it is not meant for cryptographic hashing.
    ///
    /// \param seed The existing hash to amend.
    /// \param v The value to hash and amend.
    /// \tparam The type of the value to hash and amend.
    /// \sa http://stackoverflow.com/a/2595226/1518329
    template <class T>
    static void combine(std::size_t& seed, const T& v)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <typename BufferType>
    static std::string sha256(const BufferType& image)
    {
        Poco::Crypto::RSAKey key(Poco::Crypto::RSAKey::KL_2048,
                                 Poco::Crypto::RSAKey::EXP_LARGE);
        Poco::Crypto::RSADigestEngine eng(key, "SHA256");

        // "MD5", "SHA1", "SHA256", "SHA512"

        eng.update(image.getData(), image.size());
        const auto& sig = eng.digest(); // We just want the digest, unsigned.
        return Poco::DigestEngine::digestToHex(sig);
    }

    template <typename BufferType>
    static std::string sha1(const BufferType& buffer)
    {
        Poco::SHA1Engine sha1;
        sha1.update(buffer.getData(), buffer.size());
        const auto& digest = sha1.digest(); // obtain result
        return Poco::DigestEngine::digestToHex(digest);
    }

    template <typename BufferType>
    static std::string md5(const BufferType& buffer)
    {
        Poco::MD5Engine md5;
        md5.update(buffer.getData(), buffer.size());
        const auto& digest = md5.digest(); // obtain result
        return Poco::DigestEngine::digestToHex(digest);
    }

};



} } // namespace ofx::IO
