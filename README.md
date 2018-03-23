

# To do
- [x] faster project compilations: split compilation and linking with scripts
- [X] make test compilation faster
- [ ] implement `reverse` on SIter
- [ ] make possible with mcincluder to generate precompiled headers for each individual file. Because now only possible that only first header can be precompiled which is silly
- [ ] call mxxbuild from runtest directly (`import mxxbuild`)
- [ ] make possible to imitate classes (and inheritance) in C with mcinclude

# What ive learned
- always split .h and .cpp
- use forward-declarations as much as possible
- dont use `inline` in definition if declaration does not have it
- use `&&` (move) references. [tutor](https://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11)


