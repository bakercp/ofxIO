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
#include "Poco/Path.h"
#include "Poco/String.h"
#include "Poco/UTF8String.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


class FileExtensionFilter: public AbstractPathFilter
    /// \brief A path filter to accept files with certain extensions.
{
public:
    FileExtensionFilter();
        ///< \brief Construct an empty file extension filter.

    FileExtensionFilter(bool ignoreCase, bool acceptMatches = true);
        ///< \brief Construct a file extension filter.
        ///< \param ignoreCase will ingore case when comparing file extensions.
        ///< \param acceptMatches will accept matches. When acceptMatches is
        ///<        false, matching extensions are rejected.

    virtual ~FileExtensionFilter();
        ///< \brief Destroy a file extension filter.

    bool accept(const Poco::Path& path) const;
        ///< \returns true iff the path extension matches one from the list
        ///<        and the additional match criteria (ignoreCase and
        ///<        acceptMatches) are also satisfied.

    void addExtension(const std::string& extension);
        ///< \brief Add an extension to the list of extensions.
        ///< \param extension to be added to the list (e.g. ".jpg").

    void removeExtension(const std::string& extension);
        ///< \brief Remove an extension from the list of extensions.
        ///< \param extension to be removed from the list (e.g. ".jpg").

    void setIgnoreCase(bool ignoreCase);
        ///< \param ignoreCase will ingore case when comparing file extensions.

    bool getIgnoreCase() const;
        ///< \returns true if the file extension case will be ignored.

private:
    bool _ignoreCase;
    bool _acceptMatches;
    std::set<std::string> _extensions;
    
};


} } // namespace ofx::IO
