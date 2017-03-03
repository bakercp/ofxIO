//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/BackoffStrategy.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>


namespace ofx {
namespace IO {


BackoffStrategy::BackoffStrategy():
    BackoffStrategy(BackoffStrategy::Method::EXPONENTIAL,
                    DEFAULT_INITIAL_DELAY,
                    DEFAULT_MAXIMUM_RETIRES,
                    DEFAULT_MAXIMUM_DELAY)
{
}


BackoffStrategy::BackoffStrategy(Method method,
                                 uint64_t initialDelay,
                                 uint64_t maximumDelay,
                                 uint64_t maximumRetries):
    _method(method),
    _initialDelay(initialDelay),
    _maximumDelay(maximumDelay),
    _maximumRetries(maximumRetries)
{
}


void BackoffStrategy::setBackoffMethod(BackoffStrategy::Method method)
{
    reset();
    _method = method;
}


BackoffStrategy::Method BackoffStrategy::getBackoffMethod() const
{
    return _method;
}


void BackoffStrategy::setInitialDelay(uint64_t initialDelay)
{
    reset();
    _initialDelay = initialDelay;
}


uint64_t BackoffStrategy::getInitialDelay() const
{
    return _initialDelay;
}


void BackoffStrategy::setMaximumDelay(uint64_t maximumDelay)
{
    return _maximumDelay;
}


uint64_t BackoffStrategy::getMaximumDelay() const
{
    return _maximumDelay;
}


void BackoffStrategy::setMaximumRetries(uint64_t maximumRetries)
{
    reset();
    _maximumRetries = maximumRetries;
}


uint64_t BackoffStrategy::getMaximumRetries() const
{
    return _maximumRetries;
}


void BackoffStrategy::reset()
{
    _retryNumber = 0;
}


void BackoffStrategy::abort()
{
    _retryNumber = _maximumRetries;
}

bool BackoffStrategy::failed() const
{
    return _retryNumber >= _maximumRetries;
}


std::size_t BackoffStrategy::remaining() const
{
    if (_maximumRetries == 0)
    {
        return std::numeric_limits<std::size_t>::max();
    }

    return _maximumRetries - _retryNumber;
}


uint64_t BackoffStrategy::next()
{
    if (!failed())
    {
        switch (_method)
        {
            case Method::LINEAR:
                _lastDelay += _initialDelay;
                break;
            case Method::EXPONENTIAL:
                _lastDelay = std::pow(2, std::min(_maximumRetries, _retryNumber)) * _initialDelay;
                break;
            case Method::FIBONACCI:
                _lastDelay += _lastDelay;
                break;
        }

        return std::min(_maximumDelay, _lastDelay);
    }

    throw std::range_error("Backoff strategy failed.");
}


} }  // namespace ofx::IO
