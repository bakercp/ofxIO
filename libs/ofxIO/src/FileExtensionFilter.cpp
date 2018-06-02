//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/FileExtensionFilter.h"
#include <iostream>

namespace ofx {
namespace IO {


FileExtensionFilter::FileExtensionFilter():
    _ignoreCase(true),
    _acceptMatches(true)
{
}


FileExtensionFilter::FileExtensionFilter(const std::string& fileExtension,
                                         bool ignoreCase,
                                         bool acceptMatches):
    _ignoreCase(ignoreCase),
    _acceptMatches(acceptMatches)
{
    addExtension(fileExtension);
}


FileExtensionFilter::~FileExtensionFilter()
{
}

    
bool FileExtensionFilter::accept(const Poco::Path& path) const
{
    // Note: We go through all of these steps to enable ignore case, etc.
    
    std::string extension = path.getExtension();

    auto iter = _extensions.begin();

    while (iter != _extensions.end())
    {
        bool match = false;

        if (_ignoreCase)
        {
            match = (0 == Poco::UTF8::icompare(extension, *iter));
        }
        else
        {
            match = (0 == extension.compare(*iter));
        }

        if (_acceptMatches && match)
        {
            return true;
        }

        ++iter;
    }

    return !_acceptMatches;
}


void FileExtensionFilter::addExtension(const std::string& extension)
{
    _extensions.insert(extension);
}


void FileExtensionFilter::addExtensions(const std::unordered_set<std::string>& extensions)
{
    _extensions.insert(extensions.begin(), extensions.end());
}


void FileExtensionFilter::removeExtension(const std::string& extension)
{
    _extensions.erase(extension);
}


void FileExtensionFilter::setIgnoreCase(bool ignoreCase)
{
    _ignoreCase = ignoreCase;
}


bool FileExtensionFilter::getIgnoreCase() const
{
    return _ignoreCase;
}


} } // namespace ofx::IO
