//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/IO/PollingThread.h"
#include "ofMath.h"


namespace ofx {
namespace IO {


PollingThread::PollingThread(std::function<void()> threadedFunction,
                             uint64_t pollingInterval,
                             uint64_t pollingIntervalRandomMinimum,
                             uint64_t pollingIntervalRandomMaximum):
    Thread(threadedFunction),
    _maximumPollingCount(DEFAULT_MAXIMUM_POLLING_COUNT),
    _pollingCount(0),
    _pollingInterval(pollingInterval),
    _pollingIntervalRandomMinimum(pollingIntervalRandomMinimum),
    _pollingIntervalRandomMaximum(pollingIntervalRandomMaximum)
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
    if (_pollingIntervalRandomMinimum > 0 ||
        _pollingIntervalRandomMaximum > 0)
    {
        return _pollingInterval + ofRandom(_pollingIntervalRandomMinimum, _pollingIntervalRandomMaximum);
    }
    else return _pollingInterval;
}


void PollingThread::setPollingIntervalRandomMinimum(int64_t value)
{
    _pollingIntervalRandomMinimum = value;
}


int64_t PollingThread::getPollingIntervalRandomMinimum() const
{
    return _pollingIntervalRandomMinimum;
}


void PollingThread::setPollingIntervalRandomMaximum(int64_t value)
{
    _pollingIntervalRandomMaximum = value;
}


int64_t PollingThread::getPollingIntervalRandomMaximum() const
{
    return _pollingIntervalRandomMaximum;
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

    delay = getPollingInterval();
    ++_pollingCount;
    return true;
}

} } // namespace ofx::IO
