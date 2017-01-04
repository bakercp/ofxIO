//
// Copyright (c) 2010 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/DirectoryWatcherManager.h"
#include "Poco/PriorityDelegate.h"


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

        _mutex.lock();

        if (pFilter)
        {
            filterList[path] = pFilter;
        }

        watchList[path] = watcher;

        _mutex.unlock();

        if (listExistingItemsOnStart)
        {
            std::vector<Poco::File> files;
            
            DirectoryUtils::list(file, files, sortAlphaNumeric, pFilter);

            std::vector<Poco::File>::iterator iter = files.begin();

            while (iter != files.end())
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
    std::unique_lock<std::mutex> lock(_mutex);
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
    std::unique_lock<std::mutex> lock(_mutex);
    return watchList.find(path) != watchList.end();
}


AbstractPathFilter* DirectoryWatcherManager::getFilterForPath(const Poco::Path& path)
{
    std::unique_lock<std::mutex> lock(_mutex);
    FilterListIter iter = filterList.find(path);

    if (iter != filterList.end())
    {
        return (*iter).second;
    }
    else
    {
        return nullptr;
    }
}

    
} } // namespace ofx::IO
