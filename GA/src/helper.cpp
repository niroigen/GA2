#include "GA/helper.hpp"

void GaHelper::evaluateFitness(Individual &individual)
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

void GaHelper::pickRandomIndividuals(Individual **randomIndividuals, Individual **population)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, NUM_INDIVIDUALS - 1);

    for (int i = 0; i < k; i++)
    {
        #if DEBUG
        std::cout << distr(eng) << '\n';
        #endif

        int randIdx = distr(eng);

        randomIndividuals[i] = population[randIdx];

        #if DEBUG
        std::cout << randomIndividuals[i]->fitness << ' ' << population[randIdx]->fitness << '\n';
        #endif
    }
}

Individual* GaHelper::findBestIndividual(Individual **individuals, int numIndividuals)
{
    unsigned int bestIdx = 0;
    float bestFitness = individuals[0]->fitness;
    for (int i = 1; i < numIndividuals; i++)
    {
        if(individuals[i]->fitness < bestFitness)
        {
            bestIdx = i;
            bestFitness = individuals[i]->fitness;
        }
    }

    return individuals[bestIdx];
}

void GaHelper::selectParents(Individual **matingPool, Individual **population)
{
    unsigned int currentMember = 0;

    while(currentMember < LAMBDA)
    {
        Individual *randomIndividuals[k];

        GaHelper::pickRandomIndividuals(randomIndividuals, population);

        Individual* bestIndividual = GaHelper::findBestIndividual(randomIndividuals, k);

        #if DEBUG
        std::cout << bestIndividual->fitness << '\n';
        #endif

        matingPool[currentMember] = bestIndividual;
        currentMember++;
    }
}
