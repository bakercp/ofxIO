//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <istream>
#include <memory>
#include "Poco/InflatingStream.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


class InflatingInputStreamFilter: public AbstractInputStreamFilter
{
public:
    InflatingInputStreamFilter(Poco::InflatingStreamBuf::StreamType type);

    virtual ~InflatingInputStreamFilter();

    std::istream& filter(std::istream& stream);

private:
    Poco::InflatingStreamBuf::StreamType _type;
    std::unique_ptr<Poco::InflatingInputStream> _stream;

};


} } // namespace ofx::IO
