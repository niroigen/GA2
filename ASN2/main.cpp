#include <chrono>
#include "GA/ga.hpp"

#define DEBUG 1
#define PARAMETER_TUNING 0

const int NUM_INDIVIDUALS = 100;
// const int MU = 75;
// const int LAMBDA = 6 * MU;
// const int k = 65;
// const float CROSSOVER_RATE = 0.65;
// const float MUTATION_RATE = 0.05;
auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 eng {seed};
int generation;

int main()
{
    GA ga1(75, 6 * 75, 65, 0.65, 0.05);

    ga1.run();
}
//     Individual *population[NUM_INDIVIDUALS];
//     Individual *matingPool[MU];
//     Individual *offsprings[LAMBDA];

//     #if PARAMETER_TUNING
//     for (int it = 0; it < 10; it++)
//     {
//     #endif

//         initializePopulation(population);
//         GaHelper::evaluatePopulation(population);

//         #if DEBUG
//         Individual* bestIndividualInit = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
//         std::cout << bestIndividualInit->fitness << '\n';
//         #endif

//         for (generation = 0; generation < 1000; generation++)
//         {
//             // Selecting parents for next generation
//             GaHelper::selectParents(matingPool, population);

//             // Creating offsprings off of the potential parents
//             GaHelper::createOffsprings(offsprings, matingPool);

//             // Evaluating their fitness level
//             GaHelper::evaluatePopulation(offsprings, LAMBDA);

//             // Freeing the population
//             freePopulation(population);

//             // Sorting the by fitness
//             std::sort(offsprings, offsprings+LAMBDA, GaHelper::compareIndividual);

//             // Replace the population with NUM_INDIVIDUAL's best offspring
//             GaHelper::survivorSelection(population, offsprings);

//             // Freeing the offspring that will no longer be used
//             freeOffsprings(offsprings);

//             #if DEBUG
//             Individual* bestIndividualInit = population[0];
//             std::cout << bestIndividualInit->fitness << '\n';
//             #endif
//         }

//         Individual* bestIndividual = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
//         std::cout << bestIndividual->fitness << ',' << std::flush;

//         #if !PARAMETER_TUNING
//         outputBestIndividual(bestIndividual);
//         #endif

// void freePopulation(Individual** population)
// {
//     for (int i = 0; i < NUM_INDIVIDUALS; i++)
//     {
//         delete population[i];
//     }
// }

// void freeOffsprings(Individual** offsprings)
// {
//     if (NUM_INDIVIDUALS < LAMBDA)
//     {
//         for (int i = NUM_INDIVIDUALS; i < LAMBDA; i++)
//         {
//             delete offsprings[i];
//         }
//     }
// }