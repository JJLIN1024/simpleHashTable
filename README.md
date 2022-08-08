# simpleHashTable

A simple hash table using open addressing.
## Support OS

- Ubuntu-latest
- MacOS-latest

## Basic Usage

1. clone this repository into your desired location, e.g. `dir`.
2. `cd dir`

### Quick Demo
1. `make`
2. `./hash`

A series of hash operation written in `main.c` will be performed, and the result(with explanation) will be displayed in the terminal.

### Debug
1. `make debug`

- [valgrind](https://valgrind.org/)
    - make sure [valgrind](https://valgrind.org/) is installed on your system
    - `make valgrind` 
- [cppcheck]()
    - make sure [cppcheck](https://cppcheck.sourceforge.io/) is installed on your system
    - `make check` 


## TODOs

- [ ] add test
- [ ] support for hashing with different hash functions
- [ ] better error report

## Reference

Inspired by [jamesroutley's tutorial on how to write a hash table](https://github.com/jamesroutley/write-a-hash-table).