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


#include "DirectoryWatcher.h"
#include "DirectoryUtils.h"

namespace ofx {
namespace IO {


//------------------------------------------------------------------------------
DirectoryWatcher::DirectoryWatcher()
{
}


//------------------------------------------------------------------------------
DirectoryWatcher::~DirectoryWatcher()
{
}

//------------------------------------------------------------------------------
bool DirectoryWatcher::isWatching(const Poco::Path& path) const {
    ScopedLock lock(mutex);
    return watchList.find(path) != watchList.end();
}


//------------------------------------------------------------------------------
void DirectoryWatcher::addPath(const Poco::Path& path,
                               bool bListExistingItemsOnStart,
                               BaseFileFilter* fileFilterPtr,
                               int eventMask,
                               int scanInterval)
{

    if(isWatching(path)) {
        Exception exc("Already Watching Exception",path.toString());
        ofNotifyEvent(events.onError,exc,this);
        return;
    }

    try {
        Poco::File file(path);

        if(!file.exists()) {
            Poco::FileNotFoundException exc(path.toString());
            throw exc;
        }

        cout <<"ADDING PATH: " << path.toString() << endl;

        
        WatchID id = addWatch(path.toString(),this);

        mutex.lock();
        if(fileFilterPtr != NULL) filterList[path] = fileFilterPtr;
        watchList[path] = id;
        mutex.unlock();

        if(bListExistingItemsOnStart) {
            std::vector<Poco::File> files;
            DirectoryUtils::list(file, files, fileFilterPtr);

            std::vector<Poco::File>::iterator iter = files.begin();

            while(iter != files.end())
            {
                DirectoryWatcherEventArgs event(path,*iter,DirectoryWatcherEvents::ITEM_ADDED);
                ofNotifyEvent(events.onItemAdded,event,this);
                ++iter;
            }

        }

    } catch(const Poco::FileNotFoundException& exc) {
        ofNotifyEvent(events.onError,exc,this);
    }
}

//------------------------------------------------------------------------------
void DirectoryWatcher::removePath(const Poco::Path& path)
{
    ScopedLock lock(mutex);
    WatchListIter watchListIter = watchList.find(path);

    if(watchListIter != watchList.end()) {
        watchList.erase(watchListIter);
        FilterListIter filterListIter = filterList.find(path);
        if(filterListIter != filterList.end()) {
            filterList.erase(filterListIter);
        }
    }


}


} }
