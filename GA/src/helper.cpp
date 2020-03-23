#include "GA/helper.hpp"
#include "GA/crossover.hpp"

void GaHelper::evaluatePopulation(Individual **population, int size)
{
    for (int i = 0; i < size; i++)
    {
        GaHelper::evaluateFitness(*population[i]);
    }
}

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

    while(currentMember < MU)
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

Individual* GaHelper::getRandomParent(Individual **matingPool)
{
    std::uniform_int_distribution<> distr(0, MU - 1);

    return matingPool[distr(eng)];
}

void GaHelper::performCrossover(Individual *offspring1, Individual *offspring2,
                                std::uniform_int_distribution<>& distr)
{
    twoPointCrossover(offspring1, offspring2, distr);
}

bool GaHelper::compareIndividual(const Individual* i1, const Individual* i2)
{
    return i1->fitness < i2->fitness;
}

void GaHelper::createOffsprings(Individual **offsprings, Individual **matingPool)
{
    int i = 0;

    std::uniform_real_distribution<> dist(0, 1);
    std::uniform_int_distribution<> distr(0, matingPool[0]->size - 1);

    while(i < LAMBDA)
    {
        Individual* parent1 = GaHelper::getRandomParent(matingPool);
        Individual* parent2 = GaHelper::getRandomParent(matingPool);

        float r = dist(eng);

        Individual* offspring1 = new Individual(*parent1);
        Individual* offspring2 = new Individual(*parent2);

        if (r <= CROSSOVER_RATE)
        {
            GaHelper::performCrossover(offspring1, offspring2, distr);
        }

        GaHelper::performMutation(offspring1);
        GaHelper::performMutation(offspring2);

        offsprings[i++] = offspring1;
        offsprings[i++] = offspring2;
    }
}

void GaHelper::performMutation(Individual *offspring)
{
    std::uniform_real_distribution<> dist(0, 1);
    std::uniform_real_distribution<> distX(0, offspring->frameLength);
    std::uniform_real_distribution<> distY(0, offspring->frameWidth);

    for (int i = 0; i < offspring->size; i++)
    {
        auto r1 = dist(eng);
        auto r2 = dist(eng);
        auto r3 = dist(eng);

        if (r1 <= MUTATION_RATE)
        {
            offspring->tiles[i].x = distX(eng);
        }

        if (r2 <= MUTATION_RATE)
        {
            offspring->tiles[i].y = distY(eng);
        }

        if (r3 <= MUTATION_RATE)
        {
            auto temp = offspring->tiles[i].l;
            offspring->tiles[i].l = offspring->tiles[i].w;
            offspring->tiles[i].w = temp;
        }
    }
}