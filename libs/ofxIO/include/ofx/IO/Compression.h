// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
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
#include "Poco/InflatingStream.h"
#include "Poco/DeflatingStream.h"
#include "ofx/IO/ByteBuffer.h"


namespace ofx {
namespace IO {


class Compression
{
public:
    enum Type
    {
//        /// \brief Expect a zlib header, use Adler-32 checksum.
//        ZLIB = Poco::InflatingStreamBuf::STREAM_ZLIB,
//
//        /// \brief Expect a gzip header, use CRC-32 checksum.
//		GZIP = Poco::InflatingStreamBuf::STREAM_GZIP,
//
//        /// \brief STREAM_ZIP is handled as STREAM_ZLIB,
//        /// except that we do not check the ADLER32 value (must be checked by caller)
//		ZIP = Poco::InflatingStreamBuf::STREAM_ZIP,
//
        /// \brief Use the snappy compression algorithm.
        SNAPPY,

        /// \brief Use the LZ4 compression algorithm .
        LZ4
    };

    static std::size_t uncompress(const ByteBuffer& compressedBuffer,
                                  ByteBuffer& uncompressedBuffer,
                                  Type type);

    static std::size_t compress(const ByteBuffer& uncompressedBuffer,
                                ByteBuffer& compressedBuffer,
                                Type type);

};


} } // namespace ofx::IO
