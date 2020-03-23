#include "GA/fitness.hpp"

void defaultFitnessFunction(Individual& individual)
{
    int frame[individual.frameWidth][individual.frameLength];

    for (int i = 0; i < individual.frameWidth; i++)
    {
        for (int j = 0; j < individual.frameLength; j++)
        {
            frame[i][j] = 1;
        }
    }

    for (int i = 0; i < individual.size; i++)
    {
        for (int j = individual.tiles[i].y; j < individual.tiles[i].y + individual.tiles[i].w; j++)
        {
            for (int k = individual.tiles[i].x; k < individual.tiles[i].x + individual.tiles[i].l; k++)
            {
                if (k < individual.frameLength && j < individual.frameWidth)
                {
                    frame[j][k] = 0;
                }
            }
        }
    }

    unsigned int free_space = 0;

    for (int i = 0; i < individual.frameWidth; i++)
    {
        for (int k = 0; k < individual.frameLength; k++)
        {
            free_space += frame[i][k];
        }
    }

    individual.fitness = ((free_space * 1.0)/(individual.frameLength * individual.frameWidth) * 100);
}