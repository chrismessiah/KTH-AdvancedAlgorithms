#ifndef RAND
#define RAND

#include <random>
#include <ctime>

// we may want to move this out of the header file so that the distribution does
// not need to be regenerated

int randInt(int lower, int upper);

int randInt(int lower, int upper) {
    srand(time(NULL));
    return ( rand() % (upper - lower) ) + lower;
}

#endif
