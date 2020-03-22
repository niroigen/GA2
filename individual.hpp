#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include <iostream>
#include "tile.hpp"

struct Individual
{
    const Tile *tiles;
    const unsigned int size;
    float fitness;

    Individual(const Tile *tiles, unsigned int size)
    : tiles(tiles), size(size) 
    {
        std::cout << "Initialized\n";
    }

    ~Individual()
    {
        if (tiles != nullptr)
        {
            delete [] tiles;

            std::cout << "Destroying tiles\n";

            tiles = nullptr;
        }

        std::cout << "Destroyed\n";
    }
};

#endif