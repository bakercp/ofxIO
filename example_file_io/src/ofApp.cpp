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
