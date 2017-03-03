//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once



#include <thread>
#include "ofEvents.h"


namespace ofx {
namespace IO {


/// \brief A simple thread class.
class Thread
{
public:
    /// \brief Create a thread with the given function.
    /// \param threadedFunction The function to run in a seperate thread.
    Thread(std::function<void()> threadedFunction);

    /// \brief Destroy the Thread.
    virtual ~Thread();

    /// \brief Stop the thread and block until stopped.
    void stopAndJoin();

    /// \brief Stop the thread, without blocking.
    void stop();

    /// \brief Start the thread, if not already running.
    void start();

    /// \returns true if the thread is running.
    bool isRunning() const;

protected:
    /// \brief Update callback from the main thread.
    ///
    /// This is used to synchronize message delivery.
    ///
    /// \param evt The event passed from the main loop.
    virtual void onUpdate();

    /// \brief Exit callback from the main thread.
    ///
    /// This is called before the thread has been stopped and joined.
    ///
    /// \param evt The event passed from the main loop.
    virtual void onExit();

    /// \brief Called from the thread after _isRunning is true before _threadedFunction is called.
    /// \note This is called from within the thread loop.
    virtual void onThreadStarted();

    /// \brief Called when the thread stop has been requested.
    /// \note This will be called from outside of the thread, so subclasses must
    /// take care to protect data via mutexes, locks, etc.
    virtual void onStopRequested();

    /// \brief Called when the thread has returned from the _threadedFunctionPtr.
    /// \note This is called from within the thread loop.
    virtual void onThreadFinished();

    /// \brief Called after the thread has been joined after calling stopAndJoin.
    /// \note This will be called from outside of the thread, so subclasses must
    /// take care to protect data via mutexes, locks, etc.
    virtual void onThreadJoined();

    /// \brief Allow subclasses to request a the repetition of the thread.
    ///
    /// By default, this returns false.
    ///
    /// \param delay The delay in milliseconds for repeating the function.
    /// \returns true if the threaded function should be repeated upon completion.
    virtual bool shouldRepeatWithDelay(uint64_t& delay);

    /// \brief The std::mutex.
    mutable std::mutex mutex;

    /// \brief The condition variable.
    mutable std::condition_variable condition;

private:
    /// \brief Update callback from the main thread.
    ///
    /// This is used to synchronize message delivery.
    ///
    /// \param evt The event passed from the main loop.
    void _update(ofEventArgs& evt);

    /// \brief Exit callback from the main thread.
    ///
    /// This is used to make sure the thread is shut down correctly.
    ///
    /// \param evt The event passed from the main loop.
    void _exit(ofEventArgs& evt);

    /// \brief The exit listener handle.
    ofEventListener _exitListener;

    /// \brief The update listener handle.
    ofEventListener _updateListener;

    /// \brief The function to be run in a thread.
    std::function<void()> _threadedFunction;

    /// \brief The management thread.
    ///
    /// When start() is called, this marks the Thread as running, executes
    /// preThread(), then calls _threadedFunctionPtr, and then postThread()
    /// upon the return _threadedFunctionPtr.
    void _run();

    /// \brief The std::thread used.
    std::thread _thread;

    /// \brief True if the thread is running.
    std::atomic<bool> _isRunning;

};


} } // namespace ofx::IO
