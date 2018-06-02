//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/PathFilterCollection.h"


namespace ofx {
namespace IO {


PathFilterCollection::PathFilterCollection()
{
}
    

PathFilterCollection::~PathFilterCollection()
{
}


bool PathFilterCollection::accept(const Poco::Path& path) const
{
    std::set<AbstractPathFilter*>::const_iterator iter = _filters.begin();

    while (iter != _filters.end())
    {
        if (!(*iter)->accept(path))
        {
            return false;
        }
        ++iter;
    }

    return true;
}

void PathFilterCollection::addFilter(AbstractPathFilter* filter)
{
    _filters.insert(filter);
}


void PathFilterCollection::removeFilter(AbstractPathFilter* filter)
{
    _filters.erase(filter);
}


} } // namespace ofx::IO
