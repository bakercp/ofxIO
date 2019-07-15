//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <set>
#include "Poco/File.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


/// \brief A path filter to accept directory paths.
class DirectoryFilter: public AbstractPathFilter
{
public:
    /// \brief Construct a directory filter.
    DirectoryFilter(bool acceptMatches = true);

    /// \brief Destroys a directory filter.
    virtual ~DirectoryFilter() override;

    /// \brief Accept a path based if it represents a directory.
    /// \returns true iff the path represents a directory.
    bool accept(const Poco::Path& path) const override;

private:
    /// \brief true iff matches should be accepted,
    /// otherwise false iff matches should be rejected.
    bool _acceptMatches;

};


} } // namespace ofx::IO
