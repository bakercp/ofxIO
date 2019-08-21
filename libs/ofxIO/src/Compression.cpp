//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/IO/Compression.h"
#include "ofx/IO/ByteBufferStream.h"
#include "Poco/Buffer.h"
#include "Poco/DeflatingStream.h"
#include "Poco/InflatingStream.h"
#include "Poco/Version.h"
#include "snappy.h"
#include "lz4.h"
#include "ofLog.h"

#include "brotli/decode.h"
#include "brotli/encode.h"
#include "common/version.h"

//#include "enc/compressor.h"
//#include "tools/version.h"


namespace ofx {
namespace IO {


//static const size_t kFileBufferSize = 65536;
//
//
//static int Decompress(FILE* fin, FILE* fout) {
//
//    /* Dictionary should be kept during first rounds of decompression. */
//    uint8_t* dictionary = NULL;
//    uint8_t* input;
//    uint8_t* output;
//    size_t total_out;
//    size_t available_in;
//    const uint8_t* next_in;
//    size_t available_out = kFileBufferSize;
//    uint8_t* next_out;
//    BrotliResult result = BROTLI_RESULT_ERROR;
//    BrotliState* s = BrotliCreateState(NULL, NULL, NULL);
//    if (!s) {
//        fprintf(stderr, "out of memory\n");
//        return 0;
//    }
//
//    input = (uint8_t*)malloc(kFileBufferSize);
//    output = (uint8_t*)malloc(kFileBufferSize);
//    if (!input || !output) {
//        fprintf(stderr, "out of memory\n");
//        goto end;
//    }
//    
//    next_out = output;
//    result = BROTLI_RESULT_NEEDS_MORE_INPUT;
//    while (1) {
//        if (result == BROTLI_RESULT_NEEDS_MORE_INPUT) {
//            if (feof(fin)) {
//                break;
//            }
//            available_in = fread(input, 1, kFileBufferSize, fin);
//            next_in = input;
//            if (ferror(fin)) {
//                break;
//            }
//        } else if (result == BROTLI_RESULT_NEEDS_MORE_OUTPUT) {
//            fwrite(output, 1, kFileBufferSize, fout);
//            if (ferror(fout)) {
//                break;
//            }
//            available_out = kFileBufferSize;
//            next_out = output;
//        } else {
//            break; /* Error or success. */
//        }
//        result = BrotliDecompressStream(&available_in, &next_in,
//                                        &available_out, &next_out, &total_out, s);
//    }
//    if (next_out != output) {
//        fwrite(output, 1, (size_t)(next_out - output), fout);
//    }
//
//    if ((result == BROTLI_RESULT_NEEDS_MORE_OUTPUT) || ferror(fout)) {
//        fprintf(stderr, "failed to write output\n");
//    } else if (result != BROTLI_RESULT_SUCCESS) { /* Error or needs more input. */
//        fprintf(stderr, "corrupt input\n");
//    }
//
//end:
//    free(dictionary);
//    free(input);
//    free(output);
//    BrotliDestroyState(s);
//    return (result == BROTLI_RESULT_SUCCESS) ? 1 : 0;
//}
//
//static int Compress(int quality, int lgwin, FILE* fin, FILE* fout) {
//    BrotliEncoderState* s = BrotliEncoderCreateInstance(0, 0, 0);
//    uint8_t* buffer = (uint8_t*)malloc(kFileBufferSize << 1);
//    uint8_t* input = buffer;
//    uint8_t* output = buffer + kFileBufferSize;
//    size_t available_in = 0;
//    const uint8_t* next_in = NULL;
//    size_t available_out = kFileBufferSize;
//    uint8_t* next_out = output;
//    int is_eof = 0;
//    int is_ok = 1;
//
//    if (!s || !buffer) {
//        is_ok = 0;
//        goto finish;
//    }
//
//    BrotliEncoderSetParameter(s, BROTLI_PARAM_QUALITY, (uint32_t)quality);
//    BrotliEncoderSetParameter(s, BROTLI_PARAM_LGWIN, (uint32_t)lgwin);
//
//    while (1) {
//        if (available_in == 0 && !is_eof) {
//            available_in = fread(input, 1, kFileBufferSize, fin);
//            next_in = input;
//            if (ferror(fin)) break;
//            is_eof = feof(fin);
//        }
//
//        if (!BrotliEncoderCompressStream(s,
//                                         is_eof ? BROTLI_OPERATION_FINISH : BROTLI_OPERATION_PROCESS,
//                                         &available_in, &next_in, &available_out, &next_out, NULL)) {
//            is_ok = 0;
//            break;
//        }
//
//        if (available_out != kFileBufferSize) {
//            size_t out_size = kFileBufferSize - available_out;
//            fwrite(output, 1, out_size, fout);
//            if (ferror(fout)) break;
//            available_out = kFileBufferSize;
//            next_out = output;
//        }
//        
//        if (BrotliEncoderIsFinished(s)) break;
//    }
//    
//finish:
//    free(buffer);
//    BrotliEncoderDestroyInstance(s);
//    
//    if (!is_ok) {
//        /* Should detect OOM? */
//        fprintf(stderr, "failed to compress data\n");
//        return 0;
//    } else if (ferror(fout)) {
//        fprintf(stderr, "failed to write output\n");
//        return 0;
//    } else if (ferror(fin)) {
//        fprintf(stderr, "failed to read input\n");
//        return 0;
//    }
//    return 1;
//}
//


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

