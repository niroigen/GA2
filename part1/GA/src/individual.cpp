#include "GA/individual.hpp"

#define DEBUG_MODE 0

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#else
#define DEBUG(x)
#endif

Individual::Individual(Tile *tiles, unsigned int size,
                       unsigned int frameLength, unsigned int frameWidth)
    : tiles(tiles), size(size), frameLength(frameLength), frameWidth(frameWidth)
{
    for(unsigned int i = 0; i < size; i++)
    {
        indices[i] = i;
    }

    DEBUG("Initialized Base")
}

Individual::Individual(Tile *tiles, unsigned int size, const Individual *baseIndividual,
                       unsigned int frameLength, unsigned int frameWidth)
        : tiles(tiles), size(size), frameLength(frameLength), frameWidth(frameWidth)
{
    for(int i = 0; i < size; i++)
    {
        indices[i] = -1;
    }

    for(int i = 0; i < size; i++)
    {
        indices[i] = findExistingTile(baseIndividual->tiles[i]);
    }

    DEBUG("Initialized")
}

Individual::Individual(const Individual& individual)
    : size(individual.size), frameLength(individual.frameLength),
      frameWidth(individual.frameWidth)
{
    DEBUG("Starting copy constructor")
    tiles = new Tile[individual.size];

    for (int i = 0; i < individual.size; i++)
    {
        tiles[i] = individual.tiles[i];
    }

    for (int i = 0; i < individual.size; i++)
    {
        indices[i] = individual.indices[i];
    }

    DEBUG("Individual Copy Constructor")
}

Individual& Individual::operator=(const Individual& individual)
{
    DEBUG("Starting assignmnet operator");
    tiles = new Tile[individual.size];

    for (int i = 0; i < individual.size; i++)
    {
        tiles[i] = individual.tiles[i];
    }

    for (int i = 0; i < individual.size; i++)
    {
        indices[i] = individual.indices[i];
    }

    size = individual.size;
    frameLength = individual.frameLength;
    frameWidth = individual.frameWidth;

    DEBUG("Individual Assignment Operator Called")

    return *this;
}

bool Individual::isIdxListed(int idx)
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

bool Individual::areTilesEqual(const Tile &tile1, const Tile &tile2, const int idx)
{
    return tile1 == tile2 && !isIdxListed(idx);
}

int Individual::findExistingTile(const Tile &tile)
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

Individual::~Individual()
{
    if (tiles != nullptr)
    {
        delete [] tiles;

        DEBUG("Destroying tiles")

        tiles = nullptr;
    }

    if (indices != nullptr)
    {
        delete [] indices;

        DEBUG("Destroying indices")

        indices = nullptr;
    }

    DEBUG("Destroyed")
}