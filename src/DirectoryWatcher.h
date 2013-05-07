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


namespace ofx {
namespace IO {


class DirectoryWatcherEventArgs;
class DirectoryWatcherMoveEventArgs;


class DirectoryWatcherEvents {
public:

    // Type will eventually be an alias for Poco::DirectoryWatcher
    enum Type {
        
        ITEM_ADDED = 1,
        /// A new item has been created and added to the directory.

        ITEM_REMOVED = 2,
        /// An item has been removed from the directory.

        ITEM_MODIFIED = 4,
        /// An item has been modified.

        ITEM_MOVED_FROM = 8,
        /// An item has been renamed or moved. This event delivers the old name.

        ITEM_MOVED_TO = 16,
        /// An item has been renamed or moved. This event delivers the new name.
    };

    DirectoryWatcherEvents() { }
    virtual ~DirectoryWatcherEvents() { }

    ofEvent<const DirectoryWatcherEventArgs>       onItemAdded;
    ofEvent<const DirectoryWatcherEventArgs>       onItemRemoved;
    ofEvent<const DirectoryWatcherEventArgs>       onItemModified;
    ofEvent<const DirectoryWatcherMoveEventArgs>   onItemMoved;
    ofEvent<const Poco::Exception>                 onError;
    
};


class DirectoryWatcherEventArgs {
public:
    DirectoryWatcherEventArgs(const Poco::Path& _path,
                              const Poco::File& _item,
                              DirectoryWatcherEvents::Type _event)
    : path(_path)
    , item(_item)
    , event(_event)
    {
    }

    const Poco::Path& path;
    const Poco::File& item;
    DirectoryWatcherEvents::Type event;
};


class DirectoryWatcherMoveEventArgs : public DirectoryWatcherEventArgs {
public:
    DirectoryWatcherMoveEventArgs(const Poco::Path& _path,
                                  const Poco::File& _item,
                                  DirectoryWatcherEvents::Type _event,
                                  const Poco::Path& _newPath,
                                  const Poco::File& _newItem)
    : DirectoryWatcherEventArgs(_path, _item, _event)
    , newPath(_newPath)
    , newItem(_newItem)
    {
    }

    const Poco::Path& newPath;
    const Poco::File& newItem;
};


class DirectoryWatcher : public FileWatcher, public FileWatchListener {
public:
    typedef Poco::FastMutex::ScopedLock ScopedLock;

    
    enum DirectoryEventMask {
		DW_FILTER_ENABLE_ALL = 31,
        /// Enables all event types.
        
		DW_FILTER_DISABLE_ALL = 0
        /// Disables all event types.
	};

    enum {
		DW_DEFAULT_SCAN_INTERVAL = 5 /// Default scan interval for platforms that don't provide a native notification mechanism.
	};

    DirectoryWatcher();
    
    void addPath(const Poco::Path& path,
                 bool bListExistingItemsOnStart = false,
                 BaseFileFilter* fileFilterPtr  = NULL,
                 int  eventMask                 = DW_FILTER_ENABLE_ALL,
                 int  scanInterval              = DW_DEFAULT_SCAN_INTERVAL);

    void removePath(const Poco::Path& path);

    virtual ~DirectoryWatcher();

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
                          FileWatcher::Action action) {
        
        DirectoryWatcherEvents::Type evt = (DirectoryWatcherEvents::Type)0;

        Poco::Path path(_path);
        Poco::File item(Poco::Path(_item).makeAbsolute());

        BaseFileFilter* fileFilterPtr = getFilterForPath(path);

        if(fileFilterPtr == NULL || fileFilterPtr->accept(item)) {
            // not all events are supported yet
            if(action == FileWatcher::Add) {
                evt = DirectoryWatcherEvents::ITEM_ADDED;
                DirectoryWatcherEventArgs args(path,item,evt);
                ofNotifyEvent(events.onItemAdded,args,this);
            } else if(action == FileWatcher::Delete) {
                evt = DirectoryWatcherEvents::ITEM_REMOVED;
                DirectoryWatcherEventArgs args(path,item,evt);
                ofNotifyEvent(events.onItemRemoved,args,this);
            } else if(action == FileWatcher::Modified) {
                evt = DirectoryWatcherEvents::ITEM_MODIFIED;
                DirectoryWatcherEventArgs args(path,item,evt);
                ofNotifyEvent(events.onItemModified,args,this);
            } else {
                Poco::IOException exc("Unknown FileWatcher::Action",action);
                ofNotifyEvent(events.onError,exc);
            }
        } else {
            // file was ignored based on the file filter
        }
    }

    BaseFileFilter* getFilterForPath(const Poco::Path& path) {
        ScopedLock lock(mutex);
        FilterListIter iter = filterList.find(path);
        if(iter != filterList.end()) {
            return (*iter).second;
        } else {
            return NULL;
        }
    }

private:
    typedef std::map<Poco::File,WatchID>         WatchList;
    typedef WatchList::iterator                  WatchListIter;
    typedef std::map<Poco::File,BaseFileFilter*> FilterList;
    typedef FilterList::iterator                 FilterListIter;

    WatchList  watchList;
    FilterList filterList;

    mutable Poco::FastMutex mutex;
};


} }

