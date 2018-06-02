//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/DirectoryFilter.h"


namespace ofx {
namespace IO {


DirectoryFilter::DirectoryFilter(bool acceptMatches):
	_acceptMatches(acceptMatches)
{
}


DirectoryFilter::~DirectoryFilter()
{
}


bool DirectoryFilter::accept(const Poco::Path& path) const
{
	bool isDirectory = Poco::File(path).isDirectory();

	return _acceptMatches ? isDirectory : !isDirectory;
}


} } // namespace ofx::IO
