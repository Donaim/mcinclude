
#include "stdafx.h"
// #include "oiter.hh"
#include "s_iter.h"

#define ttext  "\t abc \t"

#define verbose true

TEST_CASE("simple") {
	if(verbose){cout << "\n\n" << "simple next" <<endl;}
    
    SIter it(ttext);
	while(it.inarr()) {
        auto c = it.next();
        if (verbose) {
            printf("[%c]", c);
        }
    }
}
TEST_CASE("turn around") {
	if(verbose){cout << "\n\n" << "turn around" << endl;}
    
    SIter it(ttext);

    it.next(); // \t
    it.next(); // ' '
    it.next(); // a
    it.next(); // b
	it.turn_around();

	while(it.inarr()) {
        auto c = it.next();
        if (verbose) {
            printf("[%c]", c);
        }
    }
}
TEST_CASE("goto beg + skip_whitespace") {
	// if(verbose){cout << "\n\n" <<"goto beg + skip_whitespace" << endl;}
    
    // SIter it(ttext);

	// while(it.inarr()) { it.next(); }
    // it.next();
    // it.next();
    // it.next();

    // it.beg();

    // // it.turn_around();
    // it.skip_whitespace();

    // // it.turn_around();

	// while(it.inarr()) {
    //     auto c = it.next();
    //     if (verbose) {
    //         printf("[%c]", c);
    //     }
    // }
}
TEST_CASE("exceed") {
	if(verbose){cout << "\n\n" << "exceed test" <<endl;}
    
    SIter it(ttext);

	while(it.inarr()) { it.next(); }
    it.next();
    it.next();
    it.next();
    it.turn_around();

	while(it.inarr()) {
        auto c = it.next();
        if (verbose) {
            printf("[%c]", c);
        }
    }
}
TEST_CASE("loop test") {
	if(verbose){cout << "\n\n" << "simple loop curr" <<endl;}
    
    SIter it(ttext);
	while(it.loop()) {
        auto c = it.curr();
        if (verbose) {
            printf("[%c]", c);
        }
    }
}
