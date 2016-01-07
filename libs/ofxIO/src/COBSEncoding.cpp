// =============================================================================
//
// Copyright (c) 2010-2016 Christopher Baker <http://christopherbaker.net>
//
// Portions:
//  Copyright (c) 2011, Jacques Fortier. All rights reserved.
//  https://github.com/jacquesf/COBS-Consistent-Overhead-Byte-Stuffing
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


#include "ofx/IO/COBSEncoding.h"


namespace ofx {
namespace IO {


COBSEncoding::COBSEncoding()
{
}


COBSEncoding::~COBSEncoding()
{
}


std::size_t COBSEncoding::encode(const ByteBuffer& buffer,
                                 ByteBuffer& encodedBuffer)
{
    if (buffer.size() > 0)
    {
        const std::size_t encodedMax = buffer.size() + (buffer.size() / 254) + 1;
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


std::size_t COBSEncoding::decode(const ByteBuffer& buffer,
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


std::size_t COBSEncoding::encode(const uint8_t* buffer,
                                 std::size_t size,
                                 uint8_t* encoded)
{
    if (size == 0)
        return 0;

    std::size_t read_index  = 0;
    std::size_t write_index = 1;
    std::size_t code_index  = 0;
    uint8_t code = 1;

    while (read_index < size)
    {
        if (buffer[read_index] == 0)
        {
            encoded[code_index] = code;
            code = 1;
            code_index = write_index++;
            read_index++;
        }
        else
        {
            encoded[write_index++] = buffer[read_index++];
            code++;

            if (code == 0xFF)
            {
                encoded[code_index] = code;
                code = 1;
                code_index = write_index++;
            }
        }
    }

    encoded[code_index] = code;

    return write_index;
}

std::size_t COBSEncoding::decode(const uint8_t* buffer,
                                 std::size_t size,
                                 uint8_t* decoded)
{
    if (size == 0)
        return 0;

    size_t read_index  = 0;
    size_t write_index = 0;
    uint8_t code;
    uint8_t i;

    while (read_index < size)
    {
        code = buffer[read_index];

        if (read_index + code > size && code != 1)
        {
            return 0;
        }

        read_index++;

        for (i = 1; i < code; i++)
        {
            decoded[write_index++] = buffer[read_index++];
        }

        if (code != 0xFF && read_index != size)
        {
            decoded[write_index++] = '\0';
        }
    }
    
    return write_index;
}


} }  // namespace ofx::IO
