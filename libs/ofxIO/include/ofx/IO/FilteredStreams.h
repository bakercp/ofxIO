// =============================================================================
//
// Copyright (c) 2016 Christopher Baker <http://christopherbaker.net>
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


#include <istream>
#include <memory>
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


class FilteredInputStream
{
public:
    FilteredInputStream(std::istream& stream);

    virtual ~FilteredInputStream();

    void push(std::unique_ptr<AbstractInputStreamFilter> filter);

    /// \returns the original stream with all filters applied.
    std::istream& stream();

    operator std::istream&()
    {
        return stream();
    }

//    template<typename ParameterType>
//    inline ofParameter<ParameterType>::operator const ParameterType & () const{
//        return obj->value;
//    }

private:
    std::vector<std::unique_ptr<AbstractInputStreamFilter>> _filters;

    std::istream& _stream;

};


class FilteredOutputStream
{
public:
    FilteredOutputStream(std::ostream& stream);

    virtual ~FilteredOutputStream();

    void push(std::unique_ptr<AbstractOutputStreamFilter> filter);

    /// \returns the original stream with all filters applied.
    std::ostream& stream();

    operator std::ostream&()
    {
        return stream();
    }

private:
    std::vector<std::unique_ptr<AbstractOutputStreamFilter>> _filters;
    
    std::ostream& _stream;
    
};


} } // namespace ofx::IO
