#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include <iostream>
#include "GA/tile.hpp"

struct Individual
{
    Tile *tiles;
    unsigned int size, frameLength, frameWidth;
    unsigned int *indices = new unsigned int[size];
    float fitness = 0;

    Individual() {}
    Individual(Tile*, unsigned int,
               unsigned int, unsigned int);
    Individual(Tile*, unsigned int, const Individual*, unsigned int, unsigned int);
    Individual(const Individual&);
    Individual& operator=(const Individual&);
    ~Individual();


    bool isIdxListed(int);
    bool areTilesEqual(const Tile&, const Tile&, const int);
    int findExistingTile(const Tile&);
};

#endif