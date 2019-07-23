# ofxIO

## Description

A collection of I/O core utils for [openFrameworks](https://openframeworks.cc).

## Features

- `ofEvent`-based Directory Watcher
  - Watch for changes in your directories.
  - _NOTE: `Poco::DirectoryWatcher` was added in Poco 1.5+.  These files are included for backward compatibility._
- File filters.
- Compression
  - Zip, deflate, gzip, [snappy](https://github.com/google/snappy), [LZ4](https://github.com/lz4/lz4), [brotli](https://github.com/google/`brotli`)
  - Encoding`.`
    - COBS, `SLIP`, Hex Binary, Base64, etc.
- `ByteBuffer`
  - Tools for interacting with raw byte buffers.
  - `ByteBuffer` streams.
  - `ByteBufferReader`.
  - `ByteBufferWriter`.
  - `ByteBufferStream`.
- Recursive File Listing `Poco::RecursiveDirectoryIterator`
  - List files and folders inside of directories.
  - Use custom file filters to return relevant results.
    - _NOTE: `Poco::RecursiveDirectoryIterator` was added in Poco 1.6+.  These files are included under the `ofxIO` namespace for backward compatibility._
- Correct alphanumeric filename ordering
  - _Note: Implemented using [alphanum.hpp](http://www.davekoelle.com/files/alphanum.hpp)_

## Getting Started

### Bootstrap

Every effort is made to keep the repository small. Thus sometimes third-party libraries need to be compiled and example data needs to be downloaded. The bootstrap script takes care of this.

-   From the `scripts/` directory ...
    -   `./bootstrap.sh`

### Generate Project Files

1.   Generate the example project files using the openFrameworks [Project Generator](http://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/).
2.   Open the Project Files in your Integrated Development Environment (IDE), or run `make && make run` from the example directory.

For more, see [docs/GETTING_STARTED.md](docs/GETTING_STARTED.md).

## Support

See [docs/SUPPORT.md](docs/SUPPORT.md).

## Documentation

API documentation can be found [here](https://bakercp.github.io/ofxAddon/).

## Requirements

-   ofxPoco (included with openFrameworks)

## Compatibility

### Supported Platforms

| Platform          | Build Status | Notes  |
|-------------------|--------------|--------|
| **osx**           |      ❓      | _None_ |
| **linux**         |      ❓      | _None_ |
| **Linux64**       |      ❓      | _None_ |
| **linuxarmv6l**   |      ❓      | _None_ |
| **msys2**         |      ❓      | _None_ |
| **vs**            |      ❓      | _None_ |
| **ios**           |      ❓      | _None_ |
| **tvos**          |      ❓      | _None_ |
| **emscripten**    |      ❓      | _None_ |
| **android**       |      ❓      | _None_ |

|      Status      | Symbol |
|------------------|--------|
| **Tested**       |   ✅   | 
| **Untested**     |   ⚠️   |
| **Incompatible** |   ❌   |
| **Unknown**      |   ❓   |

Linux, macOS [![Build Status](https://travis-ci.org/bakercp/ofxIO.svg?branch=master)](https://travis-ci.org/bakercp/ofxIO)

Visual Studio, MSYS [![Build status](https://ci.appveyor.com/api/projects/status/krr0ck8ffida8nsj/branch/master?svg=true)](https://ci.appveyor.com/project/bakercp/ofxio/branch/master)

### Build Status

The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master).

Some past openFrameworks releases are supported via tagged versions, but only `stable` and `master` branches are actively supported.

### Branches

The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master). This is often the same as the `stable` branch.

The `develop` branch of this repository is used by developers to test new features. It is usually compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master), but is compatibility is not guaranteed. The `develop` branch should not be used for production.

Some past openFrameworks releases are supported via tagged versions and [releases](releases/), but only `stable` and `master` branches are actively supported.

## Versioning

This project uses [Semantic Versioning](http://semver.org/spec/v2.0.0.html), although strict adherence will only come into effect at version 1.0.0.

## Changelog

See [CHANGELOG.md](CHANGELOG.md)

## Code of Conduct

See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md)

## Licensing

See [LICENSE.md](LICENSE.md)
