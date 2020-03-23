#include <chrono>
#include "Json/jsonReader.hpp"
#include "Json/jsonWriter.hpp"
#include "GA/helper.hpp"

#define DEBUG 0

const int NUM_INDIVIDUALS = 100;
const int MU = 75;
const int LAMBDA = 6 * MU;
auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 eng {seed};

int main()
{
    Individual *population[NUM_INDIVIDUALS];
    Individual *matingPool[MU];
    Individual *offsprings[LAMBDA];

    initializePopulation(population);
    GaHelper::evaluatePopulation(population);

    Individual* bestIndividualInit = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
    std::cout << bestIndividualInit->fitness << '\n';

    for (int gen = 0; gen < 1000; gen++)
    {
        GaHelper::selectParents(matingPool, population);
        GaHelper::createOffsprings(offsprings, matingPool);

        for (int i = 0; i < NUM_INDIVIDUALS; i++)
        {
            delete population[i];
        }

        for (int i = 0; i < NUM_INDIVIDUALS; i++)
        {
            population[i] = offsprings[i];
        }

        for (int i = NUM_INDIVIDUALS; i < LAMBDA; i++)
        {
            delete offsprings[i];
        }
    }

    GaHelper::evaluatePopulation(population);

    Individual* bestIndividual = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
    std::cout << bestIndividual->fitness << '\n';

    outputBestIndividual(bestIndividual);

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}