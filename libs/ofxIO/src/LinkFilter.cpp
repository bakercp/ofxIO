//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/LinkFilter.h"


namespace ofx {
namespace IO {


LinkFilter::LinkFilter()
{
}


LinkFilter::~LinkFilter()
{
}


bool LinkFilter::accept(const std::filesystem::path& path) const
{
    return Poco::File(path.string()).isLink();
}


} } // namespace ofx::IO
