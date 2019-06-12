//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofMain.h"
#include "ofxIO.h"


class ImageProcessingClass: public ofxIO::Thread
{
public:
    ImageProcessingClass():
        ofxIO::Thread(std::bind(&ImageProcessingClass::functionToBeRunInAThread, this))
    {
    }

    virtual ~ImageProcessingClass()
    {
    }

    void functionToBeRunInAThread()
    {
        ofPixels pixelsToReceive;
        ofPixels pixelsToSend;

        ofxIO::Base64Encoding base64Encoder;
        
        // Check to make sure the thread is running.
        // Try to receive the pixels sent() to this channel. They could be sent
        // from anywhere, but in this case they are sent from the main thread.
        // thread (returns true if the channel is still open).
        while (isRunning() && input.receive(pixelsToReceive))
        {
            // If our process is slow, we can start dropping frames. In this case,
            // we start dropping frames if our queue gets larger than 30.
            if (input.size() > 30)
                continue;

            
            ////////////////////////////////////////////////////////////////////
            /// BEGIN Arbitrarily difficult image processing ///////////////////
            ////////////////////////////////////////////////////////////////////
            
            ofBuffer compressedPixels;

            // Save the pixels to a buffer using PNG compression.
            ofSaveImage(pixelsToReceive, compressedPixels, OF_IMAGE_FORMAT_PNG);

            // Encode the compressed pixels in base64.
            ofxIO::ByteBuffer base64CompressedPixelsIn;
            base64Encoder.encode(ofxIO::ByteBuffer(compressedPixels.getData(), compressedPixels.size()),
                                 base64CompressedPixelsIn);


            // Send them somewhere for processing. This is boring, but we just
            // copy them. They could be sent to a server using and ofxHTTP
            // client processed by a command line program, etc.
            ofxIO::ByteBuffer base64CompressedPixelsProcessed = base64CompressedPixelsIn;
            
            // We also introduce a delay to simulate a long running process.
            uint64_t delay = ofRandom(1000);
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait_for(lock, std::chrono::milliseconds(delay));
            
            // Turn the processed / compressed image back into ofPixels.

            // Decode base64.
            ofxIO::ByteBuffer base64CompressedPixelsOut;
            base64Encoder.decode(base64CompressedPixelsProcessed,
                                 base64CompressedPixelsOut);


            // Decompress PNG.
            ofLoadImage(pixelsToSend, ofBuffer(base64CompressedPixelsOut.getCharPtr(),
                                               base64CompressedPixelsOut.size()));

            ////////////////////////////////////////////////////////////////////
            /// END Arbitrarily difficult image processing /////////////////////
            ////////////////////////////////////////////////////////////////////

            // Send the pixels back to the output channel.
            // Then any thread can safely receive() these pixels, but in this
            // example we receive() them from the main thread because we want to
            // display upload and display them with OpenGL. Additionally, with
            // care, we could use std::move() operator here for additional
            // speed, but that is outside of the scope of this example.
            // (see C++ std::move() semantics).
            output.send(pixelsToSend);
        }
    }
    
    // This thread channel recevies our uncompressed input pixels.
    // The main thread sends pixels to this input.
    // The auxillary thread (this class) receives these pixels and processes them.
    ofxIO::ThreadChannel<ofPixels> input;
    
    // This thread channel receives our uncompressed, processed output pixels.
    // The auxillary thread (this class) sends processed pixels to this channel.
    // The main thread receives pixels from this channel and then uploads them
    // textures, displays them, etc.
    ofxIO::ThreadChannel<ofPixels> output;
    
    // We are using ofxIO::ThreadChannel rather than ofThreadChannel because
    // the size() method is not available in ofThreadChannel and this allows
    // us to make decisions based on the size of the ThreadChannel (e.g. skip
    // or drop frames). Besides the addition of the size() and empty() methods,
    // there is no difference between the ofxIO::ThreadChannel and the
    // ofThreadChannel.
    
    // It is important to note that ofxIO::ThreadChannel and ofThreadChannel can
    // be used anywhere. They can be class members, they can be passed by
    // reference, pointer, etc. Their key function is simply to move data
    // between threads without worrying about thread safety (e.g. deadlock,
    // race conditions, mutexes, etc.).
    //
    // In many cases, it might make sense for the main thread to send images to
    // a single Thread Channel and have _multiple_ service threads receiving
    // those images for processing. Then all threads could send() their
    // processed results back to the main thread for display via a common
    // thread channel. In this case, there would be no guarantee of order in the
    // queue, but that could be overcome by creating a class that included pixel
    // data and timing information and creating a ThreadChannel for that class.
};


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    ImageProcessingClass imageProcessor;

    ofVideoGrabber grabber;

    ofTexture texture;
   
    
};
