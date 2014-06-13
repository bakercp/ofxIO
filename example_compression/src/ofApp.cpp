// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
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


const std::string ofApp::LOREM_IPSUM = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent quis laoreet magna. Proin rutrum congue vulputate. Nulla aliquet, leo nec viverra dapibus, sapien tellus porttitor justo, sit amet luctus mi mauris non metus. Phasellus placerat convallis quam a malesuada. Sed rutrum quam in dictum auctor. Fusce orci lectus, porttitor vitae consectetur sit amet, mollis vitae mi. Nulla ante diam, aliquam id ante ut, hendrerit commodo dolor. Nunc lacinia sodales sollicitudin. Integer sollicitudin neque ac diam commodo venenatis.\
\
Donec eleifend arcu a purus gravida feugiat. Duis consequat eget odio congue laoreet. Praesent eget semper nibh. Suspendisse molestie diam ligula, quis convallis eros auctor non. Ut molestie felis eget pharetra varius. Fusce cursus dolor ac felis accumsan, mattis ultricies nisi rutrum. Curabitur interdum, est sed elementum vehicula, turpis lorem imperdiet ipsum, sit amet pharetra enim enim at nisi. Nunc feugiat fermentum erat, eu eleifend turpis aliquet ac. Nunc ornare metus ut leo tempor euismod. Aliquam erat volutpat. Etiam erat dui, elementum rutrum consequat ac, mollis in ante. Suspendisse eleifend tincidunt mauris, ut mattis diam adipiscing non. Curabitur vulputate at risus id bibendum.\
\
Donec tincidunt, felis at ornare dapibus, leo eros congue lectus, ac feugiat augue sapien sed dui. Nulla quis ligula sem. Morbi rutrum tortor dignissim scelerisque vulputate. Vestibulum convallis fermentum eros nec blandit. Sed consectetur mollis imperdiet. Nulla sed accumsan elit, sed suscipit quam. Phasellus tincidunt enim turpis. In iaculis risus a fermentum porta. Aliquam at orci non arcu aliquam porttitor eu ut neque. Vivamus ultrices elit porttitor adipiscing venenatis. Aliquam feugiat, mi non pretium ullamcorper, velit erat cursus felis, a varius ante diam nec orci. Sed sed faucibus ipsum, vel fringilla massa. Vestibulum suscipit, felis eget porta sagittis, augue augue porttitor arcu, et venenatis lacus metus sit amet leo. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed elementum purus nunc, varius laoreet elit posuere vel. Morbi sed ligula rhoncus, commodo nunc a, feugiat ipsum.\
\
Suspendisse egestas arcu sit amet ligula rhoncus, eget malesuada dolor ultrices. Vivamus vestibulum mauris ut purus commodo luctus. Nullam nec urna varius, consequat purus a, posuere nisl. Quisque eleifend a arcu eget imperdiet. Nulla sed est quis nisi imperdiet imperdiet. In hac habitasse platea dictumst. Phasellus euismod, justo non laoreet fermentum, ante est ornare diam, eu fermentum leo enim ut urna. Aliquam erat volutpat. Proin est leo, fringilla id nunc interdum, auctor dictum purus. Maecenas nisl eros, rhoncus id pulvinar id, auctor sit amet felis. In hac habitasse platea dictumst. Fusce a consequat sem.\
\
Sed sapien justo, fermentum quis vulputate ut, aliquet nec leo. Maecenas sollicitudin quis purus a auctor. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Interdum et malesuada fames ac ante ipsum primis in faucibus. Donec eget volutpat lacus, nec dignissim neque. Nulla porta nunc viverra tortor rhoncus accumsan. Curabitur lacus odio, laoreet in eleifend ac, convallis et quam. In varius interdum auctor. Fusce porttitor molestie lacus, non vestibulum erat scelerisque et.\
\
Sed porttitor nunc nec dolor ullamcorper bibendum sit amet vulputate erat. Proin faucibus nisi sit amet adipiscing eleifend. Interdum et malesuada fames ac ante ipsum primis in faucibus. Donec adipiscing porta hendrerit. Donec hendrerit ac tellus eu venenatis. Vivamus non egestas orci. Donec erat elit, tempus sed iaculis placerat, tincidunt sed velit. In pulvinar, enim nec vehicula pellentesque, nunc est facilisis purus, ut vehicula lacus velit in ipsum. Pellentesque dictum quis dolor laoreet suscipit. Nam id dapibus lacus, in laoreet lacus. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Cras pretium magna a neque placerat, eleifend pharetra risus volutpat. Sed odio purus, faucibus ultricies eros a, interdum lacinia massa. Etiam augue arcu, rutrum et accumsan vitae, volutpat ac purus. Lorem ipsum dolor sit amet, consectetur adipiscing elit.\
\
Morbi sed ipsum eu leo vestibulum cursus a et dolor. Vivamus tincidunt sapien nec ipsum lobortis tristique. Donec blandit suscipit iaculis. Nam a porttitor justo. Pellentesque vel lectus vel tellus dictum hendrerit nec porttitor est. Vivamus at faucibus metus. Praesent elementum volutpat tempus. Phasellus vitae pretium sapien, a fringilla nulla. Vivamus vehicula orci ut nibh malesuada, vel pellentesque nibh vehicula. Vivamus turpis massa, facilisis non tortor non, fermentum lobortis odio.\
\
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce vitae tristique velit. Integer eu malesuada diam, ut tempus ipsum. Aenean gravida non risus ut vulputate. Etiam suscipit ipsum mi, non convallis odio luctus vel. Aenean sodales aliquet libero, et tempor enim aliquam sit amet. Donec aliquam tortor quis elit accumsan placerat. Integer dignissim justo non porta tempor. Praesent malesuada justo dolor, vel consectetur nibh cursus ornare.\
\
Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Duis congue justo sit amet diam porta, ac elementum elit hendrerit. Mauris facilisis mi vitae mi rutrum tempus. Aliquam fringilla quis est faucibus mollis. Morbi id elit vitae risus congue lobortis ut quis justo. Aenean imperdiet ipsum ac felis sagittis, at tincidunt sapien elementum. Nulla vehicula tellus quis eros egestas, et dictum diam vestibulum. Quisque tortor massa, luctus in velit in, porttitor varius lorem. Donec dictum interdum iaculis. Proin dapibus ultrices libero, a hendrerit lorem. Pellentesque gravida rhoncus nibh sed tincidunt. Suspendisse sollicitudin justo non nisl feugiat tincidunt. Nulla tempor nisi sit amet tincidunt tincidunt. Nulla et accumsan turpis.\
\
In eleifend neque sit amet facilisis aliquet. Nullam cursus egestas elit eget pulvinar. Sed mattis erat in fermentum faucibus. Quisque in eros sit amet augue pharetra rhoncus. Nullam tristique ornare neque, sit amet pellentesque lorem congue eu. Aliquam eget eros in nulla rhoncus cursus. Morbi non interdum lectus. Fusce a ligula velit. Donec pharetra urna in feugiat dapibus. Quisque molestie, velit id molestie dapibus, turpis mauris elementum ante, sit amet suscipit sem purus suscipit felis.\
\
Sed feugiat arcu ante, nec fermentum magna varius non. Duis at molestie odio, nec feugiat odio. Nam ut iaculis lorem, id malesuada metus. Pellentesque id ipsum eget ante sodales bibendum id sed turpis. Etiam adipiscing quam neque. Vestibulum fringilla, sapien vitae luctus hendrerit, justo lacus sodales nulla, nec faucibus est erat at est. Nullam aliquam non quam in dapibus. Donec dapibus urna sit amet lacus pellentesque tincidunt. In scelerisque bibendum odio sed facilisis.\
\
Integer felis ante, placerat vitae arcu vel, blandit luctus orci. Quisque vulputate ipsum ac felis gravida tincidunt. Mauris tempus non dui sit amet hendrerit. Sed lacinia turpis ut hendrerit elementum. Integer sed porta ante. Pellentesque viverra risus dolor, non accumsan risus semper et. Sed nulla libero, tristique ac condimentum a, rutrum eu neque. In lacinia lectus mauris, id posuere augue tristique rhoncus. Nunc rhoncus vitae lectus at pretium. Morbi quis fringilla nulla. Integer vitae feugiat nunc, in rutrum metus. Vestibulum quis mattis leo. Nunc odio nulla, porttitor a diam vel, tempus gravida orci.\
\
Aliquam non justo nibh. Suspendisse ut tellus orci. Interdum et malesuada fames ac ante ipsum primis in faucibus. Morbi vehicula sapien sem, non interdum erat aliquam a. Pellentesque malesuada at libero dictum consectetur. Nulla facilisi. Duis at rutrum diam, id luctus velit. Ut pulvinar eros eros, nec rhoncus orci tincidunt a.\
\
Integer rhoncus suscipit urna a feugiat. Curabitur faucibus sit amet ipsum vitae mattis. Proin rhoncus ullamcorper enim, id euismod eros consequat ac. Nam iaculis convallis nunc vel venenatis. Cras venenatis sem id nisl varius, ut luctus dolor bibendum. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aenean eu aliquet ante, ut tincidunt tellus metus.";

