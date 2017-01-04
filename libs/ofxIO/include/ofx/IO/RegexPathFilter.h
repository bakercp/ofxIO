//
// Copyright (c) 2009 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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


/// \brief A regular expression-based path filter.
class RegexPathFilter: public AbstractPathFilter
{
public:
    /// \brief Construct a new RegexPathFilter.
    /// \param pattern is the regular expression pattern.
    /// \param options for the regular expression.  Options
    ///        are defined in the Poco::RegularExpression class.
    /// \param optimize can be set to true when the Regex pattern
    ///        should be analyzed and optimized.
    /// \throws Poco::RegularExpressionException os thrown
    ///        if the pattern cannot be compiled.
    /// \sa Poco::RegularExpression
    RegexPathFilter(const std::string& pattern,
                    int options = 0,
                    bool optimize = true);

    /// \brief Destroys the regex path filter.
    virtual ~RegexPathFilter();

    /// \brief Accept a path based on a regular expression.
    /// \returns true iff the path is accepted by the path filter.
    bool accept(const Poco::Path& path) const override;

private:
    /// \brief the regular expression pointer.
	Poco::RegularExpression _regex;

};


} } // namespace ofx::IO
