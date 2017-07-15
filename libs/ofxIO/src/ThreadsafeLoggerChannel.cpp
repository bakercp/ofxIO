//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/ThreadsafeLoggerChannel.h"


namespace ofx {
namespace IO {


LoggerMessage::LoggerMessage():
    LoggerMessage(OF_LOG_NOTICE,
                  "",
                  "",
                  std::chrono::system_clock::now(),
                  std::this_thread::get_id())
{
}


LoggerMessage::LoggerMessage(ofLogLevel level,
                             const std::string& module,
                             const std::string& message,
                             const std::chrono::system_clock::time_point& timestamp,
                             std::thread::id threadId):
    _level(level),
    _module(module),
    _message(message),
    _timestamp(timestamp),
    _threadId(threadId)
{
}


LoggerMessage::~LoggerMessage()
{
}


ofLogLevel LoggerMessage::level() const
{
    return _level;
}


std::string LoggerMessage::module() const
{
    return _module;
}


std::string LoggerMessage::message() const
{
    return _message;
}


std::chrono::system_clock::time_point LoggerMessage::timestamp() const
{
    return _timestamp;
}


std::thread::id LoggerMessage::threadId() const
{
    return _threadId;
}


BaseThreadsafeLoggerChannel::BaseThreadsafeLoggerChannel():
    _updateListener(ofEvents().update.newListener(this, &BaseThreadsafeLoggerChannel::_update))
    _exitListener(ofEvents().exit.newListener(this, &BaseThreadsafeLoggerChannel::_exit)),
{
}


BaseThreadsafeLoggerChannel::~BaseThreadsafeLoggerChannel()
{
}


void BaseThreadsafeLoggerChannel::log(ofLogLevel level,
                                      const std::string& module,
                                      const std::string& message)
{
    _messages.send(LoggerMessage(level, module, message));
}


void BaseThreadsafeLoggerChannel::log(ofLogLevel level,
                                      const std::string& module,
                                      const char* format, ...)
{
    va_list args;
    va_start(args, format);
    log(level, module, format, args);
    va_end(args);
}


void BaseThreadsafeLoggerChannel::log(ofLogLevel level,
                                      const std::string& module,
                                      const char* format, std::va_list args)
{
    log(level, module, ofVAArgsToString(format, args));
}


void BaseThreadsafeLoggerChannel::setUpdateInterval(uint64_t updateInterval)
{
    _updateInterval = updateInterval;
}


uint64_t BaseThreadsafeLoggerChannel::getUpdateInterval() const
{
    return _updateInterval;
}


std::size_t BaseThreadsafeLoggerChannel::size() const
{
    return _messages.size();
}


void BaseThreadsafeLoggerChannel::_update(ofEventArgs& evt)
{
    if (_updateInterval > 0)
    {
        uint64_t now = ofGetElapsedTimeMillis();

        if (now <= (_lastUpdate + _updateInterval))
        {
            return;
        }

        _lastUpdate = now;
    }

    _receive();
}


void BaseThreadsafeLoggerChannel::_exit(ofEventArgs& evt)
{
    // Flush any messages before exit.
    _receive();
}


void BaseThreadsafeLoggerChannel::_receive()
{
    std::vector<LoggerMessage> messages;

    LoggerMessage message;

    while (_messages.tryReceive(message))
    {
        messages.push_back(message);
    }

    // Sort any queued messages by timestamp.
    std::sort(messages.begin(),
              messages.end(),
              [](const LoggerMessage& lhs, const LoggerMessage& rhs)
              {
                  return lhs.timestamp() < rhs.timestamp();
              });
    
    for (const auto& message: messages) output(message);
}


void BaseThreadsafeLoggerChannel::output(const LoggerMessage& message)
{
    // print to cerr for OF_LOG_ERROR and OF_LOG_FATAL_ERROR, everything else to cout
    auto& out = message.level() < OF_LOG_ERROR ? std::cout : std::cerr;
    out << "[" << ofGetLogLevelName(message.level(), true)  << "] ";
    if (!message.module().empty()) out << message.module() << ": ";
    out << message.message() << endl;
}


ThreadsafeConsoleLoggerChannel::~ThreadsafeConsoleLoggerChannel()
{
}


void ThreadsafeConsoleLoggerChannel::output(const LoggerMessage& message)
{
    // print to cerr for OF_LOG_ERROR and OF_LOG_FATAL_ERROR, everything else to cout
    auto& out = message.level() < OF_LOG_ERROR ? std::cout : std::cerr;
    out << "[" << ofGetLogLevelName(message.level(), true)  << "] ";
    if (!message.module().empty()) out << message.module() << ": ";
    out << message.message() << endl;
}


ThreadsafeFileLoggerChannel::ThreadsafeFileLoggerChannel(const std::filesystem::path& path,
                                                         bool append)
{
    setFile(path,append);
}


ThreadsafeFileLoggerChannel::~ThreadsafeFileLoggerChannel()
{
    close();
}

void ThreadsafeFileLoggerChannel::close()
{
    file.close();
}

void ThreadsafeFileLoggerChannel::setFile(const std::filesystem::path & path,
                                          bool append)
{
    file.open(path, append ? ofFile::Append : ofFile::WriteOnly);
    file << std::endl;
    file << std::endl;
    file << "--------------------------------------- " << ofGetTimestampString() << std::endl;
}

void ThreadsafeFileLoggerChannel::output(const LoggerMessage& message)
{
    // print to cerr for OF_LOG_ERROR and OF_LOG_FATAL_ERROR, everything else to cout
    auto& out = file;
    out << "[" << ofGetLogLevelName(message.level(), true)  << "] ";
    if (!message.module().empty()) out << message.module() << ": ";
    out << message.message() << endl;
}


} } // namespace ofx::IO
