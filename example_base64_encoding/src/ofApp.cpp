// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
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
    try
    {
        // Create an empty ofxIO::ByteBuffer.
        ofxIO::ByteBuffer buffer;

        // Load the file contents into the buffer.
        ofxIO::ByteBufferUtils::loadFromFile("openFrameworks.gif", buffer);

        // Base64 encode the images's bytes.
        //
        // Additional encoding option include URL-safety, chunking and padding.
        std::string base64Buffer = ofxIO::Base64Encoding::encode(buffer);

        // Print the base64 encoded bytes to the console.
        std::cout << base64Buffer << std::endl;

        // Decode the bytes.
        //
        // Can also decode URL-safe base64 encoding.
        std::string decodedBytes = ofxIO::Base64Encoding::decode(base64Buffer);

        // Write the decoded bytes out to a new file.
        ofxIO::ByteBuffer decodedBuffer(decodedBytes);

        // Save the file back to disk.
        ofxIO::ByteBufferUtils::saveToFile(decodedBuffer, "openFrameworks_copy.gif");
    }
    catch (const std::exception& exc)
    {
        ofLogError("ofApp::setup") << "I/O Exception: " << exc.what();
    }

}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("See console for output.", ofPoint(30, 30));
}
