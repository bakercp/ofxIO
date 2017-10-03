//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/ImageUtils.h"


namespace ofx {
namespace IO {


const std::string ImageMetadata::METADATA_TYPE_COMMENTS = "COMMENTS";
const std::string ImageMetadata::METADATA_TYPE_EXIF_MAIN = "EXIF_MAIN";
const std::string ImageMetadata::METADATA_TYPE_EXIF_EXIF = "EXIF_EXIF";
const std::string ImageMetadata::METADATA_TYPE_EXIF_GPS = "EXIF_GPS";
const std::string ImageMetadata::METADATA_TYPE_EXIF_MAKERNOTE = "EXIF_MAKERNOTE";
const std::string ImageMetadata::METADATA_TYPE_EXIF_INTEROP = "EXIF_INTEROP";
const std::string ImageMetadata::METADATA_TYPE_IPTC = "IPTC";
const std::string ImageMetadata::METADATA_TYPE_XMP = "XMP";
const std::string ImageMetadata::METADATA_TYPE_GEOTIFF = "GEOTIFF";
const std::string ImageMetadata::METADATA_TYPE_ANIMATION = "ANIMATION";
//
//
//ImageHandle ImageUtils::makeHandle(const std::filesystem::path& _path)
//{
//    auto path = ofToDataPath(_path.string(), true);
//    auto fif = FreeImage_GetFIFFromFilename(path.data());
//
//    return std::shared_ptr<FIBITMAP>(FreeImage_Load(fif,
//                                                    path.data(),
//                                                    FIF_LOAD_NOPIXELS),
//                                     FreeImage_Unload);
//}
//
//
//std::size_t ImageUtils::getImageWidth(ImageHandle handle)
//{
//    return FreeImage_GetWidth(handle.get());
//}
//
//
//std::size_t ImageUtils::getImageHeight(ImageHandle handle)
//{
//    return FreeImage_GetHeight(handle.get());
//}
//
//
//std::size_t ImageUtils::getImageBitsPerPixel(ImageHandle handle)
//{
//    return FreeImage_GetBPP(handle.get());
//}
//
//
//std::vector<ImageMetadata> ImageUtils::getImageMetadata(ImageHandle handle,
//                                                        const std::string& type)
//{
//    std::vector<ImageMetadata> results;
//
//    FREE_IMAGE_MDMODEL model = FIMD_NODATA;
//
//    if (type == ImageMetadata::METADATA_TYPE_COMMENTS)
//        model = FIMD_COMMENTS;
//    else if (type == ImageMetadata::METADATA_TYPE_EXIF_MAIN)
//        model = FIMD_EXIF_MAIN;
//    else if (type == ImageMetadata::METADATA_TYPE_EXIF_EXIF)
//        model = FIMD_EXIF_EXIF;
//    else if (type == ImageMetadata::METADATA_TYPE_EXIF_GPS)
//        model = FIMD_EXIF_GPS;
//    else if (type == ImageMetadata::METADATA_TYPE_EXIF_MAKERNOTE)
//        model = FIMD_EXIF_MAKERNOTE;
//    else if (type == ImageMetadata::METADATA_TYPE_EXIF_INTEROP)
//        model = FIMD_EXIF_INTEROP;
//    else if (type == ImageMetadata::METADATA_TYPE_IPTC)
//        model = FIMD_IPTC;
//    else if (type == ImageMetadata::METADATA_TYPE_XMP)
//        model = FIMD_XMP;
//    else if (type == ImageMetadata::METADATA_TYPE_GEOTIFF)
//        model = FIMD_GEOTIFF;
//    else if (type == ImageMetadata::METADATA_TYPE_ANIMATION)
//        model = FIMD_ANIMATION;
//    else
//    {
//        ofLogError("ImageUtils::getImageMetadata") << "Unknown metadata type: " << type;
//        return results;
//    }
//
//    FITAG* tag = nullptr;
//
//    FIMETADATA* mdhandle = FreeImage_FindFirstMetadata(model,
//                                                       handle.get(),
//                                                       &tag);
//
//    if (mdhandle)
//    {
//        do
//        {
//            // Convert the tag value to a string.
//            const char* pKey = FreeImage_GetTagKey(tag);
//            const char* pValue = FreeImage_TagToString(model, tag);
//            const char* pDescription = FreeImage_GetTagDescription(tag);
//            int id = FreeImage_GetTagID(tag);
//
//            ImageMetadata md;
//            md.type = type;
//            md.id = id;
//            md.key = pKey ? pKey : "";
//            md.value = pValue ? pValue : "";
//            md.description = pDescription ? pDescription : "";
//            results.push_back(md);
//        }
//        while (FreeImage_FindNextMetadata(mdhandle, &tag));
//    }
//
//    FreeImage_FindCloseMetadata(mdhandle);
//
//    return results;
//
//}
//
//



//
//
//ofPixels_<unsigned char> ImageUtils::scaleAndCropTo(const ofPixels_<unsigned char>& pixels,
//                                                    std::size_t width,
//                                                    std::size_t height,
//                                                    ofScaleMode scaleMode)
//{
//    ofRectangle inRect(0, 0, pixels.getWidth(), pixels.getHeight());
//
//    ofRectangle outRect(0, 0, width, height);
//
//    inRect.scaleTo(outRect, scaleMode);
//
//    auto inPixels = pixels;
//
//    inPixels.resize(inRect.getWidth(), inRect.getHeight());
//
//    ofPixels_<unsigned char> outPixels;
//
//    inPixels.cropTo(outPixels,
//                    outRect.x - inRect.x,
//                    0,
//                    outRect.width,
//                    outRect.height);
//
//    return outPixels;
//}
//
//
//ofPixels_<unsigned char> ImageUtils::dither(const ofPixels_<unsigned char>& pixels,
//                                            float threshold,
//                                            float quantWeight)
//{
//    // Special thanks to @julapy / ofxDither
//    auto pixelsIn = pixels;
//
//    // ensure the image is grayscale
//    if (OF_IMAGE_GRAYSCALE != pixelsIn.getImageType())
//    {
//        pixelsIn = toGrayscale(pixels);
//    }
//
//    // make a copy
//    auto pixelsOut = pixelsIn;
//
//    // set up the quantization error
//    std::size_t width  = pixelsOut.getWidth();
//    std::size_t height = pixelsOut.getHeight();
//
//    std::size_t numPixels = width * height; // 1 byte / pixel
//
//    std::vector<float> qErrors(numPixels);
//
//    //unsigned char* inPix  = pixelsIn.getPixels();
//    unsigned char* outPix = pixelsOut.getData();
//
//    float limit = ofColor_<unsigned char>::limit();
//
//    for (std::size_t y = 0; y < height; y++)
//    {
//        for (std::size_t x = 0; x < width; x++)
//        {
//            std::size_t p = pixelsIn.getPixelIndex(x, y);
//
//            // Add error.
//            std::size_t oldPx = outPix[p] + qErrors[p];
//
//            // Threshold.
//            std::size_t newPx = (oldPx < (threshold * limit)) ? 0 : limit;
//
//            outPix[p] = newPx;
//
//            std::size_t qError = oldPx - newPx;
//
//            _accumulateDitherError(x + 1, y    , pixelsOut, qError, qErrors, quantWeight); // check east
//            _accumulateDitherError(x + 2, y    , pixelsOut, qError, qErrors, quantWeight); // check east east
//            _accumulateDitherError(x - 1, y + 1, pixelsOut, qError, qErrors, quantWeight); // check southwest
//            _accumulateDitherError(x    , y + 1, pixelsOut, qError, qErrors, quantWeight); // check south
//            _accumulateDitherError(x + 1, y + 1, pixelsOut, qError, qErrors, quantWeight); // check southeast
//            _accumulateDitherError(x    , y + 2, pixelsOut, qError, qErrors, quantWeight); // check south south
//        }
//    }
//    
//    return pixelsOut;
//}
//
//
//ofPixels_<unsigned char> ImageUtils::toGrayscale(const ofPixels_<unsigned char>& pixels)
//{
//    if (OF_IMAGE_GRAYSCALE == pixels.getImageType())
//    {
//        return pixels;
//    }
//
//    ofImage img;
//    img.setUseTexture(false);
//    img.setFromPixels(pixels);
//    img.setImageType(OF_IMAGE_GRAYSCALE);
//    return img.getPixels();
//}
//
//
//void ImageUtils::_accumulateDitherError(std::size_t x,
//                                        std::size_t y,
//                                        ofPixels_<unsigned char>& pixels,
//                                        int qError,
//                                        std::vector<float>& qErrors,
//                                        float quantWeight)
//{
//    if (x < pixels.getWidth() && y < pixels.getHeight())
//    {
//        qErrors[pixels.getPixelIndex(x, y)] += quantWeight * qError;
//    }
//}


} } // namespace ofx::IO
