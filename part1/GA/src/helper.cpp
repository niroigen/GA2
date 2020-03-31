#include "GA/helper.hpp"

#define DEBUG_MODE 0

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#define WAIT
#endif

void GaHelper::evaluatePopulation(Individual** population, int size)
{
    std::vector<std::thread> threads;
    for (int i = 0; i < size; i++)
    {
        threads.push_back(std::thread(evaluateFitness, population[i]));
    }

    for (std::thread & th : threads)
    {
        if (th.joinable())
            th.join();
    }
}

void GaHelper::evaluateFitness(Individual* individual)
{
    defaultFitnessFunction(individual);
}

void GaHelper::survivorSelection(Individual** population, Individual** offsprings)
{
    replacePopulation(population, offsprings, LAMBDA);
}

void GaHelper::pickRandomIndividuals(Individual** randomIndividuals, Individual** population, int k)
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

Individual* GaHelper::findBestIndividual(Individual** individuals, int numIndividuals)
{
    unsigned int bestIdx = 0;
    float bestFitness = individuals[0]->fitness;
    for (int i = 0; i < numIndividuals; i++)
    {
        if(individuals[i]->fitness < bestFitness)
        {
            bestIdx = i;
            bestFitness = individuals[i]->fitness;
        }
    }

    return individuals[bestIdx];
}

void GaHelper::selectParents(Individual** matingPool, Individual** population)
{
    tournamentSelection(matingPool, population, k, MU, findBestIndividual, pickRandomIndividuals);
}

Individual* GaHelper::getRandomParent(Individual** matingPool)
{
    std::uniform_int_distribution<> distr(0, MU - 1);

    Individual* test = matingPool[distr(eng)];

    return matingPool[distr(eng)];
}

bool GaHelper::compareIndividual(const Individual* i1, const Individual* i2)
{
    return i1->fitness < i2->fitness;
}

bool GaHelper::areSameSpecies(Individual* i1, Individual* i2)
{
    float distance = Individual::geneticDistance(i1, i2);
    if (distance != 0 && distance < maxDistance) maxDistance = distance;

    DEBUG(std::to_string(distance) + " " + std::to_string(std::sqrt(maxDistance)));

    return Individual::geneticDistance(i1, i2) < 130;
}


void GaHelper::createOffsprings(Individual** offsprings, Individual** matingPool)
{
    int i = 0;

    std::uniform_real_distribution<> dist(0, 1);
    
    std::uniform_int_distribution<> distr(0, matingPool[0]->size - 1);

    while(i < LAMBDA)
    {
        Individual* parent1;
        Individual* parent2;

        do 
        {
            parent1 = GaHelper::getRandomParent(matingPool);
            parent2 = GaHelper::getRandomParent(matingPool);

            DEBUG("PICKING PARENT")
        } while(!areSameSpecies(parent1, parent2));

        DEBUG("DONE");
        WAIT;

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
    randomResetting(offspring, MUTATION_RATE);
}