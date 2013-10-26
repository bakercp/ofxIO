// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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


#pragma once


#include "Poco/DirectoryIterator.h"
#include "Poco/RecursiveDirectoryIterator.h"
#include "Poco/File.h"
#include "ofFileUtils.h"
#include "ofUtils.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


class AbstractFileFilter;


class DirectoryUtils
{
public:
    
    enum
    {
        INIFINITE_DEPTH = 0
    };

    enum TraversalOrder
    {
        SIBLINGS_FIRST = 0,
        CHILDREN_FIRST
    };

    DirectoryUtils();
    virtual ~DirectoryUtils();

    static void list(const Poco::File& directory,
                     std::vector<Poco::File>& files,
                     bool sortAlphaNumeric = false,
                     AbstractFileFilter* filterPtr = NULL);

    static void list(const ofFile& directory,
                     std::vector<ofFile>& files,
                     bool sortAlphaNumeric = false,
                     AbstractFileFilter* filterPtr = NULL);

    static void list(const std::string& directory,
                     std::vector<std::string>& files,
                     bool sortAlphaNumeric = false,
                     AbstractFileFilter* filterPtr = NULL);

    static void listRecursive(const Poco::File& directory,
                              std::vector<Poco::File>& files,
                              bool sortAlphaNumeric = false,
                              AbstractFileFilter* filterPtr = NULL,
                              Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                              TraversalOrder traversalOrder = CHILDREN_FIRST);

    static void listRecursive(const ofFile& directory,
                              std::vector<ofFile>& files,
                              bool sortAlphaNumeric = false,
                              AbstractFileFilter* filterPtr = NULL,
                              Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                              TraversalOrder traversalOrder = CHILDREN_FIRST);

    static void listRecursive(const std::string& directory,
                              std::vector<std::string>& files,
                              bool sortAlphaNumeric = false,
                              AbstractFileFilter* filterPtr = NULL,
                              Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                              TraversalOrder traversalOrder = CHILDREN_FIRST);

};


} } // namespace ofx::IO
