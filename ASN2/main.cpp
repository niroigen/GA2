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
        #if DEBUG
        std::cout << i << " " << GaHelper::evaluateFitness(*population[i]) << '\n';
        #endif
    }

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}