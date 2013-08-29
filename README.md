ofxIO
=========

A collection of I/O core utils.

* `ofEvent`-based Directory Watcher
    * Watch for changes in your directories.
    * _NOTE: `Poco::DirectoryWatcher` was added in Poco 1.5+.  This feature is currently implemented using https://code.google.com/p/simplefilewatcher.  This feature will be implemented with `Poco::DirectoryWatcher` when openFrameworks includes Poco 1.5+._

* Recursive File Listing `Poco::RecursiveDirectoryIterator`
    * List files and folders inside of directories.
    * Use custom file filters to return relevant results.
    * _NOTE: `Poco::RecursiveDirectoryIterator` was added in Poco 1.6+.  These files are included for backward compatability._
* Correct alphanumeric filename ordering
    * _Note: Implemented using http://www.davekoelle.com/files/alphanum.hpp_

See the examples!