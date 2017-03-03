//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/PollingThread.h"


namespace ofx {
namespace IO {


PollingThread::PollingThread(std::function<void()> threadedFunction,
                             uint64_t pollingInterval):
    Thread(threadedFunction),
    _maximumPollingCount(DEFAULT_MAXIMUM_POLLING_COUNT),
    _pollingCount(0),
    _pollingInterval(pollingInterval)
{
}


PollingThread::~PollingThread()
{
}


void PollingThread::setPollingInterval(uint64_t pollingInterval)
{
    _pollingInterval = pollingInterval;
}


uint64_t PollingThread::getPollingInterval() const
{
    return _pollingInterval;
}


void PollingThread::setMaximumPollingCount(int64_t maximumPollingCount)
{
    _maximumPollingCount = maximumPollingCount;
}


int64_t PollingThread::getMaximumPollingCount() const
{
    return _maximumPollingCount;
}


void PollingThread::reset()
{
    _pollingCount = 0;
}


uint64_t PollingThread::pollingCount() const
{
    return _pollingCount;
}


bool PollingThread::shouldRepeatWithDelay(uint64_t& delay)
{
    if (_maximumPollingCount >= 0 && _maximumPollingCount < _pollingCount)
    {
        return false;
    }

    delay = _pollingInterval;
    ++_pollingCount;
    return true;
}

} } // namespace ofx::IO
