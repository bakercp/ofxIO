//
// Copyright (c) 2009 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <set>
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/RegularExpression.h"
#include "Poco/String.h"
#include "Poco/UTF8String.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


/// \brief A path filter to accept symbolic link paths.
class LinkFilter: public AbstractPathFilter
{
public:
    /// \brief Construct a link filter.
    LinkFilter();

    /// \brief Destroy a link filter.
    virtual ~LinkFilter();

    /// \brief Accept a path based if it represents a symbolic link.
    /// \returns true iff the path represents a symbolic link.
    bool accept(const Poco::Path& path) const override;

};


} } // namespace ofx::IO
