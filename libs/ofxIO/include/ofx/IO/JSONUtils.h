//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "json.hpp"
#include "ofFileUtils.h"
#include "ofx/IO/Compression.h"


namespace ofx {
namespace IO {


class JSONUtils
{
public:
    /// \brief Save minified json to a file.
    ///
    /// If the destination filename ends with .gz, it will be compressed
    /// using gzip.
    ///
    /// \param filename The destination path.
    /// \param json The json to save.
    /// \returns true on success.
    static bool saveJSON(const std::filesystem::path& filename,
                         const nlohmann::json& json);

    /// \brief Load json from a file.
    ///
    /// If the filename ends with .gz, it will be decompressed using gzip.
    ///
    /// \param filename The json path.
    /// \param json The target json object to be filled.
    /// \returns true on success.
    static bool loadJSON(const std::filesystem::path& file,
                         nlohmann::json& json);

    /// \brief Save CBOR encoded json to a file.
    ///
    /// If the destination filename ends with .gz, it will be compressed using
    /// gzip.  If .br, it will be encoded with brotli.
    ///
    /// \param filename The destination path.
    /// \param json The json to save.
    /// \returns true on success.
    static bool saveCBOR(const std::filesystem::path& filename,
                         const nlohmann::json& json);

    /// \brief Load CBOR encoded json from a file.
    ///
    /// If the filename ends with .gz, it will be decompressed using
    /// gzip. If .br, it will be decompressed with brotli.
    ///
    /// \param filename The json path.
    /// \param json The target json object to be filled.
    /// \returns true on success.
    static bool loadCBOR(const std::filesystem::path& file,
                         nlohmann::json& json);

};



} } // namespace ofx::IO
