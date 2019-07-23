//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/IO/JSONUtils.h"
#include "Poco/DeflatingStream.h"
#include "Poco/Exception.h"
#include "Poco/InflatingStream.h"


namespace ofx {
namespace IO {


bool JSONUtils::saveJSON(const std::filesystem::path& filename,
                         const ofJson& json)
{
    try
    {
        std::ofstream ostr(ofToDataPath(filename.string(), true),
                           std::ios::binary);

        if (std::filesystem::extension(filename) == ".gz")
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

    
bool JSONUtils::loadJSON(const std::filesystem::path& filename, ofJson& json)
{
    try
    {
        std::ifstream istr(ofToDataPath(filename.string(), true),
                           std::ios::binary);

        if (std::filesystem::extension(filename) == ".gz")
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


} } // namespace ofx::IO
