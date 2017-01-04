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


/// \brief A path filter to accept hidden files.
class HiddenFileFilter: public AbstractPathFilter
{
public:
    /// \brief Construct a hidden file filter.
    HiddenFileFilter();

    /// \brief Destroys a hidden file filter.
    virtual ~HiddenFileFilter();

    /// \brief Accept a path based if it represents a hidden file.
    /// \returns true iff the path represents a hidden file.
    bool accept(const Poco::Path& path) const override;

};


} } // namespace ofx::IO
