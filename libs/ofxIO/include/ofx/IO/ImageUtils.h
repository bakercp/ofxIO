//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofRectangle.h"
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
        /// \brief Image width in pixels.
        std::size_t width = 0;

        /// \brief Image height in pixels.
        std::size_t height = 0;

        /// \brief Image bits per pixel.
        std::size_t bpp = 0;
    };


    /// \brief Load image header information without loading pixels data.
    ///
    /// Get image information quickly by reading the header without reading the
    /// image pixel data. This should be faster when supported. Some file types
    /// do not support image header inspection.
    ///
    /// \param header The header data to fill.
    /// \param path the path of the image.
    /// \param loadPixelsIfRequired If header loading is not supported, load the full image.
    /// \returns true if successful.
    static bool loadHeader(ImageHeader& header,
                           const std::filesystem::path& path,
                           bool loadPixelsIfRequired = true);


    static ofPixels_<unsigned char> scaleAndCropTo(const ofPixels_<unsigned char>& pixelsRef,
                                                   std::size_t width,
                                                   std::size_t height,
                                                   ofScaleMode scaleMode = OF_SCALEMODE_FIT);

    static ofPixels_<unsigned char> dither(const ofPixels_<unsigned char>& pixels,
                                           float threshold = 0.75,
                                           float quantWeight = 0.125);

    /// \brief Convert ofPixels to grayscale.
    /// \param pixels The pixels to convert.
    /// \returns the grayscale version of the pixels.
    static ofPixels_<unsigned char> toGrayscale(const ofPixels_<unsigned char>& pixels);



private:
    static void _accumulateDitherError(std::size_t x,
                                       std::size_t y,
                                       ofPixels_<unsigned char>& pixels,
                                       int qError,
                                       std::vector<float>& qErrors,
                                       float quantWeight);
    
};


} } // namespace ofx::IO
