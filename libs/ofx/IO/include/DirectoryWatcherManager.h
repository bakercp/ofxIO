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
#include "DirectoryUtils.h"
#include "BaseFileFilter.h"


namespace ofx {
namespace IO {


class DirectoryWatcherEvents
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
{
public:
    DirectoryWatcherManager();
    
    virtual ~DirectoryWatcherManager();

    void addPath(const Poco::Path& path,
                 bool listExistingItemsOnStart = false,
                 bool sortAlphaNumeric         = false,
                 BaseFileFilter* fileFilterPtr = NULL,
                 int  eventMask                = Poco::DirectoryWatcher::DW_FILTER_ENABLE_ALL,
                 int  scanInterval             = Poco::DirectoryWatcher::DW_DEFAULT_SCAN_INTERVAL);

    void removePath(const Poco::Path& path);
    
    bool isWatching(const Poco::Path& path) const;

    DirectoryWatcherEvents events;

    template<class ListenerClass>
    void registerAllEvents(ListenerClass* listener)
    {
        ofAddListener(events.onItemAdded,    listener, &ListenerClass::onDirectoryWatcherItemAdded);
        ofAddListener(events.onItemRemoved,  listener, &ListenerClass::onDirectoryWatcherItemRemoved);
        ofAddListener(events.onItemModified, listener, &ListenerClass::onDirectoryWatcherItemModified);
        ofAddListener(events.onItemMovedFrom,listener, &ListenerClass::onDirectoryWatcherItemMovedFrom);
        ofAddListener(events.onItemMovedTo,  listener, &ListenerClass::onDirectoryWatcherItemMovedTo);
        ofAddListener(events.onScanError,    listener, &ListenerClass::onDirectoryWatcherError);
    }

    template<class ListenerClass>
    void unregisterAllEvents(ListenerClass* listener)
    {
        ofRemoveListener(events.onItemAdded,    listener, &ListenerClass::onDirectoryWatcherItemAdded);
        ofRemoveListener(events.onItemRemoved,  listener, &ListenerClass::onDirectoryWatcherItemRemoved);
        ofRemoveListener(events.onItemModified, listener, &ListenerClass::onDirectoryWatcherItemModified);
        ofRemoveListener(events.onItemMovedFrom,listener, &ListenerClass::onDirectoryWatcherItemMovedFrom);
        ofRemoveListener(events.onItemMovedTo,  listener, &ListenerClass::onDirectoryWatcherItemMovedTo);
        ofRemoveListener(events.onScanError,    listener, &ListenerClass::onDirectoryWatcherError);
    }

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


protected:
    BaseFileFilter* getFilterForPath(const Poco::Path& path);

private:
    typedef std::shared_ptr<Poco::DirectoryWatcher> DirectoryWatcherPtr;
    typedef std::map<Poco::File,DirectoryWatcherPtr> WatchList;
    typedef WatchList::iterator                  WatchListIter;
    typedef std::map<Poco::File,BaseFileFilter*> FilterList;
    typedef FilterList::iterator                 FilterListIter;

    WatchList  watchList;
    FilterList filterList;

    mutable Poco::FastMutex mutex;
    
};


} } // namespace ofx::IO
