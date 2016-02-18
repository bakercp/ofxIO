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
        LZ4
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
