#include "GA/fitness.hpp"

#define DEBUG_MODE 0

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#endif

void defaultFitnessFunction(Individual* individual)
{
    Matrix frame(individual->frameWidth, std::vector<int>(individual->frameLength));
    TileMatrix unique(individual->frameWidth, std::vector<std::vector<Tile*>>(individual->frameLength));

    for (int i = 0; i < individual->frameWidth; i++)
    {
        for (int j = 0; j < individual->frameLength; j++)
        {
            frame[i][j] = 1;
        }
    }

    for (int i = 0; i < individual->size; i++)
    {
        calculateOverlap(individual->tiles[i], frame, unique, individual->frameLength, individual->frameWidth);
    }

    unsigned int free_space = 0;

    for (int i = 0; i < individual->frameWidth; i++)
    {
        for (int k = 0; k < individual->frameLength; k++)
        {
            free_space += frame[i][k];

            for (int idx = 0; idx < unique[i][k].size(); idx++)
            {
                DEBUG(unique[i][k].size());
                unique[i][k][idx]->fitness = ((unique[i][k].size() - 1) * 1.0) / individual->size;
                DEBUG(unique[i][k][idx]->fitness);
                // WAIT;
            }
        }
    }

    // DEBUG(unique_space);

    double area = individual->frameLength * individual->frameWidth;

    individual->fitness = (free_space * 1.0)/area;//+ (((unique_space * 1.0)/area) * 0.01));
}

void calculateOverlap(Tile& tile, Matrix& frame, TileMatrix& unique, const int frameLength, const int frameWidth)
{
    int overlap = 0;
    for (int j = tile.y; j < tile.y + tile.w; j++)
    {
        for (int k = tile.x; k < tile.x + tile.l; k++)
        {
            if (k < frameLength && j < frameWidth)
            {
                frame[j][k] = 0;
                unique[j][k].push_back(&tile);
            }
        }
    }
}