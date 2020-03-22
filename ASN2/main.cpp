#include "JsonReader/jsonReader.hpp"
#include "GA/helper.hpp"

#define DEBUG 0

const int NUM_INDIVIDUALS = 100;
const int LAMBDA = NUM_INDIVIDUALS;
const int MU = NUM_INDIVIDUALS;

int main()
{
    Individual *population[NUM_INDIVIDUALS];
    initializePopulation(population);

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        GaHelper::evaluateFitness(*population[i]);
        #if DEBUG
        std::cout << i << " " << population[i]->fitness << '\n';
        #endif
    }

    Individual *matingPool[LAMBDA];
    GaHelper::selectParents(matingPool, population);

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}