void ofApp::setup()
{
//    test(ofx::IO::Compression::ZLIB);
//    test(ofx::IO::Compression::GZIP);
//    test(ofx::IO::Compression::ZIP);
    test(ofx::IO::Compression::SNAPPY);
    test(ofx::IO::Compression::LZ4);
}

void ofApp::test(ofx::IO::Compression::Type type)
{
    ofx::IO::ByteBuffer raw(LOREM_IPSUM);

    ofx::IO::ByteBuffer compressed;

    std::size_t result = 0;

    result = ofx::IO::Compression::compress(raw, compressed, type);

    if (result <= 0)
    {
        ofLogError("ofApp::test()") << "Error compressing with " << ofx::IO::Compression::toString(type);
        return;
    }

    ofLogNotice("ofApp::test()") << "------------------------";
    ofLogNotice("ofApp::test()") << "      Compression Type: " << ofx::IO::Compression::toString(type);
    ofLogNotice("ofApp::test()") << "           Lib Version: " << ofx::IO::Compression::version(type);
    ofLogNotice("ofApp::test()") << "  Original buffer size: " << raw.size();
    ofLogNotice("ofApp::test()") << "Compressed buffer size: " << compressed.size();
    ofLogNotice("ofApp::test()") << "     Compression Ratio: " << ((double)compressed.size() / raw.size());

    ofx::IO::ByteBuffer uncompressed;

    result = ofx::IO::Compression::uncompress(compressed, uncompressed, type);

    if (result <= 0)
    {
        ofLogError("ofApp::test()") << "Error uncompressing with " << ofx::IO::Compression::toString(type);
        return;
    }

    ofLogNotice("ofApp::test()") << "     Uncompressed Size: " << uncompressed.size();

    std::string uncompressedString = uncompressed.toString();

    if (uncompressedString.compare(LOREM_IPSUM) == 0)
    {
        ofLogNotice("ofApp::test()") << "        String Matches: TRUE";
    }
    else
    {
        ofLogNotice("ofApp::test()") << "        String Matches: FALSE";
    }

    ofLogNotice("ofApp::test()") << "------------------------";

}
