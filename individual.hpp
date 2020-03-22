#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include <iostream>
#include "tile.hpp"

struct Individual
{
    const Tile *tiles;
    const unsigned int size;
    unsigned int *indices = new unsigned int[size];
    float fitness = 0;

    Individual(const Tile *tiles, unsigned int size)
    : tiles(tiles), size(size) 
    {
        for(unsigned int i = 0; i < size; i++)
        {
            indices[i] = i;
        }

        std::cout << "Initialized Base\n";
    }

    bool isIdxListed(int idx)
    {
        for (int i = 0; i < size; i++)
        {
            if (idx == indices[i]) 
            {
                return true;
            }
        }

        return false;
    }

    bool areTilesEqual(const Tile &tile1, const Tile &tile2, const int idx)
    {
        return tile1 == tile2 && !isIdxListed(idx);
    }

    int findExistingTile(const Tile &tile)
    {
        for(int i = 0; i < size; i++)
        {
            const Tile &currTile = tiles[i];
            if (areTilesEqual(currTile, tile, i))
            {
                return i;
            }
        }

        // Should NEVER happen
        return -1;
    }

    Individual(const Tile *tiles, unsigned int size, const Individual *baseIndividual)
        : tiles(tiles), size(size) 
    {
        for(int i = 0; i < size; i++)
        {
            indices[i] = -1;
        }

        for(int i = 0; i < size; i++)
        {
            indices[i] = findExistingTile(baseIndividual->tiles[i]);
        }

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

        if (indices != nullptr)
        {
            delete [] indices;

            std::cout << "Destroying indices\n";

            indices = nullptr;
        }

        std::cout << "Destroyed\n";
    }
};

#endif