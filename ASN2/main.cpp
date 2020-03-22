#include "JsonReader/jsonReader.hpp"
#include "GA/helper.hpp"

#define DEBUG 0

const int NUM_INDIVIDUALS = 100;

int main()
{
    Individual *population[NUM_INDIVIDUALS];
    initializePopulation(population);

    std::cout << GaHelper::evaluateFitness(*population[0]);

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}