#pragma once

#include <deque>
#include "ofMain.h"
#include "DirectoryWatcher.h"
#include "BaseFileFilter.h"

using ofx::IO::BaseFileFilter;
using ofx::IO::DirectoryWatcher;
using ofx::IO::DirectoryWatcherEventArgs;
using ofx::IO::DirectoryWatcherMoveEventArgs;


class HiddenFileFilter : public BaseFileFilter {
public:
    HiddenFileFilter() { }
    virtual ~HiddenFileFilter() { }
    bool accept(const Poco::File& file) const {
        return !file.isHidden();
    }
};


class ofExampleApp : public ofBaseApp {
public:
    enum {
        TXT_HEIGHT = 14
    };

    void exit();
    void setup();
    void draw();

    void gotMessage(ofMessage msg);

    void onDirectoryWatcherItemAdded(const DirectoryWatcherEventArgs& evt) {
        ofSendMessage("Added:    " + evt.item.path());
    }
    
    void onDirectoryWatcherItemRemoved(const DirectoryWatcherEventArgs& evt) {
        ofSendMessage("Removed:  " + evt.item.path());
    }
    
    void onDirectoryWatcherItemModified(const DirectoryWatcherEventArgs& evt) {
        ofSendMessage("Modified: " + evt.item.path());
    }
    
    void onDirectoryWatcherItemMoved(const DirectoryWatcherMoveEventArgs& evt) {
        ofLogNotice("ofApp::onDirectoryWatcherItemMoved") << "Moved From: " << evt.item.path();
    }
        
    void onDirectoryWatcherError(const Exception& exc) {
        ofLogError("ofApp::onDirectoryWatcherError") << "Error: " << exc.displayText();
    }
    
    DirectoryWatcher watcher;

    HiddenFileFilter fileFilter; // an example file filter

    std::deque<string> messages;

};
