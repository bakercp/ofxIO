//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofFileUtils.h"
#include "FreeImage.h"


namespace ofx {
namespace IO {


/// \brief A lightweight class representing an image.
///
/// When possible, only the image headers are loaded.
class ImageHeader
{
public:
    /// \brief Create an empty ImageHeader.
    ImageHeader();

    /// \brief Create an ImageHeader from the image at the given path.
    /// \param path The path of the image to load.
    ImageHeader(const std::filesystem::path& path);

    /// \brief Destroy the ImageHeader.
    ~ImageHeader();

    /// \brief Load an ImageHeader from the given path.
    /// \param path The path of the image to load.
    /// \returns true if the ImageHeader was successfully loaded.
    bool load(const std::filesystem::path& path);

    /// \returns true if the ImageHeader was successfully loaded.
    bool isLoaded() const;

    /// \returns the image width in pixels.
    std::size_t getWidth() const;

    /// \returns the image width in pixels.
    std::size_t getHeight() const;

    /// \returns the image bits per pixel.
    std::size_t getBitsPerPixel() const;

    /// \brief Get a metadata value as a string for the given key.
    ///
    /// This method will iterate through all known metadata models until a
    /// a value is found for this key.
    ///
    /// These metadata models include those supported by FreeImage, including
    /// EXIF, XMP, GEO, etc.
    ///
    /// The returned value is a string representation (which may be an
    /// approximation for non-ASCII value-types). Care must be taken to get
    /// an accurate intrepretation of non-ASCII values.
    ///
    /// \param key The metadata field to find.
    /// \returns the value for the requested tag or an empty string if none.
    std::string getMetadataTagAsString(const std::string& key);

    

//    std::tm t = {};
//    std::istringstream ss("2011-Februar-18 23:12:34");
//    ss.imbue(std::locale("de_DE.utf-8"));
//    ss >> std::get_time(&t, "%Y-%b-%d %H:%M:%S");
//    if (ss.fail()) {
//        std::cout << "Parse failed\n";
//        } else {
//            std::cout << std::put_time(&t, "%c") << '\n';
//        }


//    template<typename Type>
//    std::vector<Type> getMetadataTag(const std::string& key)
//    {
//        FITAG* tag = nullptr;
//
//        for (const auto& model: METADATA_MODELS)
//        {
//            if (FreeImage_GetMetadata(model, _dib.get(), key.data(), &tag))
//            {
//                std::vector<Type> v;
//
//                DLL_API FREE_IMAGE_MDTYPE DLL_CALLCONV FreeImage_GetTagType(FITAG *tag);
//                DLL_API DWORD DLL_CALLCONV FreeImage_GetTagCount(FITAG *tag);
//                DLL_API DWORD DLL_CALLCONV FreeImage_GetTagLength(FITAG *tag);
//                DLL_API const void *DLL_CALLCONV FreeImage_GetTagValue(FITAG *tag);
//            }
//        }
//        
//        return std::vector<Type>();
//    }

    /// \brief Get the underlying image handle (aka device-independent bitmap).
    ///
    /// This memory managed dib can be passed to many FreeImage functions.
    ///
    /// For example, to get the width of an image:
    ///
    ///     FreeImage_GetWidth(dib().get());
    ///
    /// \returns the underlying image dib as a memory-managed shared pointer.
    std::shared_ptr<FIBITMAP> dib();

private:
    /// \brief Make an image handle.
    static std::shared_ptr<FIBITMAP> _makeDIB(const std::filesystem::path& path);

    /// \brief The image handle.
    std::shared_ptr<FIBITMAP> _dib = nullptr;

    static const std::vector<FREE_IMAGE_MDMODEL> METADATA_MODELS;
};



} } // namespace ofx::IO
