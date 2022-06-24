# Sample programs 

The samples are mainly from Reiner Grimm's STL book.

## Prerequisites

- A modern C++ compiler: like VisualStudio 2015 or 2019.
- CMake - latest version.
- Python 3

## Resources

### Copy and Swap Idiom
https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom

### Rule of the three / five
https://en.cppreference.com/w/cpp/language/rule_of_three

https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)



## Building

Simply call `build.py build` which will build everything and put all the executables in `bin` subdirectory.

## examples

The examples contain small executables illustrating a single concept.
Each file is built to its own executable.

In fact, this is a requirement, based on how the `CMakeLists.txt` file is structured for this folder. Only single-source-file executables.

