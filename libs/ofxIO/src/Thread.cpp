//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/Thread.h"
#include "ofLog.h"


namespace ofx {
namespace IO {


Thread::Thread(std::function<void()> threadedFunction):
    _exitListener(ofEvents().exit.newListener(this, &Thread::_exit)),
    _updateListener(ofEvents().update.newListener(this, &Thread::_update)),
    _threadedFunction(threadedFunction),
    _isRunning(false)
{
}


Thread::~Thread()
{
    stopAndJoin();
}


void Thread::stopAndJoin()
{
    stop();

    try
    {
        _thread.join();
        onThreadJoined();
    }
    catch (...)
    {
        ofLogVerbose("Thread::stopAndJoin") << "Thread join failed.";
    }
}


void Thread::stop()
{
    if (_isRunning)
    {
        _isRunning = false;
        condition.notify_all();
        onStopRequested();
    }
}


void Thread::start()
{
    if (!_isRunning)
    {
        _thread = std::thread(&Thread::_run, this);
    }
}


bool Thread::isRunning() const
{
    return _isRunning;
}


void Thread::onUpdate()
{
}


void Thread::onExit()
{
}


void Thread::onThreadStarted()
{
    ofLogVerbose("Thread::onThreadStarted") << "On thread started.";
}


void Thread::onStopRequested()
{
    ofLogVerbose("Thread::onStopRequested") << "On stop requested.";
}


void Thread::onThreadFinished()
{
    ofLogVerbose("Thread::onThreadFinished") << "On thread finished.";
}


void Thread::onThreadJoined()
{
    ofLogVerbose("Thread::onThreadJoined") << "On thread joined.";
}


bool Thread::shouldRepeatWithDelay(uint64_t& delay)
{
    return false;
}


void Thread::_update(ofEventArgs& evt)
{
    onUpdate();
}


void Thread::_exit(ofEventArgs& evt)
{
    onExit();
    stopAndJoin();
}


void Thread::_run()
{
    _isRunning = true;

    onThreadStarted();

    bool repeat = true;
    uint64_t delay = 0;

    do
    {
        try
        {
            if (_threadedFunction)
            {
                _threadedFunction();
            }
            else throw std::runtime_error("The _threadedFunction is a nullptr");
        }
        catch (const std::exception& exc)
        {
            ofLogError("Thread::_run") << "Exception: " << exc.what();

        }
        catch (...)
        {
            ofLogError("Thread::_run") << "Unknown exception caught.";
        }

        repeat = shouldRepeatWithDelay(delay);

        if (repeat)
        {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait_for(lock, std::chrono::milliseconds(delay));
        }
    } while (_isRunning && repeat);

    _isRunning = false;

    onThreadFinished();
}


} } // namespace ofx::IO
