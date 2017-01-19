//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/StreamFilters.h"
#include "ofTypes.h"


#include "Poco/Exception.h"

namespace ofx {
namespace IO {


InflatingInputStreamFilter::InflatingInputStreamFilter(Poco::InflatingStreamBuf::StreamType type):
    _type(type)
{
}


InflatingInputStreamFilter::~InflatingInputStreamFilter()
{
}


std::istream& InflatingInputStreamFilter::filter(std::istream& stream)
{
    _stream = std::make_unique<Poco::InflatingInputStream>(stream, _type);
    return *_stream;
}


} }  // namespace ofx::IO
