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
int generation = 0;

void freePopulation(Individual **population);
void freeOffsprings(Individual **offsprings);
void replacePopulation(Individual **population,Individual **offsprings);

int main()
{
    Individual *population[NUM_INDIVIDUALS];
    Individual *matingPool[MU];
    Individual *offsprings[LAMBDA];

    initializePopulation(population);
    GaHelper::evaluatePopulation(population);

    Individual* bestIndividualInit = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
    std::cout << bestIndividualInit->fitness << '\n';

    for (; generation < 1000; generation++)
    {
        // Selecting parents for next generation
        GaHelper::selectParents(matingPool, population);

        // Creating offsprings off of the potential parents
        GaHelper::createOffsprings(offsprings, matingPool);

        // Evaluating their fitness level
        GaHelper::evaluatePopulation(offsprings, LAMBDA);

        // Freeing the population
        freePopulation(population);

        // Sorting the by fitness
        std::sort(offsprings, offsprings+LAMBDA, GaHelper::compareIndividual);

        // Replace the population with NUM_INDIVIDUAL's best offspring
        replacePopulation(population, offsprings);

        // Freeing the offspring that will no longer be used
        freeOffsprings(offsprings);
    }

    Individual* bestIndividual = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
    std::cout << bestIndividual->fitness << '\n';

    outputBestIndividual(bestIndividual);

    freePopulation(population);
}

void freePopulation(Individual **population)
{
    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}

void replacePopulation(Individual **population, Individual **offsprings)
{
    int numToReplace = NUM_INDIVIDUALS;

    if (LAMBDA < NUM_INDIVIDUALS) {
        numToReplace = LAMBDA;
    }
    for (int i = NUM_INDIVIDUALS - 1; i > (NUM_INDIVIDUALS - 1) - numToReplace; i--)
    {
        population[i] = offsprings[i];
    }
}

void freeOffsprings(Individual **offsprings)
{
    if (NUM_INDIVIDUALS < LAMBDA)
    {
        for (int i = NUM_INDIVIDUALS; i < LAMBDA; i++)
        {
            delete offsprings[i];
        }
    }
}