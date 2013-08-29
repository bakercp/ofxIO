// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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


#include <deque>
#include "ofMain.h"
#include "DirectoryWatcher.h"
#include "BaseFileFilter.h"


using ofx::IO::BaseFileFilter;
using ofx::IO::DirectoryWatcher;
using ofx::IO::DirectoryWatcherEventArgs;
using ofx::IO::DirectoryWatcherMoveEventArgs;


// a custom hidden file filter
class HiddenFileFilter: public BaseFileFilter
{
public:
    HiddenFileFilter()
    {
    }

    virtual ~HiddenFileFilter()
    {
    }

    bool accept(const Poco::File& file) const
    {
        return !file.isHidden();
    }
};


class ofApp: public ofBaseApp
{
public:
    enum
    {
        TXT_HEIGHT = 14
    };

    void exit();
    void setup();
    void draw();

    void gotMessage(ofMessage msg);

    void onDirectoryWatcherItemAdded(const DirectoryWatcherEventArgs& evt)
    {
        ofSendMessage("Added:    " + evt.item.path());
    }
    
    void onDirectoryWatcherItemRemoved(const DirectoryWatcherEventArgs& evt)
    {
        ofSendMessage("Removed:  " + evt.item.path());
    }
    
    void onDirectoryWatcherItemModified(const DirectoryWatcherEventArgs& evt)
    {
        ofSendMessage("Modified: " + evt.item.path());
    }
    
    void onDirectoryWatcherItemMoved(const DirectoryWatcherMoveEventArgs& evt)
    {
        ofLogNotice("ofApp::onDirectoryWatcherItemMoved") << "Moved From: " << evt.item.path();
    }
        
    void onDirectoryWatcherError(const Exception& exc)
    {
        ofLogError("ofApp::onDirectoryWatcherError") << "Error: " << exc.displayText();
    }

    
    DirectoryWatcher watcher;
    HiddenFileFilter fileFilter; // an example file filter
    std::deque<string> messages;

};
