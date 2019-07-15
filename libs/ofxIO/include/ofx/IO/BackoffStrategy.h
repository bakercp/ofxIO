//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <cstddef>
#include <cstdint>


namespace ofx {
namespace IO {


/// \brief A class for generating backoff delays based on a particular strategy.
class BackoffStrategy
{
public:
    /// \brief An enumeration of backoff strategy types.
    enum class Method
    {
        /// \brief Retry with a fixed linear sequence of intervals.
        LINEAR,
        /// \brief Retry with an exponential sequence of intervals.
        EXPONENTIAL,
        /// \brief Retry with a Fibonacci sequence of intervals.
        FIBONACCI
    };

    /// \brief Create a default exponential BackoffStrategy.
    BackoffStrategy();

    /// \brief Create a BackoffStrategy with the given parameters.
    /// \param method The backoff method.
    /// \param initialDelay The initial delay in milliseconds.
    /// \param maximumDelay The maximum delay that can be returned.
    /// \param maximumRetries The maximum number or retries before failure.
    BackoffStrategy(Method method,
                    uint64_t initialDelay = DEFAULT_INITIAL_DELAY,
                    uint64_t maximumDelay = DEFAULT_MAXIMUM_RETIRES,
                    uint64_t maximumRetries = DEFAULT_MAXIMUM_DELAY);

    /// \brief Set the backoff method.
    ///
    /// Setting the backoff method will reset the backoff progress.
    ///
    /// \param method The method to set.
    void setBackoffMethod(Method method);

    /// \returns the backoff method.
    Method getBackoffMethod() const;

    /// \brief Set the initial delay.
    ///
    /// Setting the initial delay will reset the backoff progress.
    ///
    /// \param initialDelay The initial delay in milliseconds.
    void setInitialDelay(uint64_t initialDelay);

    /// \returns the initial delay in milliseconds.
    uint64_t getInitialDelay() const;

    /// \brief Set the maximum delay.
    ///
    /// This sets the maximum delay that can be returned by the next()
    /// function.
    ///
    /// Setting the maximum delay will reset the backoff progress.
    ///
    /// \param maximumDelay The maximum delay in milliseconds.
    void setMaximumDelay(uint64_t maximumDelay);

    /// \returns the maximum delay in milliseconds.
    uint64_t getMaximumDelay() const;

    /// \brief Set the maximum number of retries before failing.
    ///
    /// This causes the BackoffStrategy to fail after maximumRetries has been
    /// submitted.
    ///
    /// Setting maximumRetries to 0 is eqivalent to saying there is no limit.
    ///
    /// Setting the maximum retries will reset the backoff progress.
    ///
    /// \param maximumRetries The maximum retires to attempt before failure.
    void setMaximumRetries(uint64_t maximumRetries);

    /// \returns the maximum retries to attempt before failure.
    uint64_t getMaximumRetries() const;

    /// \brief Reset the current strategy, including counts, etc.
    void reset();

    /// \brief Immediately abort the current backoff attempt.
    ///
    /// Subsequent calls to failed() should return true.
    void abort();

    /// \returns true if there are no more delays.
    bool failed() const;

    /// \returns the number of retries remaining or
    ///          std::numeric_limits<std::size_t>::max() if infinite.
    std::size_t remaining() const;

    /// \brief Get the next delay in milliseconds.
    ///
    /// If the backoff strategy has failed (i.e. failed() returns true), a
    /// std::range_error will be thrown.
    ///
    /// \returns the next delay interval in milliseconds.
    /// \throws std::range_error if there are no delays remaining.
    uint64_t next();

    /// \brief An anonymous enumeration of default values.
    enum
    {
        /// \brief The default initial delay in milliseconds.
        DEFAULT_INITIAL_DELAY = 0,

        /// \brief The default maximum number of retries.
        DEFAULT_MAXIMUM_RETIRES = 10,

        /// \brief The default maximum delay in milliseconds.
        DEFAULT_MAXIMUM_DELAY = 120000
    };

private:
    /// \brief The backoff method.
    Method _method = Method::EXPONENTIAL;

    /// \brief The initial delay in milliseconds.
    uint64_t _initialDelay = DEFAULT_INITIAL_DELAY;

    /// \brief The current retry number.
    uint64_t _retryNumber = 0;

    /// \brief The next delay.
    uint64_t _lastDelay = 0;

    /// \brief The maximum delay time that can be generated.
    uint64_t _maximumDelay = DEFAULT_MAXIMUM_DELAY;

    /// \brief The maximum number of retries before failure.
    uint64_t _maximumRetries = DEFAULT_MAXIMUM_RETIRES;

};


} } // namespace ofx::IO
