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
    bool accept(const Poco::Path& path) const;

private:
    /// \brief the regular expression pointer.
    Poco::RegularExpression* _pRegex;

};


} } // namespace ofx::IO
