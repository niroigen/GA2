#include <chrono>
#include "JsonReader/jsonReader.hpp"
#include "GA/helper.hpp"

#define DEBUG 0

const int NUM_INDIVIDUALS = 100;
const int LAMBDA = NUM_INDIVIDUALS;
const int MU = NUM_INDIVIDUALS;
auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 eng {seed};

int main()
{
    Individual *population[NUM_INDIVIDUALS];
    Individual *matingPool[LAMBDA];
    Individual *offsprings[LAMBDA];

    initializePopulation(population);

    for (int gen = 0; gen < 1000; gen++)
    {
        for (int i = 0; i < NUM_INDIVIDUALS; i++)
        {
            GaHelper::evaluateFitness(*population[i]);
            #if DEBUG
            std::cout << i << " " << population[i]->fitness << '\n';
            #endif
        }

        GaHelper::selectParents(matingPool, population);
        GaHelper::createOffsprings(offsprings, matingPool);

        Individual* bestIndividual = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);

        std::cout << bestIndividual->fitness << '\n';

        for (int i = 0; i < NUM_INDIVIDUALS; i++)
        {
            delete population[i];
        }

        for (int i = 0; i < NUM_INDIVIDUALS; i++)
        {
            population[i] = offsprings[i];
        }
    }

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}