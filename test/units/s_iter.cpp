
#include "stdafx.h"
// #include "oiter.hh"
#include "s_iter.h"

#define ttext  "\t abc \t"

TEST_CASE("simple") {
	INFO("simple next");
    
    SIter it = SIter::create_local(ttext);
	while(it.inarr()) {
        const char c = it.next();
        DPLOGH("[%c]", c);
    }

    DNEWL();
}
TEST_CASE("turn around") {
	INFO("turn around");
    
    SIter it = SIter::create_local(ttext);

    it.next(); // \t
    it.next(); // ' '
    it.next(); // a
    it.next(); // b
	it.turn_around();

	while(it.inarr()) {
        auto c = it.next();
        DPLOGH("[%c]", c);
    }
    DNEWL();
}
TEST_CASE("exceed") {
	INFO("exceed test");
    
    SIter it = SIter::create_local(ttext);

	while(it.inarr()) { it.next(); }
    it.next();
    it.next();
    it.next();
    it.turn_around();

	while(it.inarr()) {
        auto c = it.next();
        DPLOGH("[%c]", c);
    }
    DNEWL();
}
TEST_CASE("loop test") {
	INFO("simple loop curr");
    
    SIter it = SIter::create_local(ttext);
	while(it.loop()) {
        auto c = it.curr();
        DPLOGH("[%c]", c);
    }
    DNEWL();
}
TEST_CASE("bounds check") {
    INFO("bounds check");

    SIter it = SIter::create_local(ttext);

    while(it.inarr()) { it.next(); }
    it.next();
    it.next();
    char c = it.next();
    DPLOGH("[%c]", c);
    it.next();

    CHECK_NOTHROW( // because string is supposed to return '\0', not throw
        it.look(20);
    );

    CHECK_NOTHROW( // same here
        it.curr();
    );
}