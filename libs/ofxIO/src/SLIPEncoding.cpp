// =============================================================================
//
// Copyright (c) 2015 Jean-Pierre Mouilleseaux <jpm@chordedconstructions.com>
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


#include "ofx/IO/SLIPEncoding.h"
#include "Poco/Buffer.h"


namespace ofx {
namespace IO {


static const uint8_t END = 0300;
static const uint8_t ESC = 0333;
static const uint8_t ESC_END = 0334;
static const uint8_t ESC_ESC = 0335;


SLIPEncoding::SLIPEncoding()
{
}


SLIPEncoding::~SLIPEncoding()
{
}


bool SLIPEncoding::encode(const AbstractByteSource& buffer,
                          AbstractByteSink& encodedBuffer)
{
    std::vector<uint8_t> bytes = buffer.readBytes();

    const std::size_t encodedMax = 2 * bytes.size() + 2;

    Poco::Buffer<uint8_t> encoded(encodedMax);

    std::size_t size = encode(&bytes[0], bytes.size(), encoded.begin());

    encodedBuffer.writeBytes(encoded.begin(), size);

    return true;
}


bool SLIPEncoding::decode(const AbstractByteSource& buffer,
                          AbstractByteSink& decodedBuffer)
{
    std::vector<uint8_t> bytes = buffer.readBytes();

    Poco::Buffer<uint8_t> decoded(bytes.size() - 1);

    std::size_t size = decode(&bytes[0], bytes.size(), decoded.begin());

    decodedBuffer.writeBytes(decoded.begin(), size);

    return true;
}


std::size_t SLIPEncoding::encode(const uint8_t* buffer,
                                 std::size_t size,
                                 uint8_t* encoded)
{
    std::size_t read_index  = 0;
    std::size_t write_index = 0;

    // double-ENDed, flush any data that may have accumulated due to line noise
    encoded[write_index++] = END;

    while (read_index < size)
    {
        if(buffer[read_index] == END)
        {
            encoded[write_index++] = ESC;
            encoded[write_index++] = ESC_END;
            read_index++;
        }
        else if(buffer[read_index] == ESC)
        {
            encoded[write_index++] = ESC;
            encoded[write_index++] = ESC_ESC;
            read_index++;
        }
        else
        {
            encoded[write_index++] = buffer[read_index++];
        }
    }

    encoded[write_index++] = END;

    return write_index;
}

std::size_t SLIPEncoding::decode(const uint8_t* buffer,
                                 std::size_t size,
                                 uint8_t* decoded)
{
    std::size_t read_index  = 0;
    std::size_t write_index = 0;

    while (read_index < size)
    {
        if(buffer[read_index] == END)
        {
            // flush or done
            read_index++;
        }
        else if(buffer[read_index] == ESC)
        {
            if(buffer[read_index+1] == ESC_END)
            {
                decoded[write_index++] = END;
                read_index += 2;
            }
            else if(buffer[read_index+1] == ESC_ESC)
            {
                decoded[write_index++] = ESC;
                read_index += 2;
            }
            else
            {
                // considered a protocol violation
            }
        }
        else
        {
            decoded[write_index++] = buffer[read_index++];
        }
    }

    return write_index;
}


} }  // namespace ofx::IO
