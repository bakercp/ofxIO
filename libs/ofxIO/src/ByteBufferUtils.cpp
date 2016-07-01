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


#include "ofx/IO/ByteBufferUtils.h"
#include "ofx/IO/ByteBuffer.h"
#include "Poco/Buffer.h"
#include "Poco/FileStream.h"
#include <iostream> 
#include "ofLog.h"
#include "ofUtils.h"


namespace ofx {
namespace IO {


ByteBuffer ByteBufferUtils::makeBuffer(uint8_t d0,
                                       uint8_t d1)
{
    uint8_t bytes[] = { d0, d1 };
    return ByteBuffer(bytes, 2);
}


ByteBuffer ByteBufferUtils::makeBuffer(uint8_t d0,
                                       uint8_t d1,
                                       uint8_t d2)
{
    uint8_t bytes[] = { d0, d1, d2 };
    return ByteBuffer(bytes, 3);
}


ByteBuffer ByteBufferUtils::makeBuffer(uint8_t d0,
                                       uint8_t d1,
                                       uint8_t d2,
                                       uint8_t d3)
{
    uint8_t bytes[] = { d0, d1, d2, d3 };
    return ByteBuffer(bytes, 4);
}


ByteBuffer ByteBufferUtils::makeBuffer(uint8_t d0,
                                       uint8_t d1,
                                       uint8_t d2,
                                       uint8_t d3,
                                       uint8_t d4)
{
    uint8_t bytes[] = { d0, d1, d2, d3, d4 };
    return ByteBuffer(bytes, 5);
}


ByteBuffer ByteBufferUtils::makeBuffer(std::istream& istr,
                                       std::size_t bufferSize)
{
    ByteBuffer buffer;
    copyStreamToBuffer(istr, buffer, bufferSize);
    return buffer;
}


std::streamsize ByteBufferUtils::copyStreamToBuffer(std::istream& istr,
                                                    ByteBuffer& byteBuffer,
                                                    std::size_t bufferSize)
{
	poco_assert (bufferSize > 0);

    Poco::Buffer<char> buffer(bufferSize);
    std::streamsize len = 0;
    istr.read(buffer.begin(), static_cast<std::streamsize>(bufferSize));
    std::streamsize n = istr.gcount();

    while (n > 0)
	{
		len += n;
        byteBuffer.writeBytes(reinterpret_cast<uint8_t*>(buffer.begin()), static_cast<std::size_t>(n));
        if (istr)
		{
			istr.read(buffer.begin(), static_cast<std::streamsize>(bufferSize));
            n = istr.gcount();
		}
        else
        {
            n = 0;
        }
	}
    
	return len;
}


std::ostream& ByteBufferUtils::copyBufferToStream(const ByteBuffer& byteBuffer,
                                                  std::ostream& ostr)
{
    if (!ostr.bad())
    {
        ostr.write(byteBuffer.getCharPtr(), static_cast<std::streamsize>(byteBuffer.size()));
    }
    else
    {
        ofLogError("ByteBufferUtils::copyBufferToStream") << "Bad output stream.";
    }

    return ostr;
}


std::streamsize ByteBufferUtils::loadFromFile(const std::string& path,
                                              ByteBuffer& byteBuffer,
                                              bool appendBuffer,
                                              std::ios::openmode openMode)
{
    Poco::FileInputStream fis(ofToDataPath(path, true), openMode);

    if (fis.good())
    {
        if (!appendBuffer)
        {
            byteBuffer.clear();
        }

        std::streamsize n = copyStreamToBuffer(fis, byteBuffer);
        fis.close();
        return n;
    }
    else
    {
        throw Poco::IOException("Bad file input stream.");
    }
}


bool ByteBufferUtils::saveToFile(const ByteBuffer& byteBuffer,
                                 const std::string& path,
                                 std::ios::openmode mode)
{
    Poco::FileOutputStream fos(ofToDataPath(path, true), mode);

    if (fos.good())
    {
        copyBufferToStream(byteBuffer, fos);
        fos.close();
        return true;
    }
    else
    {
        throw Poco::IOException("Bad file output stream.");
    }
}


} } // ofx::IO
