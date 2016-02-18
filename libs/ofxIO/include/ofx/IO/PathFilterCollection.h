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


#pragma once


#include <set>
#include "Poco/Path.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


/// \brief A collection of path filters that can be executed at once.
///
/// In many cases functions are allowed to recieve a single AbstractPathFilter.
/// This class allows users to create a collection of AbstractPathFilters that
/// will be treated as a single filter.
class PathFilterCollection: public AbstractPathFilter
{
public:
    /// \brief Create an empty file filter collection.
    PathFilterCollection();

    /// \brief Destroy a file filter collection.
    /// \warning This class does not take ownership of the pointers in the
    /// collection and does not manage their memory.
    virtual ~PathFilterCollection();

    bool accept(const Poco::Path& path) const override;

    /// \brief Add a file filter to the collection.
    ///
    /// The owner of the filter must manage the memory of the filter and
    /// maintain the pointer's validity while used in this file filter
    /// collection.
    ///
    /// \param filter A pointer to the AbstractPathFilter to add.
    void addFilter(AbstractPathFilter* filter);

    /// \brief Remove a file filter from the collection.
    ///
    /// This does not delete or otherwise free the filter's memory.  The
    /// original owner of the filter is responsible for managing the filter's
    /// memory.
    ///
    /// \param filter A pointer to the AbstractPathFilter to remove.
    void removeFilter(AbstractPathFilter* filter);

private:
    /// \brief A set of file filters.
    std::set<AbstractPathFilter*> _filters;
    
};


} } // namespace ofx::IO
