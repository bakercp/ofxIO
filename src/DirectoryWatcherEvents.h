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


#include "ofEvents.h"


namespace ofx {
namespace IO {


class DirectoryWatcherEventArgs;
class DirectoryWatcherMoveEventArgs;


class DirectoryWatcherEvents
{
public:

    // Type will eventually be an alias for Poco::DirectoryWatcher
    enum Type
    {
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

    DirectoryWatcherEvents()
    {
    }

    virtual ~DirectoryWatcherEvents()
    {
    }

    ofEvent<const DirectoryWatcherEventArgs>       onItemAdded;
    ofEvent<const DirectoryWatcherEventArgs>       onItemRemoved;
    ofEvent<const DirectoryWatcherEventArgs>       onItemModified;
    ofEvent<const DirectoryWatcherMoveEventArgs>   onItemMoved;
    ofEvent<const Poco::Exception>                 onError;

};


class DirectoryWatcherEventArgs
{
public:
    DirectoryWatcherEventArgs(const Poco::Path& _path,
                              const Poco::File& _item,
                              DirectoryWatcherEvents::Type _event):
        path(_path),
        item(_item),
        event(_event)
    {
    }

    const Poco::Path& path;
    const Poco::File& item;
    DirectoryWatcherEvents::Type event;
};


class DirectoryWatcherMoveEventArgs: public DirectoryWatcherEventArgs
{
public:
    DirectoryWatcherMoveEventArgs(const Poco::Path& _path,
                                  const Poco::File& _item,
                                  DirectoryWatcherEvents::Type _event,
                                  const Poco::Path& _newPath,
                                  const Poco::File& _newItem):
        DirectoryWatcherEventArgs(_path, _item, _event),
        newPath(_newPath),
        newItem(_newItem)
    {
    }

    const Poco::Path& newPath;
    const Poco::File& newItem;
};


}} // ofx::IO
