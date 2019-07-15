//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
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

    bool accept(const Poco::Path& path) const override;

};


} } // namespace ofx::IO
