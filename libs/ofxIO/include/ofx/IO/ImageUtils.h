//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofTypes.h"
#include "ofFileUtils.h"
#include "ofImage.h"
#include "FreeImage.h"


namespace ofx {
namespace IO {



/// \brief A simple typedef for an image handle.
///
/// This handle should be created with 
typedef std::shared_ptr<FIBITMAP> ImageHandle;


/// \brief An image metadata entry.
struct ImageMetadata
{
    /// \brief Image metadata type.
    std::string type;

    /// \brief Entry id.
    int id;

    /// \brief Entry key.
    std::string key;

    /// \brief Entry value.
    std::string value;
    
    /// \brief Entry description.
    std::string description;

    /// \brief Single comment or keywords.
    static const std::string METADATA_TYPE_COMMENTS;

    /// \brief Exif-TIFF metadata.
    static const std::string METADATA_TYPE_EXIF_MAIN;

    /// \brief Exif-specific metadata.
    static const std::string METADATA_TYPE_EXIF_EXIF;

    /// \brief Exif GPS metadata.
    static const std::string METADATA_TYPE_EXIF_GPS;

    /// \brief Exif maker note metadata.
    static const std::string METADATA_TYPE_EXIF_MAKERNOTE;

    /// \brief Exif interoperability metadata.
    static const std::string METADATA_TYPE_EXIF_INTEROP;

    /// \brief IPTC/NAA metadata.
    static const std::string METADATA_TYPE_IPTC;

    /// \brief Abobe XMP metadata.
    static const std::string METADATA_TYPE_XMP;

    /// \brief GeoTIFF metadata.
    static const std::string METADATA_TYPE_GEOTIFF;

    /// \brief Animation metadata.
    static const std::string METADATA_TYPE_ANIMATION;



    

};





/// \brief A set of image utilities.
class ImageUtils
{
public:

//    static std::string getMetadataByKey(ImageHandle handle, const std::string& key);


//    static std::string getImageMetaData(ImageHandle handle,
//                                        const std::string& type,
//                                        int tag);
//
//                                 // YYYY:MM:DD HH:MM:SS
//
//
//    // http://www.exiv2.org/tags.html

    // 0x9003	36867	Image	Exif.Image.DateTimeOriginal
//0x9003	36867	Image	Exif.Image.DateTimeOriginal	Ascii	The date and time when the original image data was generated.
//    DateTimeOriginal
//    DateTimeDigitized

//    0x9290	37520	Photo	Exif.Photo.SubSecTime	Ascii	A tag used to record fractions of seconds for the <DateTime> tag.
//        0x9291	37521	Photo	Exif.Photo.SubSecTimeOriginal	Ascii	A tag used to record fractions of seconds for the <DateTimeOriginal> tag.
//            0x9292	37522	Photo	Exif.Photo.SubSecTimeDigitized	Ascii	A tag used to record fractions of seconds for the <DateTimeDigitized> tag.


//    static std::string

//    /// \brief Load image header information without loading pixels data.
//    /// \param header The header data to fill.
//    /// \param path the path of the image.
//    /// \param loadPixelsIfRequired If header loading is not supported, load the full image.
//    /// \returns true if successful.
//    static bool loadHeader(ImageHeader& header,
//                           const std::filesystem::path& path,
//                           bool loadPixelsIfRequired = true);
//
//
//    static ofPixels_<unsigned char> scaleAndCropTo(const ofPixels_<unsigned char>& pixelsRef,
//                                                   std::size_t width,
//                                                   std::size_t height,
//                                                   ofScaleMode scaleMode = OF_SCALEMODE_FIT);
//
//    static ofPixels_<unsigned char> dither(const ofPixels_<unsigned char>& pixels,
//                                           float threshold = 0.75,
//                                           float quantWeight = 0.125);
//
//    static ofPixels_<unsigned char> toGrayscale(const ofPixels_<unsigned char>& pixels);
//


private:
//    static void _accumulateDitherError(std::size_t x,
//                                       std::size_t y,
//                                       ofPixels_<unsigned char>& pixels,
//                                       int qError,
//                                       std::vector<float>& qErrors,
//                                       float quantWeight);

};



} } // namespace ofx::IO
