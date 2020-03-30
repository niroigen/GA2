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
    int frame[individual->frameWidth][individual->frameLength];
    std::vector<Tile*> unique[individual->frameWidth][individual->frameLength];

    for (int i = 0; i < individual->frameWidth; i++)
    {
        for (int j = 0; j < individual->frameLength; j++)
        {
            frame[i][j] = 1;
        }
    }

    for (int i = 0; i < individual->size; i++)
    {
        int overlap = 0;
        for (int j = individual->tiles[i].y; j < individual->tiles[i].y + individual->tiles[i].w; j++)
        {
            for (int k = individual->tiles[i].x; k < individual->tiles[i].x + individual->tiles[i].l; k++)
            {
                if (k < individual->frameLength && j < individual->frameWidth)
                {
                    frame[j][k] = 0;
                    unique[j][k].push_back(&individual->tiles[i]);
                }
            }
        }
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