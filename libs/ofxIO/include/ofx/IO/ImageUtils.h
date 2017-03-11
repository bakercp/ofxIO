//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "FreeImage.h"
#include "ofTypes.h"
#include "ofFileUtils.h"
#include "ofImage.h"


namespace ofx {
namespace IO {


/// \brief A set of image utilities.
class ImageUtils
{
public:
    /// \basic Image parameters.
    struct ImageHeader
    {
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        FREE_IMAGE_TYPE type = FIT_UNKNOWN;
        std::size_t width = 0;
        std::size_t height = 0;
        std::size_t bpp = 0;
    };


    /// \brief Load image header information without loading pixels data.
    /// \param header The header data to fill.
    /// \param path the path of the image.
    /// \param loadPixelsIfRequired If header loading is not supported, load the full image.
    /// \returns true if successful.
    static bool loadHeader(ImageHeader& header,
                           const std::filesystem::path& path,
                           bool loadPixelsIfRequired = true);






};


} } // namespace ofx::IO
