//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <unordered_set>
#include "Poco/Path.h"
#include "Poco/String.h"
#include "Poco/UTF8String.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


/// \brief A path filter to accept files with certain extensions.
class FileExtensionFilter: public AbstractPathFilter
{
public:
    /// \brief Construct an empty file extension filter.
    FileExtensionFilter();

    /// \brief Construct a simple file extension filter.
    /// \param fileExtension a single file extension to add (e.g. "jpg").
    /// \param ignoreCase will ingore case when comparing file extensions.
    /// \param acceptMatches will accept matches. When acceptMatches is
    ///        false, matching extensions are rejected.
    FileExtensionFilter(const std::string& fileExtension,
                        bool ignoreCase = true,
                        bool acceptMatches = true);

    /// \brief Destroy the file extension filter.
    virtual ~FileExtensionFilter();

    /// \brief Accept a path if it satisfies the file filter.
    /// \returns true iff the path extension matches one from the list
    ///        and the additional match criteria (ignoreCase and
    ///        acceptMatches) are also satisfied.
    bool accept(const Poco::Path& path) const override;

    /// \brief Add an extension to the list of extensions.
    /// \note Do not include the dot (e.g. use "jpg" not ".jpg").
    /// \param extension to be added to the list (e.g. "jpg").
    void addExtension(const std::string& extension);

    /// \brief Add a set of extensions to the list of extensions.
    /// \note Do not include the dot (e.g. use "jpg" not ".jpg").
    /// \param extensions to be added to the list (e.g. "jpg").
    void addExtensions(const std::unordered_set<std::string>& extensions);

    /// \brief Remove an extension from the list of extensions.
    /// \note Do not include the dot (e.g. use "jpg" not ".jpg").
    /// \param extension to be removed from the list (e.g. "jpg").
    void removeExtension(const std::string& extension);

    /// \brief Set if the case should be ignored.
    /// \param ignoreCase will ingore case when comparing file extensions.
    void setIgnoreCase(bool ignoreCase);

    /// \brief Query if the case is ignored.
    /// \returns true if the file extension case will be ignored.
    bool getIgnoreCase() const;

private:
    /// \brief true iff the case should be ignored.
    bool _ignoreCase = true;

    /// \brief true iff matches should be accepted,
    /// otherwise false iff matches should be rejected.
    bool _acceptMatches = true;

    /// \brief The list of file extensions to match.
    std::unordered_set<std::string> _extensions;

};


} } // namespace ofx::IO
