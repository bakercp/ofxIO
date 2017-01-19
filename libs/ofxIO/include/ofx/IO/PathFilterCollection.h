//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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
