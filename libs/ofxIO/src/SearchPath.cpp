//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/SearchPath.h"


namespace ofx {
namespace IO {


SearchPath::SearchPath():
    _path(""),
    _isRecursive(false)
{
}


SearchPath::SearchPath(const Poco::Path& path, bool isRecursive):
    _path(path),
    _isRecursive(isRecursive)
{
}


SearchPath::~SearchPath()
{
}


bool SearchPath::isRecursive() const
{
    return _isRecursive;
}


Poco::Path SearchPath::getPath() const
{
    return _path;
}


} } // namespace ofx::Assets
