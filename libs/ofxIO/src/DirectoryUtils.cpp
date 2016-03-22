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


#include "ofx/IO/DirectoryUtils.h"
#include "Poco/Exception.h"
#include "alphanum.hpp"


namespace ofx {
namespace IO {



void DirectoryUtils::list(const AbstractSearchPath& path,
                          std::vector<Poco::Path>& paths,
                          bool sortAlphaNumeric,
                          AbstractPathFilter* pFilter,
                          Poco::UInt16 maxDepth,
                          TraversalOrder traversalOrder)
{
    paths.clear();

    std::vector<std::string> _files;

    if (path.isRecursive())
    {
        listRecursive(path.getPath().toString(),
                      _files,
                      sortAlphaNumeric,
                      pFilter,
                      maxDepth,
                      traversalOrder);
    }
    else
    {
        list(path.getPath().toString(),
             _files,
             sortAlphaNumeric,
             pFilter);
    }

    std::vector<std::string>::const_iterator iter = _files.begin();

    while (iter != _files.end())
    {
        paths.push_back(*iter);
        ++iter;
    }

}

void DirectoryUtils::list(const Poco::File& directory,
                          std::vector<Poco::File>& files,
                          bool sortAlphaNumeric,
                          AbstractPathFilter* pFilter)
{
	files.clear();

    std::vector<std::string> _files;

    list(directory.path(), _files, sortAlphaNumeric, pFilter);

    std::vector<std::string>::const_iterator iter = _files.begin();

    while (iter != _files.end())
    {
        files.push_back(Poco::File(*iter));
        ++iter;
    }

}


void DirectoryUtils::list(const ofFile& directory,
                          std::vector<ofFile>& files,
                          bool sortAlphaNumeric,
                          AbstractPathFilter* pFilter)
{
    files.clear();

    std::vector<std::string> _files;
    
    list(directory.path(),_files, sortAlphaNumeric, pFilter);

    std::vector<std::string>::const_iterator iter = _files.begin();

    while (iter != _files.end())
    {
        files.push_back(ofFile(*iter));
        ++iter;
    }
    
}


void DirectoryUtils::list(const std::string& directory,
                          std::vector<std::string>& files,
                          bool sortAlphaNumeric,
                          AbstractPathFilter* pFilter)
{
    try
    {
        files.clear();

        std::string _directory = ofToDataPath(directory, true);

        ofFile file(_directory);

        if (!file.exists())
        {
            ofLogError("DirectoryUtils::list") << file.path() << " not found.";
            return;
        }

        Poco::DirectoryIterator iter(_directory);
        Poco::DirectoryIterator endIter;

        while (iter != endIter)
        {
            if(!pFilter || pFilter->accept((*iter).path()))
            {
                files.push_back(iter.path().toString());
            }

            ++iter;
        }

        if (sortAlphaNumeric)
        {
            // now sort the vector with the algorithm
            std::sort(files.begin(),
                      files.end(),
                      doj::alphanum_less<std::string>());
        }
    }
    catch (Poco::Exception& exc)
    {
        ofLogError("DirectoryUtils::list") << exc.displayText();
    }

}


void DirectoryUtils::listRecursive(const std::string& directory,
                                   std::vector<std::string>& files,
                                   bool sortAlphaNumeric,
                                   AbstractPathFilter* pFilter,
                                   Poco::UInt16 maxDepth,
                                   TraversalOrder traversalOrder)
{
    files.clear();

    std::string _directory = ofToDataPath(directory, true);

    if (traversalOrder == SIBLINGS_FIRST)
    {
        SiblingsFirstRecursiveDirectoryIterator iter(_directory, maxDepth);
        SiblingsFirstRecursiveDirectoryIterator endIter;
        
        while (iter != endIter)
        {
            if (!pFilter || pFilter->accept((*iter).path()))
            {
                files.push_back(iter.path().toString());
            }
            
            ++iter;
        }
    }
    else if (traversalOrder == CHILDREN_FIRST)
    {
        SimpleRecursiveDirectoryIterator iter(_directory, maxDepth);
        SimpleRecursiveDirectoryIterator endIter;

        while (iter != endIter)
        {
            if(!pFilter || pFilter->accept((*iter).path()))
            {
                files.push_back(iter.path().toString());
            }
            
            ++iter;
        }
    }


    if (sortAlphaNumeric)
    {
        // now sort the vector with the alpha numeric algorithm
        std::sort(files.begin(),
                  files.end(),
                  doj::alphanum_less<std::string>());
    }

}


void DirectoryUtils::listRecursive(const ofFile& directory,
                                   std::vector<ofFile>& files,
                                   bool sortAlphaNumeric,
                                   AbstractPathFilter* pFilter,
                                   Poco::UInt16 maxDepth,
                                   TraversalOrder traversalOrder)
{
    files.clear();

    std::vector<std::string> _files;

    listRecursive(directory.path(),
                  _files,
                  sortAlphaNumeric,
                  pFilter,
                  maxDepth,
                  traversalOrder);

    std::vector<std::string>::iterator iter = _files.begin();

    while (iter != _files.end())
    {
        files.push_back(ofFile(*iter));
        ++iter;
    }

}


void DirectoryUtils::listRecursive(const Poco::File& directory,
                                   std::vector<Poco::File>& files,
                                   bool sortAlphaNumeric,
                                   AbstractPathFilter* pFilter,
                                   Poco::UInt16 maxDepth,
                                   TraversalOrder traversalOrder)
{
	files.clear();

    std::vector<std::string> _files;

    listRecursive(directory.path(),
                  _files,
                  sortAlphaNumeric,
                  pFilter,
                  maxDepth,
                  traversalOrder);

    std::vector<std::string>::iterator iter = _files.begin();

    while (iter != _files.end())
    {
        files.push_back(Poco::File(*iter));
        ++iter;
    }
}


} } // namespace ofx::IO
