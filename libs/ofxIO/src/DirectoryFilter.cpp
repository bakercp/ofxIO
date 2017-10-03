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


bool DirectoryFilter::accept(const std::filesystem::path& path) const
{
	bool isDirectory = std::filesystem::is_directory(path);

	return _acceptMatches ? isDirectory : !isDirectory;
}


} } // namespace ofx::IO
