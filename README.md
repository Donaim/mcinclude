# MCINCLUDE
Includes some preprocessor magic to your project.  
[previous version](https://github.com/Donaim/pyincluder)  

## Currently available:
- `#include <targetpath>` [`at labelname`]  
    Just copies the content of `targetpath` file.  
    Hovewer there are some improvements over std c include:
    - `at (destination)` option  
        Allows to copy content at specific location in source file (based on labels)
- `#label name`   
    Defines _target-point_ for instructions like `#include`, `#moveat`
- `#moveat labelname` [`lines_count: int`]  
    Moves text below at `labelname` position
    _text below_ should end with `#endmove` line. Alternatively if `lines_count` provided _text below_ ends in that many lines  
    Does not allow for repetitions by default  

# Compilation
- with scripts:  
    `$ python3.5 scripts/mxxbuildlnk.py ./src` 
- manual  
    `$ find ./src -name "*.cpp" -exec g++ -c {} -o ./build/$(basename {}) \;`  
    `$ cd ./build`  
    `$ g++ *.o`  

# Testing
Required [DOCTEST](https://github.com/onqtam/doctest) to be located in ./extern/doctest  

example testing with scripts:  
`$ python3.5 scripts/runtest.py sfile`  


# To do
- [x] faster project compilations: split compilation and linking with scripts
- [X] make test compilation faster
- [ ] make quote splitters trim `\"` 
- [X] write `install.py` script for downloading externs
- [X] make portable to linux
- [ ] <del>make mlog cross-platform without need of recompiling</del>
- [ ] implement `reverse` on SIter
- [ ] make possible with mcincluder to generate precompiled headers for each individual file. Because now only possible that only first header can be precompiled which is silly
- [X] call mxxbuild from runtest directly (`import mxxbuild`)
- [ ] make possible to imitate classes (and inheritance) in C with mcinclude
- [X] tags in argparse should start with `-` or `+` as booleans
- [ ] search for tags/options/nargs from end in argparse
- [ ] create even more human-readable argparser
- [ ] make startswith also check if next char after requiered is white_space
- [X] add `#label` instruction
- [ ] `at` option for `#label`
- [X] add `#include` instruction
- [X] add `#moveat` instruction
- [ ] `if` option for `#moveat`
- [ ] add `#template` instruction
- [ ] improve conditions for `if` option (maybe even up to dynamic compilation)
- [ ] make `if` syntaxis like: `#if cond then #include <filename>`, instead of `#include <filename> if cond`
- [ ] create event-system in Scope for better instructions management
- [ ] [hard] make instructions (and other objects like SFile) load dynamically 
- [ ] make example files in `/example` dir
- [ ] write better README

## What ive learned
- always split .h and .cpp
- use forward-declarations as much as possible
- dont use `inline` in definition if declaration does not have it
- use `&&` (move) references. [tutor](https://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11)
- use smart pointers. shared_ptr is espacially useful
- don't ever use strcpy and such !! have no idea how safe they are