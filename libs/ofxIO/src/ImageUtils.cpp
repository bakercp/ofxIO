//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/ImageUtils.h"


namespace ofx {
namespace IO {



bool ImageUtils::loadHeader(ImageHeader& header,
                            const std::filesystem::path& path,
                            bool loadPixelsIfRequired)
{
    int flags = FIF_LOAD_NOPIXELS;

    header.fif = FreeImage_GetFIFFromFilename(path.c_str());

    if (FreeImage_FIFSupportsNoPixels(header.fif))
    {
        FIBITMAP* dib = FreeImage_Load(header.fif, path.c_str(), flags);

        if (dib)
        {
            header.type = FreeImage_GetImageType(dib);
            header.width = FreeImage_GetWidth(dib);
            header.height = FreeImage_GetHeight(dib);
            header.bpp = FreeImage_GetBPP(dib);

            FreeImage_Unload(dib);
            return true;
        }
    }


    if (loadPixelsIfRequired)
    {
        ofPixels pixels;
        if (ofLoadImage(pixels, path))
        {
            header.type = FIT_UNKNOWN;
            header.width = pixels.getWidth();
            header.height = pixels.getHeight();
            header.bpp = pixels.getBitsPerPixel();
            return true;
        }
    }

    return false;
}




} } // namespace ofx::IO
