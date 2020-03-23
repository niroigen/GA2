#include "GA/helper.hpp"

void GaHelper::evaluatePopulation(Individual **population, int size)
{
    for (int i = 0; i < size; i++)
    {
        GaHelper::evaluateFitness(*population[i]);
    }
}

void GaHelper::evaluateFitness(Individual &individual)
{
    defaultFitnessFunction(individual);
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
    tournamentSelection(matingPool, population, GaHelper::findBestIndividual, GaHelper::pickRandomIndividuals);
}

Individual* GaHelper::getRandomParent(Individual **matingPool)
{
    std::uniform_int_distribution<> distr(0, MU - 1);

    return matingPool[distr(eng)];
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

void GaHelper::performCrossover(Individual *offspring1, Individual *offspring2,
                                std::uniform_int_distribution<>& distr)
{
    uniformCrossover(offspring1, offspring2, distr);
}

void GaHelper::performMutation(Individual *offspring)
{
    randomResetting(offspring);
}