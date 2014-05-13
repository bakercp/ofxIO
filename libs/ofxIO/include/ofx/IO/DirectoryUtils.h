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


class AbstractPathFilter;


/// \brief A collection of utilities for working with directories.
class DirectoryUtils
{
public:
    enum
    {
        /// \brief When recursively listing a directory, do not limit the dept.
        INIFINITE_DEPTH = Poco::SimpleRecursiveDirectoryIterator::D_INFINITE
    };

    /// \brief The order of directory listing traversal.
    enum TraversalOrder
    {
        /// \brief When recursively listing a directory, list sibling
        ///     directories first.
        SIBLINGS_FIRST = 0,
        /// \brief When recursively listing a directory,
        ///     list child directories first.
        CHILDREN_FIRST
    };

    /// \brief List the contents of a path.
    /// \param path is the path of the directory to list.  If enabled,
    ///        the AbstractSearchPath will be searched recursively.
    /// \param paths is an empty vector of paths to be filled.
    /// \param sortAlphaNumeric enables alphanumeric sorting.  The
    ///        Alphanum Algorithm is an improved sorting algorithm for
    ///        strings containing numbers.  Instead of sorting numbers in
    ///        ASCII order like a standard sort, this algorithm sorts
    ///        numbers in numeric order.
    /// \param pFilter will allow only certain paths to be included
    ///        in the results.
    /// \param maxDepth determines the depth of the recursion during
    ///        recursive searches.
    /// \param traversalOrder determines the order of traversal during
    ///        recursive searches.
    static void list(const AbstractSearchPath& path,
                     std::vector<Poco::Path>& paths,
                     bool sortAlphaNumeric = false,
                     AbstractPathFilter* pFilter = 0,
                     Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                     TraversalOrder traversalOrder = CHILDREN_FIRST);

    /// \brief List the contents of a directory.
    /// \param directory is the path of the directory to list.
    /// \param files is an empty vector of files to be filled.
    /// \param sortAlphaNumeric enables alphanumeric sorting.  The
    ///        Alphanum Algorithm is an improved sorting algorithm for
    ///        strings containing numbers.  Instead of sorting numbers in
    ///        ASCII order like a standard sort, this algorithm sorts
    ///        numbers in numeric order.
    /// \param pFilter will allow only certain paths to be included
    ///        in the results.
    static void list(const Poco::File& directory,
                     std::vector<Poco::File>& files,
                     bool sortAlphaNumeric = false,
                     AbstractPathFilter* pFilter = 0);

    /// \brief List the contents of a directory.
    /// \param directory is the path of the directory to list.
    /// \param files is an empty vector of files to be filled.
    /// \param sortAlphaNumeric enables alphanumeric sorting.  The
    ///        Alphanum Algorithm is an improved sorting algorithm for
    ///        strings containing numbers.  Instead of sorting numbers in
    ///        ASCII order like a standard sort, this algorithm sorts
    ///        numbers in numeric order.
    /// \param pFilter will allow only certain paths to be included
    ///        in the results.
    static void list(const ofFile& directory,
                     std::vector<ofFile>& files,
                     bool sortAlphaNumeric = false,
                     AbstractPathFilter* pFilter = 0);

    /// \brief List the contents of a path.
    /// \param directory is the path of the directory to list.
    /// \param files is an empty vector of path strings to be filled.
    /// \param sortAlphaNumeric enables alphanumeric sorting.  The
    ///        Alphanum Algorithm is an improved sorting algorithm for
    ///        strings containing numbers.  Instead of sorting numbers in
    ///        ASCII order like a standard sort, this algorithm sorts
    ///        numbers in numeric order.
    /// \param pFilter will allow only certain paths to be included
    ///        in the results.
    static void list(const std::string& directory,
                     std::vector<std::string>& files,
                     bool sortAlphaNumeric = false,
                     AbstractPathFilter* pFilter = 0);

    /// \brief Recursively list the contents of a path.
    /// \param directory is the path of the directory to list.
    /// \param files is an empty vector of path strings to be filled.
    /// \param sortAlphaNumeric enables alphanumeric sorting.  The
    ///        Alphanum Algorithm is an improved sorting algorithm for
    ///        strings containing numbers.  Instead of sorting numbers in
    ///        ASCII order like a standard sort, this algorithm sorts
    ///        numbers in numeric order.
    /// \param pFilter will allow only certain paths to be included
    ///        in the results.
    /// \param maxDepth determines the depth of the recursion during
    ///        recursive searches.
    /// \param traversalOrder determines the order of traversal during
    ///        recursive searches.
    static void listRecursive(const Poco::File& directory,
                              std::vector<Poco::File>& files,
                              bool sortAlphaNumeric = false,
                              AbstractPathFilter* pFilter = 0,
                              Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                              TraversalOrder traversalOrder = CHILDREN_FIRST);

    /// \brief Recursively list the contents of a path.
    /// \param directory is the path of the directory to list.
    /// \param files is an empty vector of path strings to be filled.
    /// \param sortAlphaNumeric enables alphanumeric sorting.  The
    ///        Alphanum Algorithm is an improved sorting algorithm for
    ///        strings containing numbers.  Instead of sorting numbers in
    ///        ASCII order like a standard sort, this algorithm sorts
    ///        numbers in numeric order.
    /// \param pFilter will allow only certain paths to be included
    ///        in the results.
    /// \param maxDepth determines the depth of the recursion during
    ///        recursive searches.
    /// \param traversalOrder determines the order of traversal during
    ///        recursive searches.
    static void listRecursive(const ofFile& directory,
                              std::vector<ofFile>& files,
                              bool sortAlphaNumeric = false,
                              AbstractPathFilter* pFilter = 0,
                              Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                              TraversalOrder traversalOrder = CHILDREN_FIRST);

    /// \brief Recursively list the contents of a path.
    /// \param directory is the path of the directory to list.
    /// \param files is an empty vector of path strings to be filled.
    /// \param sortAlphaNumeric enables alphanumeric sorting.  The
    ///        Alphanum Algorithm is an improved sorting algorithm for
    ///        strings containing numbers.  Instead of sorting numbers in
    ///        ASCII order like a standard sort, this algorithm sorts
    ///        numbers in numeric order.
    /// \param pFilter will allow only certain paths to be included
    ///        in the results.
    /// \param maxDepth determines the depth of the recursion during
    ///        recursive searches.
    /// \param traversalOrder determines the order of traversal during
    ///        recursive searches.
    static void listRecursive(const std::string& directory,
                              std::vector<std::string>& files,
                              bool sortAlphaNumeric = false,
                              AbstractPathFilter* pFilter = 0,
                              Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                              TraversalOrder traversalOrder = CHILDREN_FIRST);
};


} } // namespace ofx::IO
