// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include <map>
#include "Poco/DirectoryWatcher.h"
#include "Poco/Exception.h"
#include "Poco/Path.h"
#include "ofTypes.h"
#include "ofEvents.h"
#include "ofx/IO/DirectoryUtils.h"
#include "ofx/IO/AbstractTypes.h"


namespace ofx {
namespace IO {


class DirectoryWatcherEvents
    /// \brief A collection of directory watcher events.
    /// \sa DirectoryWatcherManager::registerAllEvents()
    /// \sa DirectoryWatcherManager::unregisterAllEvents()
    /// \sa ofAddListener()
    /// \sa ofRemoveListener()
{
public:
    typedef Poco::DirectoryWatcher::DirectoryEvent DirectoryEvent;

    DirectoryWatcherEvents()
    {
    }

    virtual ~DirectoryWatcherEvents()
    {
    }

    ofEvent<const DirectoryEvent> onItemAdded;
    ofEvent<const DirectoryEvent> onItemRemoved;
    ofEvent<const DirectoryEvent> onItemModified;
    ofEvent<const DirectoryEvent> onItemMovedFrom;
    ofEvent<const DirectoryEvent> onItemMovedTo;
    ofEvent<const Poco::Exception> onScanError;

};


class DirectoryWatcherManager
    /// \brief A thread-safe collection of directory watchers.
    /// \sa Poco::DirectoryWatcher
{
public:
    typedef Poco::DirectoryWatcher::DirectoryEvent DirectoryEvent;

    enum DirectoryEventType
	{
		ITEM_ADDED = Poco::DirectoryWatcher::DW_ITEM_ADDED,
            ///< A new item has been created and added to the directory.

		ITEM_REMOVED = Poco::DirectoryWatcher::DW_ITEM_REMOVED,
            ///< An item has been removed from the directory.

		ITEM_MODIFIED = Poco::DirectoryWatcher::DW_ITEM_MODIFIED,
            ///< An item has been modified.

		ITEM_MOVED_FROM = Poco::DirectoryWatcher::DW_ITEM_MOVED_FROM,
            ///< An item has been renamed or moved. This event delivers the old name.

		ITEM_MOVED_TO = Poco::DirectoryWatcher::DW_ITEM_MOVED_TO,
            ///< An item has been renamed or moved. This event delivers the new name.
	};


    enum DirectoryEventMask
	{
		FILTER_ENABLE_ALL = Poco::DirectoryWatcher::DW_FILTER_ENABLE_ALL,
            ///< Enables all event types.

		FILTER_DISABLE_ALL = Poco::DirectoryWatcher::DW_FILTER_DISABLE_ALL
            ///< Disables all event types.
	};

	enum
	{
		DEFAULT_SCAN_INTERVAL = Poco::DirectoryWatcher::DW_DEFAULT_SCAN_INTERVAL
            ///< Default scan interval for platforms that don't provide a native notification mechanism.
	};

    DirectoryWatcherManager();
        ///< \brief Create an empty DirectoryWatcherManager.
    
    virtual ~DirectoryWatcherManager();
        ///< \brief Destroy a DirectoryWatcherManager.

    void addPath(const Poco::Path& path,
                 bool listExistingItemsOnStart = false,
                 bool sortAlphaNumeric         = false,
                 AbstractPathFilter* pFilter   = 0,
                 int  eventMask                = FILTER_ENABLE_ALL,
                 int  scanInterval             = DEFAULT_SCAN_INTERVAL);
        ///< \brief Add a path to the watch list in order to receive related events.
        ///< \param listExistingItemsOnStart
        ///< \param sortAlphaNumeric
        ///< \param pFilter is the path filter for this path.  The
        ///< DirectoryWatcherManager does not take ownership of the pointer.
        ///< \param eventMask
        ///< \param scanInterval specifies the interval in seconds between scans.

    void removePath(const Poco::Path& path);
        ///< \brief Remove a path from the watch list.
        ///< \param path to be removed.
    
    bool isWatching(const Poco::Path& path) const;
        ///< \brief Query if a path is on the watch list.
        ///< \param path to be checked.
        ///< \returns true iff the path is on the watch list.

    DirectoryWatcherEvents events;
        ///< \brief An event object for Directory events.
        ///< \sa ofAddListener()
        ///< \sa ofRemoveListener()
        ///< \sa registerAllEvents()
        ///< \sa unregisterAllEvents()

    /// Register a class to receive notifications for all events.
    template<class ListenerClass>
    void registerAllEvents(ListenerClass* listener, int order = OF_EVENT_ORDER_AFTER_APP)
    {
        ofAddListener(events.onItemAdded, listener, &ListenerClass::onDirectoryWatcherItemAdded, order);
        ofAddListener(events.onItemRemoved, listener, &ListenerClass::onDirectoryWatcherItemRemoved, order);
        ofAddListener(events.onItemModified, listener, &ListenerClass::onDirectoryWatcherItemModified, order);
        ofAddListener(events.onItemMovedFrom, listener, &ListenerClass::onDirectoryWatcherItemMovedFrom, order);
        ofAddListener(events.onItemMovedTo, listener, &ListenerClass::onDirectoryWatcherItemMovedTo, order);
        ofAddListener(events.onScanError,listener, &ListenerClass::onDirectoryWatcherError, order);
    }

    /// Unregister a class to receive notifications for all events.
    template<class ListenerClass>
    void unregisterAllEvents(ListenerClass* listener)
    {
        ofRemoveListener(events.onItemAdded, listener, &ListenerClass::onDirectoryWatcherItemAdded);
        ofRemoveListener(events.onItemRemoved, listener, &ListenerClass::onDirectoryWatcherItemRemoved);
        ofRemoveListener(events.onItemModified, listener, &ListenerClass::onDirectoryWatcherItemModified);
        ofRemoveListener(events.onItemMovedFrom, listener, &ListenerClass::onDirectoryWatcherItemMovedFrom);
        ofRemoveListener(events.onItemMovedTo, listener, &ListenerClass::onDirectoryWatcherItemMovedTo);
        ofRemoveListener(events.onScanError, listener, &ListenerClass::onDirectoryWatcherError);
    }

protected:
    AbstractPathFilter* getFilterForPath(const Poco::Path& path);

    void onItemAdded(const Poco::DirectoryWatcher::DirectoryEvent& evt)
    {
        ofNotifyEvent(events.onItemAdded,evt,this);
    }

    void onItemRemoved(const Poco::DirectoryWatcher::DirectoryEvent& evt)
    {
        ofNotifyEvent(events.onItemRemoved,evt,this);
    }

    void onItemModified(const Poco::DirectoryWatcher::DirectoryEvent& evt)
    {
        ofNotifyEvent(events.onItemModified,evt,this);
    }

    void onItemMovedFrom(const Poco::DirectoryWatcher::DirectoryEvent& evt)
    {
        ofNotifyEvent(events.onItemMovedFrom,evt,this);
    }

    void onItemMovedTo(const Poco::DirectoryWatcher::DirectoryEvent& evt)
    {
        ofNotifyEvent(events.onItemMovedTo,evt,this);
    }

    void onScanError(const Poco::Exception& exc)
    {
        ofNotifyEvent(events.onScanError,exc,this);
    }

private:
    typedef std::shared_ptr<Poco::DirectoryWatcher> DirectoryWatcherPtr;
    typedef std::map<Poco::File,DirectoryWatcherPtr> WatchList;
    typedef WatchList::iterator                  WatchListIter;
    typedef std::map<Poco::File,AbstractPathFilter*> FilterList;
    typedef FilterList::iterator                 FilterListIter;

    WatchList  watchList;
    FilterList filterList;

    mutable Poco::FastMutex mutex;
    
};


} } // namespace ofx::IO
