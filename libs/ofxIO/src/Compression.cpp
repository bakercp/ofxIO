// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/IO/Compression.h"
#include "Poco/Buffer.h"
#include "Poco/DeflatingStream.h"
#include "Poco/InflatingStream.h"
#include "snappy.h"
#include "lz4.h"
#include "ofLog.h"


namespace ofx {
namespace IO {


std::size_t Compression::uncompress(const ByteBuffer& compressedBuffer,
                                    ByteBuffer& uncompressedBuffer,
                                    Type type)
{

    switch (type)
    {
        case ZLIB:
            ofLogWarning("Compression::uncompress") << "Not implemented.";
            return 0;
        case GZIP:
            ofLogWarning("Compression::uncompress") << "Not implemented.";
            return 0;
        case ZIP:
            ofLogWarning("Compression::uncompress") << "Not implemented.";
            return 0;
        case SNAPPY:
        {
            std::size_t size = 0;

            if (snappy::GetUncompressedLength(compressedBuffer.getCharPtr(),
                                              compressedBuffer.size(),
                                              &size))
            {
                uncompressedBuffer.resize(size);

                if (snappy::RawUncompress(compressedBuffer.getCharPtr(),
                                          compressedBuffer.size(),
                                          uncompressedBuffer.getCharPtr()))
                {
                    return size;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        case LZ4:
        {
            // TODO: Abritrary 4 x buffer.
            uncompressedBuffer.resize(compressedBuffer.size() * 4);

            int result = LZ4_decompress_safe(compressedBuffer.getCharPtr(),
                                             uncompressedBuffer.getCharPtr(),
                                             compressedBuffer.size(),
                                             uncompressedBuffer.size());

            if (result >= 0)
            {
                uncompressedBuffer.resize(result);
                return result;
            }
            else
            {
                return 0;
            }
        }
    }
}


std::size_t Compression::compress(const ByteBuffer& uncompressedBuffer,
                                  ByteBuffer& compressedBuffer,
                                  Type type)
{
    std::size_t size = 0;

    // Reserve as many as needed.
    compressedBuffer.resize(uncompressedBuffer.size());

    switch (type)
    {
        case ZLIB:
            ofLogWarning("Compression::compress") << "Not implemented.";
            break;
        case GZIP:
            ofLogWarning("Compression::compress") << "Not implemented.";
            break;
        case ZIP:
            ofLogWarning("Compression::compress") << "Not implemented.";
            break;
        case SNAPPY:
        {
            snappy::RawCompress(uncompressedBuffer.getCharPtr(),
                                uncompressedBuffer.size(),
                                compressedBuffer.getCharPtr(),
                                &size);
            break;
        }
        case LZ4:
        {
            size = LZ4_compress(uncompressedBuffer.getCharPtr(),
                                compressedBuffer.getCharPtr(),
                                uncompressedBuffer.size());
            break;
        }
    }

    compressedBuffer.resize(size);

    return size;
}


std::string Compression::version(Type type)
{
    switch (type)
    {
        case ZLIB:
            ofLogWarning("Compression::version") << "Not implemented.";
            return "?";
        case GZIP:
            ofLogWarning("Compression::version") << "Not implemented.";
            return "?";
        case ZIP:
            ofLogWarning("Compression::version") << "Not implemented.";
            return "?";
        case SNAPPY:
        {
            std::stringstream ss;
            ss << SNAPPY_MAJOR << "." << SNAPPY_MINOR << "." << SNAPPY_PATCHLEVEL;
            return ss.str();
        }
        case LZ4:
        {
            std::stringstream ss;
            ss << LZ4_VERSION_MAJOR << "." << LZ4_VERSION_MINOR << "." << LZ4_VERSION_RELEASE;
            return ss.str();
        }
        default:
            return "UNKNOWN";
    }

}

std::string Compression::toString(Type type)
{
    switch (type)
    {
        case ZLIB:
            return "ZLIB";
        case GZIP:
            return "GZIP";
        case ZIP:
            return "ZIP";
        case SNAPPY:
            return "SNAPPY";
        case LZ4:
            return "LZ4";
        default:
            return "UNKNOWN";
    }
}



} }  // namespace ofx::IO
