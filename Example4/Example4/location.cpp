// #include "genlib.h"
// #include "simpio.h"
// #include "random.h"
// #include "strutils.h"
// #include "graphics.h"
// #include "extgraph.h"

#include "location.h"  //.cpp file includes its .h

Location::Location(int xVal, int yVal) {
    x = xVal;
    y = yVal;
}

int Location::getX() {
    return x;
}

int Location::getY() {
    return y;
}

void Location::translate(int dx, int dy) {
    x += dx;
    y += dy;
}
