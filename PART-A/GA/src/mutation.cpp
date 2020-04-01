#include "GA/mutation.hpp"

void resetGene(Individual *offspring, const int idx, const float MUTATION_RATE)
{
    std::uniform_real_distribution<> dist(0, 1);
    std::uniform_real_distribution<> distX(0, offspring->frameLength);
    std::uniform_real_distribution<> distY(0, offspring->frameWidth);

    auto r1 = dist(eng);
    auto r2 = dist(eng);
    auto r3 = dist(eng);

    if (r1 <= offspring->tiles[idx].fitness + MUTATION_RATE)
    {
        offspring->tiles[idx].x = distX(eng);
    }

    if (r2 <= offspring->tiles[idx].fitness + MUTATION_RATE)
    {
        offspring->tiles[idx].y = distY(eng);
    }

    if (r3 <= offspring->tiles[idx].fitness + MUTATION_RATE)
    {
        auto temp = offspring->tiles[idx].l;
        offspring->tiles[idx].l = offspring->tiles[idx].w;
        offspring->tiles[idx].w = temp;
    }
}

void randomResetting(Individual *offspring, const float MUTATION_RATE)
{
    std::vector<std::thread> threads;

    for (int i = 0; i < offspring->size; i++)
    {
        threads.push_back(std::thread(resetGene, offspring, i, MUTATION_RATE));
    }

    for (std::thread & th : threads)
    {
        if (th.joinable())
            th.join();
    }
}