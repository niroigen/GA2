#include "GA/crossover.hpp"

void uniformCrossover(Individual *offspring1, Individual *offspring2,
                      std::uniform_int_distribution<>& distr)
{
    const int size = offspring1->size;
    int crossover_arr[size];

    for (int i = 0; i < size; i++)
    {
        crossover_arr[i] = distr(eng);
    }

    for (int i = 0; i < size; i++)
    {
        if (crossover_arr[i] < 0.5)
        {
            int tempX = offspring1->tiles[offspring1->indices[i]].x;
            int tempY = offspring1->tiles[offspring1->indices[i]].y;

            offspring1->tiles[offspring1->indices[i]].x = offspring2->tiles[offspring2->indices[i]].x;
            offspring2->tiles[offspring2->indices[i]].x = tempX;

            offspring1->tiles[offspring1->indices[i]].y = offspring2->tiles[offspring2->indices[i]].y;
            offspring2->tiles[offspring2->indices[i]].y = tempY;
        }
    }
}

void twoPointCrossover(Individual *offspring1, Individual *offspring2,
                      std::uniform_int_distribution<>& distr)
{
    int r1, r2;

    do
    {
        r1 = distr(eng);
        r2 = distr(eng);
    } while(r1 == r2);

    int startIdx = r1, endIdx = r2;

    if (r2 < r1)
    {
        startIdx = r2;
        endIdx = r1;
    }

    Tile& tile1 = offspring1->tiles[offspring1->indices[startIdx]];
    Tile& tile2 = offspring2->tiles[offspring2->indices[startIdx]];

    for (int i = startIdx; i <= endIdx; i++)
    {
        int tempX = offspring1->tiles[offspring1->indices[i]].x;
        int tempY = offspring1->tiles[offspring1->indices[i]].y;

        offspring1->tiles[offspring1->indices[i]].x = offspring2->tiles[offspring2->indices[i]].x;
        offspring2->tiles[offspring2->indices[i]].x = tempX;

        offspring1->tiles[offspring1->indices[i]].y = offspring2->tiles[offspring2->indices[i]].y;
        offspring2->tiles[offspring2->indices[i]].y = tempY;;
    }
}