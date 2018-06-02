//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/RegexPathFilter.h"


namespace ofx {
namespace IO {


RegexPathFilter::RegexPathFilter(const std::string& pattern,
                                 int options,
                                 bool optimize):
	_regex(pattern, options, optimize)
{
}

    
RegexPathFilter::~RegexPathFilter()
{
}


bool RegexPathFilter::accept(const Poco::Path& path) const
{
    return _regex.match(path.toString());
}


} } // namespace ofx::IO
