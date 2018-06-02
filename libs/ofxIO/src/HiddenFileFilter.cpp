//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/HiddenFileFilter.h"


namespace ofx {
namespace IO {


HiddenFileFilter::HiddenFileFilter()
{
}


HiddenFileFilter::~HiddenFileFilter()
{
}


bool HiddenFileFilter::accept(const Poco::Path& path) const
{
    return Poco::File(path).isHidden();
}


} } // namespace ofx::IO
