// I functional line //

#pragma once

// #include "line.h"
class Line;

class ILineFactory {

public:

    virtual Line * try_create(const Line& str) = 0;
};

