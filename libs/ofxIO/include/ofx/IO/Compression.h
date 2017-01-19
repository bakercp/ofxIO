//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include <stdint.h>
#include "ofx/IO/ByteBuffer.h"


namespace ofx {
namespace IO {


/// \brief A class for compressing and uncompressing ByteBuffers.
class Compression
{
public:
    enum Type
    {
        /// \brief Expect a zlib header, use Adler-32 checksum.
        ZLIB,
        /// \brief Expect a gzip header, use CRC-32 checksum.
		GZIP,
        /// \brief Use the snappy compression algorithm.
        SNAPPY,
        /// \brief Use the LZ4 compression algorithm.
        LZ4,
        /// \brief Use brotli compression algorithm.
        BR
    };

    /// \brief Uncompress a ByteBuffer.
    /// \param compressedBuffer The buffer compressed with `type` compression.
    /// \param uncompressedBuffer The buffer to fill with uncompressed bytes.
    /// \param type The compression Type.
    /// \returns the number of bytes uncompressed or 0 if error.
    static std::size_t uncompress(const ByteBuffer& compressedBuffer,
                                  ByteBuffer& uncompressedBuffer,
                                  Type type);

    /// \brief Uncomress a ByteBuffer using Type::ZLIB.
    /// \param compressedBuffer The compressed buffer.
    /// \param uncompressedBuffer The empty buffer to decompress with `zlib`.
    /// \param windowBits See deflateInit2() for more informtion.
    ///                   Must be in range (8 - 15) inclusive.
    /// \returns the number of bytes uncompressed or 0 if error.
    /// \sa http://www.zlib.net/manual.html
    static std::size_t uncompress(const ByteBuffer& compressedBuffer,
                                  ByteBuffer& uncompressedBuffer,
                                  int windowBits);

    /// \brief Compress a ByteBuffer.
    /// \param uncompressedBuffer The buffer to compress with `type` compression.
    /// \param compressedBuffer The buffer to fill with compressed bytes.
    /// \param type The compression Type.
    /// \returns the number of compressed bytes or 0 if error.
    static std::size_t compress(const ByteBuffer& uncompressedBuffer,
                                ByteBuffer& compressedBuffer,
                                Type type);

    /// \brief Compress a ByteBuffer.
    /// \param uncompressedBuffer The buffer to compress with `type` compression.
    /// \param compressedBuffer The buffer to fill with compressed bytes.
    /// \param type The compression Type.
    /// \param level The compression level (1 - 8) inclusive.
    ///        Only valid for Type::ZLIB and Type::GZIP.
    /// \returns the number of compressed bytes or 0 if error.
    /// \sa http://www.zlib.net/manual.html
    static std::size_t compress(const ByteBuffer& uncompressedBuffer,
                                ByteBuffer& compressedBuffer,
                                Type type,
                                int level);

    /// \brief Compress a ByteBuffer using Type::ZLIB.
    /// \param uncompressedBuffer The buffer to compress with `zlib` compression.
    /// \param compressedBuffer The buffer to fill with compressed bytes.
    /// \param windowBits See deflateInit2() for more informtion.
    ///                   Must be in range (8 - 15) inclusive.
    /// \param level The compression level (1 - 8) inclusive.
    /// \returns the number of compressed bytes or 0 if error.
    /// \sa http://www.zlib.net/manual.html
    static std::size_t compress(const ByteBuffer& uncompressedBuffer,
                                ByteBuffer& compressedBuffer,
                                int windowBits,
                                int level);

    /// \brief Query the string representation of the compression lib version.
    /// \param type The compression type.
    /// \returns the string representation of the compression lib version.
    static std::string version(Type type);

    /// \brief Query the string representation of the compression type.
    /// \param type The compression type.
    /// \returns the string representation of the compression type.
    static std::string toString(Type type);

};


} } // namespace ofx::IO
