#pragma once

#include <iostream>
#include <cstdint>

struct Individual
{
    unsigned int rules[32];
    int initialState;
    int goalState;
    float fitness = 0;

    Individual() {}
    Individual(unsigned int*, int, int);

    // Individual(Tile*, unsigned int,
    //            unsigned int, unsigned int);
    // Individual(Tile*, unsigned int, const Individual*, unsigned int, unsigned int);
    // Individual(const Individual&);
    // Individual& operator=(const Individual&);
    // ~Individual();


    // bool isIdxListed(int);
    // bool areTilesEqual(const Tile&, const Tile&, const int);
    // int findExistingTile(const Tile&);
};