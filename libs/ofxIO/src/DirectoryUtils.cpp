//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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

    std::vector<std::filesystem::path> _files;

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
        paths.push_back(iter->string());
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

    std::vector<std::filesystem::path> _files;

    list(directory.path(),
         _files,
         sortAlphaNumeric,
         pFilter,
         makeRelativeToDirectory);

    auto iter = _files.begin();

    while (iter != _files.end())
    {
        files.push_back(Poco::File(iter->string()));
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

    std::vector<std::filesystem::path> _files;
    
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


void DirectoryUtils::list(const std::filesystem::path& directory,
                          std::vector<std::filesystem::path>& files,
                          bool sortAlphaNumeric,
                          AbstractPathFilter* pFilter,
                          bool makeRelativeToDirectory)
{
    try
    {
        files.clear();

        std::filesystem::path _directory = ofToDataPath(directory, true);

        if (!std::filesystem::exists(_directory))
        {
            ofLogError("DirectoryUtils::list") << _directory << " not found.";
            return;
        }

        Poco::DirectoryIterator iter(_directory.string());
        Poco::DirectoryIterator endIter;

        while (iter != endIter)
        {
            if (!pFilter || pFilter->accept((*iter).path()))
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

        if (sortAlphaNumeric) _sortAlphaNumeric(files);
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("DirectoryUtils::list") << exc.displayText();
    }

}


void DirectoryUtils::listRecursive(const std::filesystem::path& directory,
                                   std::vector<std::filesystem::path>& files,
                                   bool sortAlphaNumeric,
                                   AbstractPathFilter* pFilter,
                                   Poco::UInt16 maxDepth,
                                   TraversalOrder traversalOrder,
                                   bool makeRelativeToDirectory)
{
    files.clear();

    std::filesystem::path _directory = ofToDataPath(directory, true);

    if (traversalOrder == SIBLINGS_FIRST)
    {
        SiblingsFirstRecursiveDirectoryIterator iter(_directory.string(), maxDepth);
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
        SimpleRecursiveDirectoryIterator iter(_directory.string(), maxDepth);
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

    if (sortAlphaNumeric) _sortAlphaNumeric(files);

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

    std::vector<std::filesystem::path> _files;

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

    std::vector<std::filesystem::path> _files;

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
        files.push_back(Poco::File(iter->string()));
        ++iter;
    }
}



std::filesystem::path DirectoryUtils::makeRelativeTo(const std::filesystem::path& path,
                                                     const std::filesystem::path& base)
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

    return finalPath;
}


void DirectoryUtils::_sortAlphaNumeric(std::vector<std::filesystem::path>& paths)
{
    std::sort(paths.begin(),
              paths.end(),
              [](const std::filesystem::path& a,
                 const std::filesystem::path& b) {
                  return doj::alphanum_comp(a.string(), b.string()) < 0;
              });
}


} } // namespace ofx::IO
