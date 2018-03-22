
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
TEST_CASE("bounds check") {
	if(verbose){cout << "\n\n" << "bounds check" <<endl;}
    
    SIter it(ttext);

    CHECK_NOTHROW(
        while(it.inarr()) { it.next(); }
        it.next();
        it.next();
        printf("%c", it.next());
        it.next();
    );

    CHECK_THROWS(
        it.look(2);
    );

    CHECK_THROWS(
        it.curr();
    );
}