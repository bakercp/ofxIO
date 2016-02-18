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
#include "Poco/File.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


/// \brief A path filter to accept directory paths.
class DirectoryFilter: public AbstractPathFilter
{
public:
    /// \brief Construct a directory filter.
    DirectoryFilter(bool acceptMatches = true);

    /// \brief Destroys a directory filter.
    virtual ~DirectoryFilter();

    /// \brief Accept a path based if it represents a directory.
    /// \returns true iff the path represents a directory.
    bool accept(const Poco::Path& path) const override;

private:
	/// \brief true iff matches should be accepted,
	/// otherwise false iff matches should be rejected.
	bool _acceptMatches;

};


} } // namespace ofx::IO
