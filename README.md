ofxIO
=========

A collection of I/O core utils.

## Compatibility
The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master).

Some past openFrameworks releases are supported via tagged versions, but only `stable` and `master` branches are actively supported.

## Project Files

Generate all project files using the openFrameworks [Project Generator](http://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/).

## Features
- `ofEvent`-based Directory Watcher
  - Watch for changes in your directories.
  - _NOTE: `Poco::DirectoryWatcher` was added in Poco 1.5+.  These files are included for backward compatibility._
- File filters.
- Compression
  - Zip, deflate, gzip, snappy, LZ4
  - Encoding.
    - COBS, SLIP, Hex Binary, Base64, etc.
- ByteBuffer
  - Tools for interacting with raw byte buffers.
  - ByteBuffer streams.
  - ByteBufferReader.
  - ByteBufferWriter.
  - ByteBufferStream.
- Recursive File Listing `Poco::RecursiveDirectoryIterator`
  - List files and folders inside of directories.
  - Use custom file filters to return relevant results.
    - _NOTE: `Poco::RecursiveDirectoryIterator` was added in Poco 1.6+.  These files are included for backward compatibility._
- Correct alphanumeric filename ordering
  - _Note: Implemented using [alphanum.hpp](http://www.davekoelle.com/files/alphanum.hpp)_

## Contributing

Pull Requests are always welcome, so if you make any improvements please feel free to float them back upstream :)

1. [Fork this repository on Github](https://github.com/bakercp/ofxIO).
2. Create your feature branch (`git checkout -b my-new-feature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin my-new-feature`).
5. Create new Pull Request.
