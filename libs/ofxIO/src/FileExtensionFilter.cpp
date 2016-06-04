// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


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
