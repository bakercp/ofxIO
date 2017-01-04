//
// Copyright (c) 2009 Christopher Baker <http://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    std::string path = ofToDataPath("openFrameworks.png", true);

    ofx::IO::ByteBuffer byteBuffer;

    try
    {
        std::streamsize in = ofx::IO::ByteBufferUtils::loadFromFile(path, byteBuffer);

        ofLogNotice("ofApp::setup") << in << " bytes read.";

        std::string newPath = ofToDataPath("openFrameworks_copy.png", true);

        bool result = ofx::IO::ByteBufferUtils::saveToFile(byteBuffer, newPath);

        if (result)
        {
            ofLogNotice("ofApp::setup") << "File written to " << newPath;
        }
        else
        {
            ofLogError("ofApp::setup") << "File not written bytes written.";
        }
    }
    catch (Poco::Exception& exception)
    {
        ofLogError("ofApp::setup") << "Exception: " << exception.displayText();
    }

    ofExit();

}
