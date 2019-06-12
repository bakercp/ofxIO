//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    // This allows multiple threads to write to the ofLog system without
    // experiencing broken messages.
    ofLog::setChannel(std::make_shared<ofxIO::ThreadsafeConsoleLoggerChannel>());

    // Create a source of images.
    grabber.setup(640, 480);
    
    // Start the image processor thread.
    imageProcessor.start();
    
    // We want to accumulate images.
    ofSetBackgroundAuto(false);
}


void ofApp::update()
{
    grabber.update();
    
    if (grabber.isFrameNew())
    {
        // Send the unprocessed pixels to the processing thread.
        imageProcessor.input.send(grabber.getPixels());
    }
    
    // Process any image(s) that have been returned by the processing thread(s).
    // This update() function is being called from the main thread, so it can
    // handle uploading pixel data to a texture.
    //
    // Here we use "tryReceive" so the while loop won't block.
    ofPixels processedPixels;
    while (imageProcessor.output.tryReceive(processedPixels))
    {
        // Depending on how fast the thread is (i.e. if it is faster than the
        // main openFrameworks thread that calls update(), this while loop may
        // end up uploading multiple images to the texture. If this is the case,
        // you may want to collect those processed images in a
        // std::vector<ofTexture> for later display.
        texture.loadData(processedPixels);
    }
}


void ofApp::draw()
{
    if (texture.isAllocated())
    {
        texture.draw(0, 0);
    }

    ofDrawBitmapStringHighlight("Images waiting to be processed: " + ofToString(imageProcessor.input.size()), 16, 16);

}
