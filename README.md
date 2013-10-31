ofxIO
=========

A collection of I/O core utils.

* `ofEvent`-based Directory Watcher
    * Watch for changes in your directories.
    * _NOTE: `Poco::DirectoryWatcher` was added in Poco 1.5+.  These files are included for backward compatability._

* Recursive File Listing `Poco::RecursiveDirectoryIterator`
    * List files and folders inside of directories.
    * Use custom file filters to return relevant results.
    * _NOTE: `Poco::RecursiveDirectoryIterator` was added in Poco 1.6+.  These files are included for backward compatability._
* Correct alphanumeric filename ordering
    * _Note: Implemented using http://www.davekoelle.com/files/alphanum.hpp_

See the examples!