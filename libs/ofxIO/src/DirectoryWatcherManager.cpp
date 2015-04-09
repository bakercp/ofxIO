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
                                      AbstractPathFilter* pFilter,
                                      int eventMask,
                                      int scanInterval)
{

    if (isWatching(path))
    {
        Poco::Exception exc("Already Watching Exception", path.toString());
        ofNotifyEvent(events.onScanError, exc, this);
        return;
    }

    try
    {
        Poco::File file(path);

        if (!file.exists())
        {
            Poco::FileNotFoundException exc(path.toString());
            throw exc;
        }

        DirectoryWatcherPtr watcher = DirectoryWatcherPtr(new DirectoryWatcher(path.toString(),
                                                                               eventMask,
                                                                               scanInterval));

        watcher->itemAdded += Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemAdded, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemRemoved += Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemRemoved, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemModified += Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemModified, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemMovedFrom += Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemMovedFrom, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemMovedTo += Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemMovedTo, OF_EVENT_ORDER_AFTER_APP);
        watcher->scanError += Poco::priorityDelegate(this, &DirectoryWatcherManager::onScanError, OF_EVENT_ORDER_AFTER_APP);

        mutex.lock();

        if(pFilter)
        {
            filterList[path] = pFilter;
        }

        watchList[path] = watcher;

        mutex.unlock();

        if (listExistingItemsOnStart)
        {
            std::vector<Poco::File> files;
            
            DirectoryUtils::list(file, files, sortAlphaNumeric, pFilter);

            std::vector<Poco::File>::iterator iter = files.begin();

            while(iter != files.end())
            {
                DirectoryWatcher::DirectoryEvent event(*iter, DirectoryWatcher::DW_ITEM_ADDED);
                ofNotifyEvent(events.onItemAdded,event,this);
                ++iter;
            }
        }
    }
    catch (const Poco::FileNotFoundException& exc)
    {
        ofNotifyEvent(events.onScanError, exc, this);
    }
}


void DirectoryWatcherManager::removePath(const Poco::Path& path)
{
    ofScopedLock lock(mutex);
    WatchListIter watchListIter = watchList.find(path);

    if (watchListIter != watchList.end())
    {
        DirectoryWatcherPtr watcher = (*watchListIter).second;

        watcher->itemAdded -= Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemAdded, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemRemoved -= Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemRemoved, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemModified -= Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemModified, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemMovedFrom -= Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemMovedFrom, OF_EVENT_ORDER_AFTER_APP);
        watcher->itemMovedTo -= Poco::priorityDelegate(this, &DirectoryWatcherManager::onItemMovedTo, OF_EVENT_ORDER_AFTER_APP);
        watcher->scanError -= Poco::priorityDelegate(this, &DirectoryWatcherManager::onScanError, OF_EVENT_ORDER_AFTER_APP);

        watchList.erase(watchListIter);

        FilterListIter filterListIter = filterList.find(path);

        if (filterListIter != filterList.end())
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


AbstractPathFilter* DirectoryWatcherManager::getFilterForPath(const Poco::Path& path)
{
    ofScopedLock lock(mutex);
    FilterListIter iter = filterList.find(path);

    if (iter != filterList.end())
    {
        return (*iter).second;
    }
    else
    {
        return 0;
    }
}

    
} } // namespace ofx::IO
