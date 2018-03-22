#pragma once

class SIter {
    int dir; // direction
    const int len;
    mutable int pos;
    const char * const source; 
public:
    SIter(const char * source);
    SIter(const char * source, int len, int pos = -1, int dir = 1);

    int direction() const; // dir
    void turn_around(); // dir *= -1
    // void reverse(); // dev: hard to implement without copying

    // void skip_whitespace() const;
    // void skip_chars(const char * arr) const;
    
    bool inarr() const; // true if pos in range of `source` 
    bool loop() const; // do `skip`, then return `inarr()`
    
    char look(int at) const; // shows `at`'th element in `dir` direction
    char curr() const; // same as look(0)
    void skip() const; // increments `pos`
    void beg() const; // go-to begining (or end if dir < 0)
    char next() const; // do `skip`, then return `curr()`
    char next_look() const; // do `next` then return `look(1)`
};