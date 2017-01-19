//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "Poco/Path.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


/// \brief Represents a searchable path that can be recursive.
class SearchPath: public AbstractSearchPath
{
public:
    /// \brief Construct an empty search path.
    SearchPath();

    /// \brief Construct a search path.
    /// \param path is the search path.
    /// \param isRecursive enables recursive path searches.
    SearchPath(const Poco::Path& path, bool isRecursive = false);

    /// \brief Destroy a search path.
    virtual ~SearchPath();

    bool isRecursive() const override;

    Poco::Path getPath() const override;
    
private:
    /// \brief The path to search.
    Poco::Path _path;

    /// \brief True if the search path is recursive.
    bool _isRecursive;

};


} } // namespace ofx::IO
