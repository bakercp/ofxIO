//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <set>
#include "Poco/File.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


/// \brief A path filter to accept device paths.
class DeviceFilter: public AbstractPathFilter
{
public:
    /// \brief Construct a device filter.
    DeviceFilter();

    /// \brief Destroy a device filter.
    virtual ~DeviceFilter();

    /// \brief Accept a path based if it represents a device.
    /// \returns true iff the path represents a device.
    bool accept(const std::filesystem::path& path) const override;
};


} } // namespace ofx::IO
