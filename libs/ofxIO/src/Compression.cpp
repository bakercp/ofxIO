// =============================================================================
//
// Copyright (c) 2013-2015 Christopher Baker <http://christopherbaker.net>
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
#include "ofx/IO/ByteBufferStream.h"
#include "Poco/Buffer.h"
#include "Poco/DeflatingStream.h"
#include "Poco/InflatingStream.h"
#include "Poco/Version.h"
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
        case GZIP:
        case ZLIB:
        {
            Poco::InflatingStreamBuf::StreamType streamType;

            if (type == ZLIB)
            {
                streamType = Poco::InflatingStreamBuf::StreamType::STREAM_ZLIB;
            }
            else if (type == GZIP)
            {
                streamType = Poco::InflatingStreamBuf::StreamType::STREAM_GZIP;
            }

            try
            {
                uncompressedBuffer.clear();
                uncompressedBuffer.reserve(compressedBuffer.size() * 4);
                ByteBufferInputStream istr(compressedBuffer);
                Poco::InflatingInputStream inflater(istr, streamType);
                inflater >> uncompressedBuffer;
                return uncompressedBuffer.size();
            }
            catch (const Poco::Exception& exc)
            {
                ofLogError("Compression::uncompress") << exc.displayText();
                return 0;
            }
        }
        case Type::SNAPPY:
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
        case Type::LZ4:
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
    switch (type)
    {
        case ZLIB:
        case GZIP:
        {
            return compress(uncompressedBuffer,
                            compressedBuffer,
                            type,
                            Z_DEFAULT_COMPRESSION);
        }
        case SNAPPY:
        {
            std::size_t size = 0;
            // Allocate as many as needed.
            compressedBuffer.resize(uncompressedBuffer.size());
            snappy::RawCompress(uncompressedBuffer.getCharPtr(),
                                uncompressedBuffer.size(),
                                compressedBuffer.getCharPtr(),
                                &size);
            compressedBuffer.resize(size);
            return size;
        }
        case LZ4:
        {
            std::size_t size = 0;
            // Allocate as many as needed.
            compressedBuffer.resize(uncompressedBuffer.size());
            size = LZ4_compress(uncompressedBuffer.getCharPtr(),
                                compressedBuffer.getCharPtr(),
                                uncompressedBuffer.size());
            compressedBuffer.resize(size);
            return size;
        }
    }
}


std::size_t Compression::compress(const ByteBuffer& uncompressedBuffer,
                                  ByteBuffer& compressedBuffer,
                                  Type type,
                                  int level)
{
    Poco::DeflatingStreamBuf::StreamType streamType;

    if (type == ZLIB)
    {
        streamType = Poco::DeflatingStreamBuf::STREAM_ZLIB;
    }
    else if (type == GZIP)
    {
        streamType = Poco::DeflatingStreamBuf::STREAM_GZIP;
    }
    else
    {
        ofLogWarning("Compression::compress") << "Ignoring 'level' for type: " << toString(type);
        return compress(uncompressedBuffer, compressedBuffer, type);
    }

    try
    {
        compressedBuffer.clear();
        compressedBuffer.reserve(uncompressedBuffer.size());

        ByteBufferOutputStream ostr(compressedBuffer);
        Poco::DeflatingOutputStream deflater(ostr, streamType, level);
        deflater << uncompressedBuffer;
        deflater.close();

        return compressedBuffer.size();
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("Compression::compress") << exc.displayText();
        return 0;
    }
}


std::size_t Compression::compress(const ByteBuffer& uncompressedBuffer,
                                  ByteBuffer& compressedBuffer,
                                  int windowBits,
                                  int level)
{
    try
    {
        compressedBuffer.clear();
        compressedBuffer.reserve(uncompressedBuffer.size());

        ByteBufferOutputStream ostr(compressedBuffer);

        Poco::DeflatingOutputStream deflater(ostr, windowBits, level);

        deflater << uncompressedBuffer;
        deflater.close();

        return compressedBuffer.size();
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("Compression::uncompress") << exc.displayText();
        return 0;
    }
}


std::size_t Compression::uncompress(const ByteBuffer& compressedBuffer,
                                    ByteBuffer& uncompressedBuffer,
                                    int windowBits)
{
    try
    {
        uncompressedBuffer.clear();
        uncompressedBuffer.reserve(compressedBuffer.size() * 4);
        ByteBufferInputStream istr(compressedBuffer);
        Poco::InflatingInputStream inflater(istr, windowBits);
        inflater >> uncompressedBuffer;
        return uncompressedBuffer.size();
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("Compression::uncompress") << exc.displayText();
        return 0;
    }
}


std::string Compression::version(Type type)
{
    switch (type)
    {
        case ZLIB:
        case GZIP:
        {
            std::stringstream ss;
            ss << "POCO_";
            ss << POCO_VERSION;
            return ss.str();
        }
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
        case SNAPPY:
            return "SNAPPY";
        case LZ4:
            return "LZ4";
    }
}



} }  // namespace ofx::IO
