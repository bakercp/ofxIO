
//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/IO/FilteredStreams.h"


namespace ofx {
namespace IO {


FilteredInputStream::FilteredInputStream(std::istream& stream): _stream(stream)
{
}


FilteredInputStream::~FilteredInputStream()
{
}


void FilteredInputStream::push(std::unique_ptr<AbstractInputStreamFilter> filter)
{
    _filters.push_back(std::move(filter));
}


std::istream& FilteredInputStream::stream()
{
    std::istream* pStream = &_stream;;

    for (auto& filter: _filters)
    {
        pStream = &filter->filter(*pStream);
    }

    return *pStream;
}


FilteredOutputStream::FilteredOutputStream(std::ostream& stream): _stream(stream)
{
}


FilteredOutputStream::~FilteredOutputStream()
{
}


void FilteredOutputStream::push(std::unique_ptr<AbstractOutputStreamFilter> filter)
{
    _filters.push_back(std::move(filter));
}


std::ostream& FilteredOutputStream::stream()
{
    std::ostream* pStream = &_stream;;

    for (auto& filter: _filters)
    {
        pStream = &filter->filter(*pStream);
    }

    return *pStream;
}


} }  // namespace ofx::IO
