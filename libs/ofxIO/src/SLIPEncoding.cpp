// =============================================================================
//
// Copyright (c) 2015 Jean-Pierre Mouilleseaux <jpm@chordedconstructions.com>
// Copyright (c) 2016 Christopher Baker <http://christopherbaker.net>
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


namespace ofx {
namespace IO {


SLIPEncoding::SLIPEncoding()
{
}


SLIPEncoding::~SLIPEncoding()
{
}


std::size_t SLIPEncoding::encode(const ByteBuffer& buffer,
                                 ByteBuffer& encodedBuffer)
{
    if (buffer.size() > 0)
    {
        const std::size_t encodedMax = 2 * buffer.size() + 2;
        encodedBuffer.resize(encodedMax);
        std::size_t size = encode(buffer.getPtr(),
                                  buffer.size(),
                                  encodedBuffer.getPtr());
        encodedBuffer.resize(size);
        return encodedBuffer.size();
    }
    else
    {
        return 0;
    }
}


std::size_t SLIPEncoding::decode(const ByteBuffer& buffer,
                                 ByteBuffer& decodedBuffer)
{
    if (buffer.size() > 0)
    {
        decodedBuffer.resize(buffer.size());
        std::size_t size = decode(buffer.getPtr(),
                                  buffer.size(),
                                  decodedBuffer.getPtr());
        decodedBuffer.resize(size);
        return decodedBuffer.size();
    }
    else
    {
        return 0;
    }
}


std::size_t SLIPEncoding::encode(const uint8_t* buffer,
                                 std::size_t size,
                                 uint8_t* encoded)
{
    if (size == 0)
        return 0;

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
    if (size == 0)
        return 0;

    std::size_t read_index  = 0;
    std::size_t write_index = 0;
    
    while (read_index < size)
    {
        if (buffer[read_index] == END)
        {
            // flush or done
            read_index++;
        }
        else if (buffer[read_index] == ESC)
        {
            if (buffer[read_index+1] == ESC_END)
            {
                decoded[write_index++] = END;
                read_index += 2;
            }
            else if (buffer[read_index+1] == ESC_ESC)
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
