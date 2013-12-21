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


#include "ofx/IO/DirectoryWatcherManager.h"


namespace ofx {
namespace IO {


DirectoryWatcherManager::DirectoryWatcherManager()
{
}


DirectoryWatcherManager::~DirectoryWatcherManager()
{
}


void DirectoryWatcherManager::addPath(const Poco::Path& path,
                                      bool listExistingItemsOnStart,
                                      bool sortAlphaNumeric,
                                      AbstractFileFilter* fileFilterPtr,
                                      int eventMask,
                                      int scanInterval)
{

    if(isWatching(path))
    {
        Poco::Exception exc("Already Watching Exception",path.toString());
        ofNotifyEvent(events.onScanError,exc,this);
        return;
    }

    try
    {
        Poco::File file(path);

        if(!file.exists())
        {
            Poco::FileNotFoundException exc(path.toString());
            throw exc;
        }

        DirectoryWatcherPtr watcher = DirectoryWatcherPtr(new Poco::DirectoryWatcher(path.toString()));

        watcher->itemAdded += Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemAdded, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemRemoved += Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemRemoved, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemModified += Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemModified, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemMovedFrom += Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemMovedFrom, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemMovedTo += Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemMovedTo, OF_EVENT_ORDER_AFTER_APP);
        watcher->scanError += Poco::priorityDelegate(this,&DirectoryWatcherManager::onScanError, OF_EVENT_ORDER_AFTER_APP);

        mutex.lock();

        if(0 != fileFilterPtr)
        {
            filterList[path] = fileFilterPtr;
        }

        watchList[path] = watcher;

        mutex.unlock();

        if(listExistingItemsOnStart)
        {
            std::vector<Poco::File> files;
            
            DirectoryUtils::list(file, files, sortAlphaNumeric, fileFilterPtr);

            std::vector<Poco::File>::iterator iter = files.begin();

            while(iter != files.end())
            {
                Poco::DirectoryWatcher::DirectoryEvent event(*iter,Poco::DirectoryWatcher::DW_ITEM_ADDED);
                ofNotifyEvent(events.onItemAdded,event,this);
                ++iter;
            }
        }
    }
    catch (const Poco::FileNotFoundException& exc)
    {
        ofNotifyEvent(events.onScanError,exc,this);
    }
}


void DirectoryWatcherManager::removePath(const Poco::Path& path)
{
    ofScopedLock lock(mutex);
    WatchListIter watchListIter = watchList.find(path);

    if(watchListIter != watchList.end())
    {
        DirectoryWatcherPtr watcher = (*watchListIter).second;

        watcher->itemAdded -= Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemAdded,OF_EVENT_ORDER_AFTER_APP);
        watcher->itemRemoved -= Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemRemoved,OF_EVENT_ORDER_AFTER_APP);
        watcher->itemModified -= Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemModified,OF_EVENT_ORDER_AFTER_APP);
        watcher->itemMovedFrom -= Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemMovedFrom,OF_EVENT_ORDER_AFTER_APP);
        watcher->itemMovedTo -= Poco::priorityDelegate(this,&DirectoryWatcherManager::onItemMovedTo,OF_EVENT_ORDER_AFTER_APP);
        watcher->scanError -= Poco::priorityDelegate(this,&DirectoryWatcherManager::onScanError,OF_EVENT_ORDER_AFTER_APP);

        watchList.erase(watchListIter);

        FilterListIter filterListIter = filterList.find(path);

        if(filterListIter != filterList.end())
        {

            filterList.erase(filterListIter);
        }
    }
}


bool DirectoryWatcherManager::isWatching(const Poco::Path& path) const
{
    ofScopedLock lock(mutex);
    return watchList.find(path) != watchList.end();
}


//void DirectoryWatcherManager::handleFileAction(WatchID watchid,
//                                               const string& _path,
//                                               const string& _item,
//                                               FileWatcher::Action action)
//{
//
//    DirectoryWatcherEvents::Type evt = (DirectoryWatcherEvents::Type)0;
//
//    Poco::Path path(_path);
//    Poco::File item(Poco::Path(_item).makeAbsolute());
//
//    BaseFileFilter* fileFilterPtr = getFilterForPath(path);
//
//    if(fileFilterPtr == NULL || fileFilterPtr->accept(item)) {
//        // not all events are supported yet
//        if(action == FileWatcher::Add) {
//            evt = DirectoryWatcherEvents::ITEM_ADDED;
//            DirectoryWatcherEventArgs args(path,item,evt);
//            ofNotifyEvent(events.onItemAdded,args,this);
//        } else if(action == FileWatcher::Delete) {
//            evt = DirectoryWatcherEvents::ITEM_REMOVED;
//            DirectoryWatcherEventArgs args(path,item,evt);
//            ofNotifyEvent(events.onItemRemoved,args,this);
//        } else if(action == FileWatcher::Modified) {
//            evt = DirectoryWatcherEvents::ITEM_MODIFIED;
//            DirectoryWatcherEventArgs args(path,item,evt);
//            ofNotifyEvent(events.onItemModified,args,this);
//        } else {
//            Poco::IOException exc("Unknown FileWatcher::Action",action);
//            ofNotifyEvent(events.onError,exc);
//        }
//    } else {
//        // file was ignored based on the file filter
//    }
//}

AbstractFileFilter* DirectoryWatcherManager::getFilterForPath(const Poco::Path& path)
{
    ofScopedLock lock(mutex);
    FilterListIter iter = filterList.find(path);
    if(iter != filterList.end()) {
        return (*iter).second;
    } else {
        return 0;
    }
}

    
} } // namespace ofx::IO
