#include "GA/individual.hpp"

Individual::Individual(Tile *tiles, unsigned int size,
                       unsigned int frameLength, unsigned int frameWidth)
    : tiles(tiles), size(size), frameLength(frameLength), frameWidth(frameWidth)
{
    for(unsigned int i = 0; i < size; i++)
    {
        indices[i] = i;
    }

    #if DEBUG
    std::cout << "Initialized Base\n" << size << '\n';
    #endif
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

    #if DEBUG
    std::cout << "Initialized\n";
    #endif
}

Individual::Individual(const Individual& individual)
    : size(individual.size), frameLength(individual.frameLength),
      frameWidth(individual.frameWidth)
{
    tiles = new Tile[individual.size];

    for (int i = 0; i < individual.size; i++)
    {
        tiles[i] = individual.tiles[i];
    }

    for (int i = 0; i < individual.size; i++)
    {
        indices[i] = individual.indices[i];
    }

    std::cout << "Individual Copy Constructor"<< std::endl;
}

Individual& Individual::operator=(const Individual& individual)
{
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

    std::cout << "Individual Assignment Operator Called"<< std::endl;

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

        #if DEBUG == 1
        std::cout << "Destroying tiles\n";
        #endif

        tiles = nullptr;
    }

    if (indices != nullptr)
    {
        delete [] indices;

        #if DEBUG
        std::cout << "Destroying indices\n";
        #endif

        indices = nullptr;
    }

    #if DEBUG
    std::cout << "Destroyed\n";
    #endif
}