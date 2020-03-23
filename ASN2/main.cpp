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

    Individual *offsprings[LAMBDA];
    GaHelper::createOffsprings(offsprings, matingPool);

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}