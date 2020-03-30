#include "GA/mutation.hpp"

void randomResetting(Individual *offspring, const float MUTATION_RATE)
{
    std::uniform_real_distribution<> dist(0, 1);
    std::uniform_real_distribution<> distX(0, offspring->frameLength);
    std::uniform_real_distribution<> distY(0, offspring->frameWidth);

    for (int i = 0; i < offspring->size; i++)
    {
        auto r1 = dist(eng);
        auto r2 = dist(eng);
        auto r3 = dist(eng);

        if (r1 <= offspring->tiles[i].fitness + MUTATION_RATE)
        {
            offspring->tiles[i].x = distX(eng);
        }

        if (r2 <= offspring->tiles[i].fitness + MUTATION_RATE)
        {
            offspring->tiles[i].y = distY(eng);
        }

        if (r3 <= offspring->tiles[i].fitness + MUTATION_RATE)
        {
            auto temp = offspring->tiles[i].l;
            offspring->tiles[i].l = offspring->tiles[i].w;
            offspring->tiles[i].w = temp;
        }
    }
}