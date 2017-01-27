ofxIO
=========

## Description

A collection of I/O core utils.

## Features

- `ofEvent`-based Directory Watcher
  - Watch for changes in your directories.
  - _NOTE: `Poco::DirectoryWatcher` was added in Poco 1.5+.  These files are included for backward compatibility._
- File filters.
- Compression
  - Zip, deflate, gzip, [snappy](https://github.com/google/snappy), [LZ4](https://github.com/lz4/lz4), [brotli](https://github.com/google/brotli)
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
    - _NOTE: `Poco::RecursiveDirectoryIterator` was added in Poco 1.6+.  These files are included under the `ofxIO` namespace for backward compatibility._
- Correct alphanumeric filename ordering
  - _Note: Implemented using [alphanum.hpp](http://www.davekoelle.com/files/alphanum.hpp)_

## Getting Started

To get started, generate the example project files using the openFrameworks [Project Generator](http://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/).

## Documentation

API documentation can be found here.

## Build Status

Linux, macOS [![Build Status](https://travis-ci.org/bakercp/ofxIO.svg?branch=master)](https://travis-ci.org/bakercp/ofxIO)

Visual Studio, MSYS [![Build status](https://ci.appveyor.com/api/projects/status/krr0ck8ffida8nsj/branch/master?svg=true)](https://ci.appveyor.com/project/bakercp/ofxio/branch/master)

## Compatibility

The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master).

Some past openFrameworks releases are supported via tagged versions, but only `stable` and `master` branches are actively supported.

## Versioning

This project uses Semantic Versioning, although strict adherence will only come into effect at version 1.0.0.

## Licensing

See `LICENSE.md`.

## Contributing

Pull Requests are always welcome, so if you make any improvements please feel free to float them back upstream :)

1. Fork this repository.
2. Create your feature branch (`git checkout -b my-new-feature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin my-new-feature`).
5. Create new Pull Request.
