//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


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
