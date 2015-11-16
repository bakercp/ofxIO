// =============================================================================
//
// Copyright (c) 2009-2015 Christopher Baker <http://christopherbaker.net>
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


#include "ofApp.h"


void ofApp::setup()
{
    ofSetWindowShape(ofGetScreenWidth(), 200);
    ofSetWindowPosition(0, 20);

    watcher.registerAllEvents(this);

    std::string folderToWatch = ofToDataPath("", true);
    bool listExistingItemsOnStart = true;

    watcher.addPath(folderToWatch, listExistingItemsOnStart, &fileFilter);

}


void ofApp::draw()
{
    ofBackground(0);
    ofFill();

    int y = TXT_HEIGHT;

    for (std::size_t i = 0; i < messages.size(); ++i)
    {
        ofSetColor(ofMap(i, 0, messages.size(), 255, 90));
        ofDrawBitmapString(messages[i], 10, y);
        y += TXT_HEIGHT;
    }
}


void ofApp::gotMessage(ofMessage msg)
{
    int height = ofGetHeight();
    
    std::size_t numLines = static_cast<std::size_t>(height / TXT_HEIGHT);

    messages.push_front(msg.message);

    while (messages.size() > numLines)
    {
        messages.pop_back();
    }
}
