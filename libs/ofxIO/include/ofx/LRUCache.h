//
// LRUCache.h
//
// $Id: //poco/1.4/Foundation/include/Poco/LRUCache.h#1 $
//
// Library: Foundation
// Package: Cache
// Module:  LRUCache
//
// Definition of the LRUCache class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

// Modified by @bakercp to use std::shared_ptr, rather than Poco::SharedPtr.


#pragma once


#include "ofx/AbstractCache.h"
#include "ofx/LRUStrategy.h"


namespace ofx {


template <
	class TKey, 
	class TValue,
	class TMutex = Poco::FastMutex,
	class TEventMutex = Poco::FastMutex
> 
    class LRUCache: public AbstractCache<TKey, TValue, LRUStrategy<TKey, TValue>, TMutex, TEventMutex>
	/// An LRUCache implements Least Recently Used caching. The default size for a cache is 1024 entries.
{
public:
    LRUCache(std::size_t cacheSize = 1024):
    AbstractCache<TKey, TValue, LRUStrategy<TKey, TValue>, TMutex, TEventMutex>(LRUStrategy<TKey, TValue>(cacheSize))
	{
	}

	~LRUCache()
	{
	}

private:
	LRUCache(const LRUCache& aCache);
	LRUCache& operator = (const LRUCache& aCache);
};


} // namespace ofx