            if (type == GZIP)
            {
                streamType = Poco::InflatingStreamBuf::StreamType::STREAM_GZIP;
            }
            else
            {
                streamType = Poco::InflatingStreamBuf::StreamType::STREAM_ZLIB;
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
        case BR:
        {
            size_t decodedSize = 0;

//            if (!BrotliDecompressedSize(compressedBuffer.size(), compressedBuffer.getPtr(), &decodedSize))
//            {
                decodedSize = compressedBuffer.size() * 4;
//            }

            uncompressedBuffer.resize(decodedSize);

            BrotliDecoderResult result = BrotliDecoderDecompress(compressedBuffer.size(),
                                                                 compressedBuffer.getPtr(),
                                                                 &decodedSize,
                                                                 uncompressedBuffer.getPtr());


//            BrotliResult result = BrotliDecompressBuffer(compressedBuffer.size(),
//                                                         compressedBuffer.getPtr(),
//                                                         &decodedSize,
//                                                         uncompressedBuffer.getPtr());

            
            if (result == BROTLI_DECODER_RESULT_SUCCESS)
            {
                uncompressedBuffer.resize(decodedSize);
                return decodedSize;
            }
            else
            {
                ofLogError("Compression::uncompress") << "Brotli error: " << result << std::endl;
                return 0;
            }

        }
        case NONE:
        {
            uncompressedBuffer.clear();
            uncompressedBuffer.writeBytes(compressedBuffer);
        }
    }

    return 0;
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
            compressedBuffer.resize(uncompressedBuffer.size() * 2);
            snappy::RawCompress(uncompressedBuffer.getCharPtr(),
                                uncompressedBuffer.size(),
                                compressedBuffer.getCharPtr(),
                                &size);
            compressedBuffer.resize(size);
            return size;
        }
        case LZ4:
        {
            std::size_t inputSize = uncompressedBuffer.size();
            std::size_t size = 0;
            // Allocate as many as needed.
            compressedBuffer.resize(inputSize);
            size = LZ4_compress_default(uncompressedBuffer.getCharPtr(),
                                        compressedBuffer.getCharPtr(),
                                        inputSize,
                                        LZ4_compressBound(inputSize));

            compressedBuffer.resize(size);
            return size;
        }
        case BR:
        {
//            brotli::BrotliParams params;
//

            std::size_t encodedSize = BrotliEncoderMaxCompressedSize(uncompressedBuffer.size());

            compressedBuffer.resize(encodedSize);
//
//            int result = brotli::BrotliCompressBuffer(params,
//                                                      uncompressedBuffer.size(),
//                                                      uncompressedBuffer.getPtr(),
//                                                      &encodedSize,
//                                                      compressedBuffer.getPtr());


            BROTLI_BOOL result = BrotliEncoderCompress(BROTLI_DEFAULT_QUALITY,
                                                       BROTLI_DEFAULT_WINDOW,
                                                       BROTLI_DEFAULT_MODE,
                                                       uncompressedBuffer.size(),
                                                       uncompressedBuffer.getPtr(),
                                                       &encodedSize,
                                                       compressedBuffer.getPtr());

            if (result == BROTLI_TRUE)
            {
                compressedBuffer.resize(encodedSize);
                return encodedSize;
            }
            else
            {
                ofLogError("Compression::compress") << "brotli::BrotliCompressBuffer compression error.";
                return 0;
            }
        }
        case NONE:
        {
            compressedBuffer.clear();
            compressedBuffer.writeBytes(uncompressedBuffer);
        }
    }

    return 0;
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


std::string Compression::version(Type type)
{
    switch (type)
    {
        case ZLIB:
        case GZIP:
        {
            std::stringstream ss;
            ss << ZLIB_VERSION;
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
        case BR:
        {
            std::stringstream ss;
            ss << BROTLI_VERSION;
            return ss.str();
        }
        case NONE:
            return "0.0.0";
    }

    return "UNKNOWN";
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
        case BR:
            return "BROTLI";
        case NONE:
            return "NONE";
    }

    return "UNKNOWN";
}



} }  // namespace ofx::IO
