//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/DeviceFilter.h"


namespace ofx {
namespace IO {


DeviceFilter::DeviceFilter()
{
}


DeviceFilter::~DeviceFilter()
{
}


bool DeviceFilter::accept(const std::filesystem::path& path) const
{
    return Poco::File(path.string()).isDevice();
}


} } // namespace ofx::IO
