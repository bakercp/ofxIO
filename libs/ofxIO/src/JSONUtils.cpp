//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/IO/JSONUtils.h"
#include "ofLog.h"
#include "ofUtils.h"
#include "Poco/DeflatingStream.h"
#include "Poco/Exception.h"
#include "Poco/InflatingStream.h"


namespace ofx {
namespace IO {


bool JSONUtils::saveJSON(const std::filesystem::path& filename,
                         const nlohmann::json& json)
{
    try
    {
        std::ofstream ostr(ofToDataPath(filename.string(), true),
                           std::ios::binary);

        if (filename.extension() == ".gz")
        {
            Poco::DeflatingOutputStream deflater(ostr,
                                                 Poco::DeflatingStreamBuf::STREAM_GZIP);
            deflater << json;
            deflater.close();
        }
        else
        {
            ostr << json;
        }

        ostr.close();

        return true;
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("JSONUtils::saveJSON") << "Error saving json " << exc.displayText();
    }
    catch (const std::exception& exc)
    {
        ofLogError("JSONUtils::saveJSON") << "Error saving json " << exc.what();
    }
    catch (...)
    {
        ofLogError("JSONUtils::saveJSON") << "Error saving json. Unknown error.";
    }

    return false;
}

    
bool JSONUtils::loadJSON(const std::filesystem::path& filename,
                         nlohmann::json& json)
{
    try
    {
        std::ifstream istr(ofToDataPath(filename.string(), true),
                           std::ios::binary);

        if (filename.extension() == ".gz")
        {
            Poco::InflatingInputStream inflater(istr, Poco::InflatingStreamBuf::STREAM_GZIP);
            inflater >> json;
        }
        else
        {
            istr >> json;
        }

        istr.close();
        
        return true;
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("JSONUtils::loadJSON") << "Error loading json " << exc.displayText();
    }
    catch (const std::exception& exc)
    {
        ofLogError("JSONUtils::loadJSON") << "Error loading json " << exc.what();
    }
    catch (...)
    {
        ofLogError("JSONUtils::loadJSON") << "Error loading json. Unknown error.";
    }

    return false;
}




bool JSONUtils::saveCBOR(const std::filesystem::path& filename,
                         const nlohmann::json& json)
{
    ByteBuffer cbor(nlohmann::json::to_cbor(json));
    ByteBuffer out;

    if (filename.extension() == ".gz")
        Compression::compress(cbor, out, Compression::GZIP);
    else if (filename.extension() == ".br")
        Compression::compress(cbor, out, Compression::BR);
    else
        out = cbor;

    return ByteBufferUtils::saveToFile(out, filename.string());
}


bool JSONUtils::loadCBOR(const std::filesystem::path& filename,
                         nlohmann::json& json)
{
    ByteBuffer bytes;
    ByteBuffer cbor;
    ByteBufferUtils::loadFromFile(filename.string(), bytes);

    if (filename.extension() == ".gz")
        Compression::uncompress(bytes, cbor, Compression::GZIP);
    else if (filename.extension() == ".br")
        Compression::uncompress(bytes, cbor, Compression::BR);
    else
        cbor = bytes;

    json = nlohmann::json::from_cbor(cbor);

    return true;
}





} } // namespace ofx::IO
