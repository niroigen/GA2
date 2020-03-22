#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include <iostream>
#include "GA/tile.hpp"

struct Individual
{
    const Tile *tiles;
    const unsigned int size, frameLength, frameWidth;
    unsigned int *indices = new unsigned int[size];
    float fitness = 0;

    Individual(const Tile *tiles, unsigned int size, 
               unsigned int frameLength, unsigned int frameWidth);
    Individual(const Tile *tiles, unsigned int size, const Individual *baseIndividual,
               unsigned int frameLength, unsigned int frameWidth);
    ~Individual();

    bool isIdxListed(int idx);
    
    bool areTilesEqual(const Tile &tile1, const Tile &tile2, const int idx);

    int findExistingTile(const Tile &tile);    
};

#endif