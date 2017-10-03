//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/ImageHeader.h"
#include "ofUtils.h"


namespace ofx {
namespace IO {


const std::vector<FREE_IMAGE_MDMODEL> ImageHeader::METADATA_MODELS {
    FIMD_COMMENTS,
    FIMD_EXIF_MAIN,
    FIMD_EXIF_EXIF,
    FIMD_EXIF_GPS,
    FIMD_EXIF_MAKERNOTE,
    FIMD_EXIF_INTEROP,
    FIMD_IPTC,
    FIMD_XMP,
    FIMD_GEOTIFF,
    FIMD_ANIMATION
};


ImageHeader::ImageHeader()
{
}


ImageHeader::ImageHeader(const std::filesystem::path& path):
    _dib(_makeDIB(path))
{
}


ImageHeader::~ImageHeader()
{
}


bool ImageHeader::load(const std::filesystem::path& path)
{
    _dib = _makeDIB(path);
    return isLoaded();
}


bool ImageHeader::isLoaded() const
{
    return _dib != nullptr;
}


std::size_t ImageHeader::getWidth() const
{
    return FreeImage_GetWidth(_dib.get());
}


std::size_t ImageHeader::getHeight() const
{
    return FreeImage_GetHeight(_dib.get());
}


std::size_t ImageHeader::getBitsPerPixel() const
{
    return FreeImage_GetBPP(_dib.get());
}


std::string ImageHeader::getMetadataTagAsString(const std::string& key)
{
    FITAG* tag = nullptr;

    for (const auto& model: METADATA_MODELS)
    {
        if (FreeImage_GetMetadata(model, _dib.get(), key.data(), &tag))
        {
            const char* pValue = FreeImage_TagToString(model, tag);
            return std::string(pValue ? pValue : "");
        }
    }

    return std::string("");
}


std::shared_ptr<FIBITMAP> ImageHeader::dib()
{
    return _dib;
}


std::shared_ptr<FIBITMAP> ImageHeader::_makeDIB(const std::filesystem::path& _path)
{
    auto path = ofToDataPath(_path.string(), true);
    
    auto fif = FreeImage_GetFIFFromFilename(path.data());

    return std::shared_ptr<FIBITMAP>(FreeImage_Load(fif,
                                                    path.data(),
                                                    FIF_LOAD_NOPIXELS),
                                     FreeImage_Unload);
}


} } // namespace ofx::IO
