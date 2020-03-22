#include "JsonReader/jsonReader.hpp"

const int NUM_INDIVIDUALS = 100;

int main()
{
    Individual *population[NUM_INDIVIDUALS];
    initializePopulation(population);

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}