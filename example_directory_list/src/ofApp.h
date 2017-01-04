//
// Copyright (c) 2009 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include <deque>
#include "ofMain.h"
#include "ofxIO.h"


// a custom hidden path filter
class CustomPathFilter: public ofxIO::AbstractPathFilter
{
public:
    CustomPathFilter()
    {
    }

    virtual ~CustomPathFilter()
    {
    }

    bool accept(const Poco::Path& path) const
    {
        // don't return hidden files or files with names containing "FilterMeOut
        return !Poco::File(path).isHidden() &&
               !ofIsStringInString(path.toString(), "FilterMeOut");
    }
};


class ofApp: public ofBaseApp
{
public:
    enum
    {
        TXT_HEIGHT = 14
    };

    void setup();
    void draw();

    void gotMessage(ofMessage msg);

    CustomPathFilter pathFilter; // an example path filter
    std::deque<std::string> messages;

    ofxIO::ByteBuffer buffer;

};
