// =============================================================================
//
// Copyright (c) 2010-2016 Christopher Baker <http://christopherbaker.net>
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
#include "json.hpp"
#include "Poco/FileStream.h"
#include "ofx/DirectoryWatcher.h"
#include "ofx/RecursiveDirectoryIterator.h"
#include "ofx/IO/AbstractTypes.h"
#include "ofx/IO/Base64Encoding.h"
#include "ofx/IO/ByteBuffer.h"
#include "ofx/IO/ByteBufferReader.h"
#include "ofx/IO/ByteBufferStream.h"
#include "ofx/IO/ByteBufferUtils.h"
#include "ofx/IO/ByteBufferWriter.h"
#include "ofx/IO/COBSEncoding.h"
#include "ofx/IO/SLIPEncoding.h"
#include "ofx/IO/Compression.h"
#include "ofx/IO/DeviceFilter.h"
#include "ofx/IO/DirectoryUtils.h"
#include "ofx/IO/DirectoryFilter.h"
#include "ofx/IO/DirectoryWatcherManager.h"
#include "ofx/IO/FileExtensionFilter.h"
#include "ofx/IO/HexBinaryEncoding.h"
#include "ofx/IO/HiddenFileFilter.h"
#include "ofx/IO/LinkFilter.h"
#include "ofx/IO/PathFilterCollection.h"
#include "ofx/IO/RegexPathFilter.h"
#include "ofx/IO/SearchPath.h"
#include "ofx/IO/URIEncoding.h"


namespace ofxIO = ofx::IO;
