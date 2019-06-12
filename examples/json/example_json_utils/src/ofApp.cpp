//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofJson json0;
    ofJson json1;

    std::vector<int> numbers = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    json0["numbers"] = numbers;

    if (ofxIO::JSONUtils::saveJSON("numbers.json", json0) &&
        ofxIO::JSONUtils::loadJSON("numbers.json", json1))
    {
        std::vector<int> _numbers = json1["numbers"];

        for (std::size_t i = 0; i < numbers.size(); ++i)
        {
            if (_numbers[i] != numbers[i])
            {
                ofLogError("ofApp::setup") << "Failure.";
                ofExit();
            }
            else
            {
                ofLogNotice("ofApp::setup") << _numbers[i] << " == " << numbers[i];
            }
        }
    }
    else
    {
        ofLogError("ofApp::setup") << "Failure.";
        ofExit();
    }

    if (ofxIO::JSONUtils::saveJSON("numbers.json.gz", json0) &&
        ofxIO::JSONUtils::loadJSON("numbers.json.gz", json1))
    {
        std::vector<int> _numbers = json1["numbers"];

        for (std::size_t i = 0; i < numbers.size(); ++i)
        {
            if (_numbers[i] != numbers[i])
            {
                ofLogError("ofApp::setup") << "Failure.";
                ofExit();
            }
            else
            {
                ofLogNotice("ofApp::setup") << _numbers[i] << " == " << numbers[i];
            }
        }
    }
    else
    {
        ofLogError("ofApp::setup") << "Failure.";
        ofExit();
    }
}
