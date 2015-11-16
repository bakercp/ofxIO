ofxIO
=========

A collection of I/O core utils.

Compatible with openFrameworks 0.9.0+

For previous version of openFrameworks (e.g. 0.8.4), see https://github.com/bakercp/ofxIO/releases

Generate all project files using the openFrameworks Project Generator.

## Features
* `ofEvent`-based Directory Watcher
    * Watch for changes in your directories.
    * _NOTE: `Poco::DirectoryWatcher` was added in Poco 1.5+.  These files are included for backward compatibility._
* File filters.
* Compression
    * Zip, GZip, COBS, SLIP, etc.
* ByteBuffer
    * Tools for interacting with raw byte buffers.
* Recursive File Listing `Poco::RecursiveDirectoryIterator`
    * List files and folders inside of directories.
    * Use custom file filters to return relevant results.
    * _NOTE: `Poco::RecursiveDirectoryIterator` was added in Poco 1.6+.  These files are included for backward compatibility._
* Correct alphanumeric filename ordering
    * _Note: Implemented using http://www.davekoelle.com/files/alphanum.hpp_

See the examples!
