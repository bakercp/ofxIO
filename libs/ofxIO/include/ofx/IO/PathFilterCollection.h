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


#include <set>
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/RegularExpression.h"
#include "Poco/String.h"
#include "Poco/UTF8String.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


class PathFilterCollection: public AbstractPathFilter
{
    /// \brief A collection of path filters that can be executed at once.
    /// \details In many cases functions are allowed to recieve a single
    /// AbstractPathFilter.  This class allows users to create a collection
    /// of AbstractPathFilters that will be treated as a single filter.
public:
    PathFilterCollection()
        ///< \brief Create an empty file filter collection.
    {
    }

    virtual ~PathFilterCollection()
        ///< \brief Destroy a file filter collection.
        ///< \warning This class does not take ownership of
        ///< the pointers in the collection and does
        ///< not manage their memory.
    {
    }

    bool accept(const Poco::Path& path) const
        ///< \returns true iff the all path filters
        ///< in the collection also return true.
    {
        std::set<AbstractFileFilter*>::iterator iter = _filters.begin();

        while (iter != _filters.end())
        {
            if (!(*iter)->accept(file))
            {
                return false;
            }
            ++iter;
        }

        return true;
    }

    void addFilter(AbstractPathFilter* filter)
        ///< Add a file filter to the collection. The owner of the filter
        ///< must manage the memory of the filter and maintain the pointer's
        ///< validity while used in this file filter collection.
    {
        _filters.insert(filter);
    }

    void removeFilter(AbstractPathFilter* filter)
        ///< Remove a file filter from the collection.  This does not
        ///< delete of free the filter's memory.  The original owner of the
        ///< filter is responsible for managing the file filter's memeory.
    {
        _filters.erase(filter);
    }

private:
    std::set<AbstractPathFilter*> _filters; ///> A set of file filters.
    
};


class FileExtensionFilter: public AbstractPathFilter
{
public:

    FileExtensionFilter(): _ignoreCase(true), _includeMatches(true)
    {
    }

    FileExtensionFilter(bool ignoreCase, bool includeMatches = true):
        _ignoreCase(ignoreCase),
        _includeMatches(includeMatches)
    {
    }

    virtual ~FileExtensionFilter()
    {
    }

    bool accept(const Poco::Path& path) const
    {
        std::string extension = path.getExtension();

        std::set<std::string>::iterator iter = _extensions.begin();

        while(iter != _extensions.end())
        {
            bool match = false;

            if(_ignoreCase)
            {
                match = (0 == Poco::UTF8::icompare(extension,*iter));
            }
            else
            {
                match = (extension == *iter);
            }

            if(_includeMatches && match)
            {
                return true;
            }

            ++iter;
        }

        return !_includeMatches;

    }

    void addExtension(const std::string& extension)
    {
        _extensions.insert(extension);
    }

    void removeExtension(const std::string& extension)
    {
        _extensions.erase(extension);
    }

    void setIgnoreCase(bool ignoreCase)
    {
        _ignoreCase = ignoreCase;
    }

    bool getIgnoreCase() const
    {
        return _ignoreCase;
    }

private:
    bool _ignoreCase;
    bool _includeMatches;
    std::set<std::string> _extensions;
    
};


class HiddenFileFilter: public AbstractPathFilter
{
public:
    HiddenFileFilter()
    {
    }

    virtual ~HiddenFileFilter()
    {
    }

    bool accept(const Poco::Path& file) const
    {
        return file.isHidden();
    }
    
};


class DirectoryFilter: public AbstractPathFilter
{
public:
    DirectoryFilter()
    {
    }

    virtual ~DirectoryFilter()
    {
    }

    bool accept(const Poco::Path& file) const
    {
        return file.isDirectory();
    }
    
};


class DeviceFilter: public AbstractPathFilter
{
public:
    DeviceFilter()
    {
    }

    virtual ~DeviceFilter()
    {
    }

    bool accept(const Poco::Path& path) const
    {
        return file.isDevice();
    }
    
};


class LinkFilter: public AbstractPathFilter
{
public:
    LinkFilter()
    {
    }

    virtual ~LinkFilter()
    {
    }

    bool accept(const Poco::Path& path) const
    {
        return file.isLink();
    }
    
};


class RegexPathFilter: public AbstractPathFilter
{
public:
    RegexPathFilter(const std::string& pattern,
                    int options = 0,
                    bool study = true):
        _regex(new Poco::RegularExpression(pattern, options, study))
        ///< \param study is set to true when the user wants to  
    {
    }

    virtual ~RegexPathFilter()
    {
        delete _regex;
    }

    bool accept(const Poco::File& file) const
    {
        return _regex->match(file.path());
    }

private:
    Poco::RegularExpression* _regex;
    
};



} } // namespace ofx::IO
