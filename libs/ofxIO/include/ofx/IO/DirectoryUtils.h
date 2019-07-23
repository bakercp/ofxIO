//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "Poco/DirectoryIterator.h"
#include "ofx/RecursiveDirectoryIterator.h"
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
        INIFINITE_DEPTH = SimpleRecursiveDirectoryIterator::D_INFINITE
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
    /// \param makeRelativeToPath True if the output files should be relative to
    ///        \p directory.
    static void list(const AbstractSearchPath& path,
                     std::vector<Poco::Path>& paths,
                     bool sortAlphaNumeric = false,
                     AbstractPathFilter* pFilter = nullptr,
                     Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                     TraversalOrder traversalOrder = CHILDREN_FIRST,
                     bool makeRelativeToPath = false);

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
    /// \param makeRelativeToDirectory True if the output files should be relative to
    ///        \p directory.
    static void list(const Poco::File& directory,
                     std::vector<Poco::File>& files,
                     bool sortAlphaNumeric = false,
                     AbstractPathFilter* pFilter = nullptr,
                     bool makeRelativeToDirectory = false);

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
    /// \param makeRelativeToDirectory True if the output files should be relative to
    ///        \p directory.
    static void list(const ofFile& directory,
                     std::vector<ofFile>& files,
                     bool sortAlphaNumeric = false,
                     AbstractPathFilter* pFilter = nullptr,
                     bool makeRelativeToDirectory = false);

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
    /// \param makeRelativeToDirectory True if the output files should be relative to
    ///        \p directory.
    static void list(const std::filesystem::path& directory,
                     std::vector<std::filesystem::path>& files,
                     bool sortAlphaNumeric = false,
                     AbstractPathFilter* pFilter = nullptr,
                     bool makeRelativeToDirectory = false);

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
    /// \param makeRelativeToDirectory True if the output files should be relative to
    ///        \p directory.
    static void listRecursive(const Poco::File& directory,
                              std::vector<Poco::File>& files,
                              bool sortAlphaNumeric = false,
                              AbstractPathFilter* pFilter = nullptr,
                              Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                              TraversalOrder traversalOrder = CHILDREN_FIRST,
                              bool makeRelativeToDirectory = false);

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
    /// \param makeRelativeToDirectory True if the output files should be relative to
    ///        \p directory.
    static void listRecursive(const ofFile& directory,
                              std::vector<ofFile>& files,
                              bool sortAlphaNumeric = false,
                              AbstractPathFilter* pFilter = nullptr,
                              Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                              TraversalOrder traversalOrder = CHILDREN_FIRST,
                              bool makeRelativeToDirectory = false);

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
    /// \param makeRelativeToDirectory True if the output files should be relative to
    ///        \p directory.
    static void listRecursive(const std::filesystem::path& directory,
                              std::vector<std::filesystem::path>& files,
                              bool sortAlphaNumeric = false,
                              AbstractPathFilter* pFilter = nullptr,
                              Poco::UInt16 maxDepth = INIFINITE_DEPTH,
                              TraversalOrder traversalOrder = CHILDREN_FIRST,
                              bool makeRelativeToDirectory = false);

    /// \brief Make \p path relative to \p base.
    /// \param path The path to make relative.
    /// \param base The reference base path used to make \p path relative.
    /// \returns A \p path made relative to \p base.
    /// \note This functionality comes with boost::filesystem::relative > 1.6.
    static std::filesystem::path makeRelativeTo(const std::filesystem::path& path,
                                                const std::filesystem::path& base);
private:
    static void _sortAlphaNumeric(std::vector<std::filesystem::path>& paths);

};


} } // namespace ofx::IO
