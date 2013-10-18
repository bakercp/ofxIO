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
#include "Poco/Exception.h"
#include "Poco/Path.h"
#include "BaseFileFilter.h"
#include "FileWatcher.h"
#include "ofEvents.h"
#include "DirectoryWatcherEvents.h"


namespace ofx {
namespace IO {

    
class DirectoryWatcher: public FileWatcher, public FileWatchListener
{
public:
    typedef Poco::FastMutex::ScopedLock ScopedLock;

    enum DirectoryEventMask
    {
		DW_FILTER_ENABLE_ALL = 31,
        /// Enables all event types.
        
		DW_FILTER_DISABLE_ALL = 0
        /// Disables all event types.
	};

    enum
    {
		DW_DEFAULT_SCAN_INTERVAL = 5 /// Default scan interval for platforms that don't provide a native notification mechanism.
	};

    DirectoryWatcher();
    
    virtual ~DirectoryWatcher();

    void addPath(const Poco::Path& path,
                 bool bListExistingItemsOnStart = false,
                 bool bSortAlphaNumeric         = false,
                 BaseFileFilter* fileFilterPtr  = NULL,
                 int  eventMask                 = DW_FILTER_ENABLE_ALL,
                 int  scanInterval              = DW_DEFAULT_SCAN_INTERVAL);

    void removePath(const Poco::Path& path);
    
    bool isWatching(const Poco::Path& path) const;

    DirectoryWatcherEvents events;

    template<class ListenerClass>
    void RegisterEvents(ListenerClass* listener){
        ofAddListener(events.onItemAdded,    listener, &ListenerClass::onDirectoryWatcherItemAdded);
        ofAddListener(events.onItemRemoved,  listener, &ListenerClass::onDirectoryWatcherItemRemoved);
        ofAddListener(events.onItemModified, listener, &ListenerClass::onDirectoryWatcherItemModified);
        ofAddListener(events.onItemMoved,    listener, &ListenerClass::onDirectoryWatcherItemMoved);
        ofAddListener(events.onError,        listener, &ListenerClass::onDirectoryWatcherError);
    }

    template<class ListenerClass>
    void UnregisterEvents(ListenerClass* listener){
        ofRemoveListener(events.onItemAdded,    listener, &ListenerClass::onDirectoryWatcherItemAdded);
        ofRemoveListener(events.onItemRemoved,  listener, &ListenerClass::onDirectoryWatcherItemRemoved);
        ofRemoveListener(events.onItemModified, listener, &ListenerClass::onDirectoryWatcherItemModified);
        ofRemoveListener(events.onItemMoved,    listener, &ListenerClass::onDirectoryWatcherItemMoved);
        ofRemoveListener(events.onError,        listener, &ListenerClass::onDirectoryWatcherError);
    }



protected:
    void handleFileAction(WatchID watchid,
                          const string& _path,
                          const string& _item,
                          FileWatcher::Action action);

    BaseFileFilter* getFilterForPath(const Poco::Path& path);

private:
    typedef std::map<Poco::File,WatchID>         WatchList;
    typedef WatchList::iterator                  WatchListIter;
    typedef std::map<Poco::File,BaseFileFilter*> FilterList;
    typedef FilterList::iterator                 FilterListIter;

    WatchList  watchList;
    FilterList filterList;

    mutable Poco::FastMutex mutex;
    
};


} } // namespace ofx::IO
