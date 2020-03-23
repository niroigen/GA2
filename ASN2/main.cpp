#include <chrono>
#include "Json/jsonReader.hpp"
#include "Json/jsonWriter.hpp"
#include "GA/helper.hpp"

#define DEBUG 0

const int NUM_INDIVIDUALS = 100;
const int MU[] = {75};
const int LAMBDA[] = {75 * 6};
const int k[] = {65};
const float CROSSOVER_RATE[] = {0.65};
const float MUTATION_RATE[] = {0.05};

int curr = 0;
auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 eng {seed};

int main()
{
    for (int test = 0; test < 5; test++)
    {
        for(curr = 0; curr < 10; curr++)
        {
            Individual *population[NUM_INDIVIDUALS];
            Individual *matingPool[MU[0]];
            Individual *offsprings[LAMBDA[0]];

            initializePopulation(population);
            GaHelper::evaluatePopulation(population);

            Individual* bestIndividualInit = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);

            for (int gen = 0; gen < 100; gen++)
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

                for (int i = NUM_INDIVIDUALS; i < LAMBDA[0]; i++)
                {
                    delete offsprings[i];
                }
            }

            GaHelper::evaluatePopulation(population);

            Individual* bestIndividual = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
            std::cout << bestIndividual->fitness << ',' << ' ';

            outputBestIndividual(bestIndividual);

            for (int i = 0; i < NUM_INDIVIDUALS; i++)
            {
                delete population[i];
            }
        }

        std::cout << std::endl;
    }
}