//
// Copyright (c) 2010 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <cstdarg>
#include "ofLog.h"
#include "ofEvents.h"
#include "ofx/IO/ThreadChannel.h"


namespace ofx {
namespace IO {


/// \brief A class representing a single logger message.
/// \todo Use Poco::Message
class LoggerMessage
{
public:
    LoggerMessage();
    LoggerMessage(ofLogLevel level,
                  const std::string& module,
                  const std::string& message,
                  const std::chrono::system_clock::time_point& timestamp = std::chrono::system_clock::now(),
                  std::thread::id threadId = std::this_thread::get_id());

    virtual ~LoggerMessage();
    ofLogLevel level() const;
    std::string module() const;
    std::string message() const;
    std::chrono::system_clock::time_point timestamp() const;
    std::thread::id threadId() const;

private:
    ofLogLevel _level = OF_LOG_NOTICE;
    std::string _module;
    std::string _message;
    std::chrono::system_clock::time_point _timestamp;
    std::thread::id _threadId;

};


/// \brief The class representing a base thread safe console logger channel.
///
/// This logging channel captures logging info and synchronizes it with the main
/// thread.
class BaseThreadsafeLoggerChannel: public ofBaseLoggerChannel
{
public:
    /// \brief Create a default BaseThreadsafeLoggerChannel.
    BaseThreadsafeLoggerChannel();

    /// \brief Destroy the BaseThreadsafeLoggerChannel.
    virtual ~BaseThreadsafeLoggerChannel();

    virtual void log(ofLogLevel level,
                     const std::string& module,
                     const std::string & message) override;

    virtual void log(ofLogLevel level,
                     const std::string& module,
                     const char* format, ...)  OF_PRINTF_ATTR(4, 5);

    virtual void log(ofLogLevel level,
                     const std::string& module,
                     const char* format, std::va_list args) ;

    /// \brief Set the poll interval in milliseconds.
    /// \param interval The poll interval in milliseconds.
    void setUpdateInterval(uint64_t updateInterval);

    /// \returns the poll interval in milliseconds.
    uint64_t getUpdateInterval() const;

    /// \returns the number of LoggerMessages that are qeued for output.
    std::size_t size() const;

    enum
    {
        /// \brief The default update interval in milliseconds.
        ///
        /// 0 milliseconds indicates an update interval equal to that of the
        /// main update() rate.
        DEFAULT_UPDATE_INTERVAL = 0
    };

protected:
    /// \brief The output method for subclasses.
    ///
    /// \param message The logger message to log.
    virtual void output(const LoggerMessage& message) = 0;

private:
    void _update(ofEventArgs& evt);
    void _exit(ofEventArgs& evt);

    void _receive();

    ofEventListener _updateListener;
    ofEventListener _exitListener;

    ThreadChannel<LoggerMessage> _messages;

    uint64_t _lastUpdate = 0;
    uint64_t _updateInterval = DEFAULT_UPDATE_INTERVAL;
};


/// \brief The class representing a base thread safe console logger channel.
///
/// This logging channel captures logging info and synchronizes it with the main
/// thread.
class ThreadsafeConsoleLoggerChannel: public BaseThreadsafeLoggerChannel
{
public:
    using BaseThreadsafeLoggerChannel::BaseThreadsafeLoggerChannel;
    virtual ~ThreadsafeConsoleLoggerChannel();

protected:
    virtual void output(const LoggerMessage& message) override;

};


/// \brief A logger channel that logs its messages to a log file.
class ThreadsafeFileLoggerChannel: public BaseThreadsafeLoggerChannel
{
public:
    /// \brief Create an ofFileLoggerChannel with parameters.
    /// \param path The file path for the log file.
    /// \param append True if the log data should be added to an existing file.
    ThreadsafeFileLoggerChannel(const std::filesystem::path& path, bool append);

    /// \brief Destroy the file logger channel.
    virtual ~ThreadsafeFileLoggerChannel();

    /// \brief Set the log file.
    /// \param path The file path for the log file.
    /// \param append True if the log data should be added to an existing file.
    void setFile(const std::filesystem::path & path, bool append = false);

    /// \brief CLose the log file.
    void close();

protected:
    virtual void output(const LoggerMessage& message) override;

private:
    /// \brief The location of the log file.
    ofFile file;
    
};


} } // namespace ofx::IO
