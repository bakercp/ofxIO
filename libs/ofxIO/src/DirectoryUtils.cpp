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
                          TraversalOrder traversalOrder,
                          bool makeRelativeToDirectory)
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
                      traversalOrder,
                      makeRelativeToDirectory);
    }
    else
    {
        list(path.getPath().toString(),
             _files,
             sortAlphaNumeric,
             pFilter,
             makeRelativeToDirectory);
    }

    auto iter = _files.begin();

    while (iter != _files.end())
    {
        paths.push_back(*iter);
        ++iter;
    }

}

void DirectoryUtils::list(const Poco::File& directory,
                          std::vector<Poco::File>& files,
                          bool sortAlphaNumeric,
                          AbstractPathFilter* pFilter,
                          bool makeRelativeToDirectory)
{
	files.clear();

    std::vector<std::string> _files;

    list(directory.path(),
         _files,
         sortAlphaNumeric,
         pFilter,
         makeRelativeToDirectory);

    auto iter = _files.begin();

    while (iter != _files.end())
    {
        files.push_back(Poco::File(*iter));
        ++iter;
    }

}


void DirectoryUtils::list(const ofFile& directory,
                          std::vector<ofFile>& files,
                          bool sortAlphaNumeric,
                          AbstractPathFilter* pFilter,
                          bool makeRelativeToDirectory)
{
    files.clear();

    std::vector<std::string> _files;
    
    list(directory.path(),
         _files,
         sortAlphaNumeric,
         pFilter,
         makeRelativeToDirectory);

    auto iter = _files.begin();

    while (iter != _files.end())
    {
        files.push_back(ofFile(*iter));
        ++iter;
    }
    
}


void DirectoryUtils::list(const std::string& directory,
                          std::vector<std::string>& files,
                          bool sortAlphaNumeric,
                          AbstractPathFilter* pFilter,
                          bool makeRelativeToDirectory)
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

        if (makeRelativeToDirectory)
        {
            for (auto& file : files)
            {
                file = makeRelativeTo(file, directory);
            }
        }

        if (sortAlphaNumeric)
        {
            // now sort the vector with the algorithm
            std::sort(files.begin(),
                      files.end(),
                      doj::alphanum_less<std::string>());
        }
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("DirectoryUtils::list") << exc.displayText();
    }

}


void DirectoryUtils::listRecursive(const std::string& directory,
                                   std::vector<std::string>& files,
                                   bool sortAlphaNumeric,
                                   AbstractPathFilter* pFilter,
                                   Poco::UInt16 maxDepth,
                                   TraversalOrder traversalOrder,
                                   bool makeRelativeToDirectory)
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

    if (makeRelativeToDirectory)
    {
        for (auto& file : files)
        {
            file = makeRelativeTo(file, directory);
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
                                   TraversalOrder traversalOrder,
                                   bool makeRelativeToDirectory)
{
    files.clear();

    std::vector<std::string> _files;

    listRecursive(directory.path(),
                  _files,
                  sortAlphaNumeric,
                  pFilter,
                  maxDepth,
                  traversalOrder,
                  makeRelativeToDirectory);

    auto iter = _files.begin();

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
                                   TraversalOrder traversalOrder,
                                   bool makeRelativeToDirectory)
{
	files.clear();

    std::vector<std::string> _files;

    listRecursive(directory.path(),
                  _files,
                  sortAlphaNumeric,
                  pFilter,
                  maxDepth,
                  traversalOrder,
                  makeRelativeToDirectory);

    auto iter = _files.begin();

    while (iter != _files.end())
    {
        files.push_back(Poco::File(*iter));
        ++iter;
    }
}



std::string DirectoryUtils::makeRelativeTo(const std::string& path,
                                           const std::string& base)
{
    // via http://stackoverflow.com/a/29221546/1518329
    std::filesystem::path from(ofToDataPath(base, true));
    std::filesystem::path to(ofToDataPath(path, true));

    std::filesystem::path result;

    // Start at the root path and while they are the same then do nothing
    // then when they first diverge take the remainder of the two path and
    // replace the entire from path with ".." segments.
    auto fromIter = from.begin();
    auto toIter = to.begin();

    // Loop through both
    while (fromIter != from.end() &&
           toIter != to.end() &&
           (*toIter) == (*fromIter))
    {
        ++toIter;
        ++fromIter;
    }

    std::filesystem::path finalPath;

    while (fromIter != from.end())
    {
        finalPath /= "..";
        ++fromIter;
    }

    while (toIter != to.end())
    {
        finalPath /= *toIter;
        ++toIter;
    }

    return finalPath.string();
}


} } // namespace ofx::IO
