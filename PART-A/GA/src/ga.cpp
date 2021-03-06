#include "GA/ga.hpp"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#endif

GA::GA(const int MU, const int LAMBDA, const int k, const float CROSSOVER_RATE, const float MUTATION_RATE)
    : MU(MU), LAMBDA(LAMBDA), k(k), CROSSOVER_RATE(CROSSOVER_RATE), MUTATION_RATE(MUTATION_RATE)
{
    population = new Individual*[NUM_INDIVIDUALS];
    matingPool = new Individual*[MU];
    offsprings = new Individual*[LAMBDA];

    DEBUG("Starting to initialize instance of GA")
    helper = new GaHelper(MU, LAMBDA, k, CROSSOVER_RATE, MUTATION_RATE);

    DEBUG("Finished initializing instance of GA")
}

void GA::freePopulation(Individual** population)
{
    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}

void GA::freeOffsprings(Individual** offsprings)
{
    if (NUM_INDIVIDUALS < LAMBDA)
    {
        for (int i = NUM_INDIVIDUALS; i < LAMBDA; i++)
        {
            delete offsprings[i];
        }
    }
}

void GA::run()
{
    #if PARAMETER_TUNING
    for (int it = 0; it < 10; it++)
    {
    #endif
        DEBUG("Starting to initialize population")
        initializePopulation(population);
        DEBUG("Initialized population")
        helper->evaluatePopulation(population);

        #if DEBUG_MODE
        Individual* bestIndividualInit = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
        DEBUG(bestIndividualInit->fitness);
        #endif

        do
        {
            // Selecting parents for next generation
            helper->selectParents(matingPool, population);

            // Creating offsprings off of the potential parents
            helper->createOffsprings(offsprings, matingPool);

            // Evaluating their fitness level
            helper->evaluatePopulation(offsprings, LAMBDA);

            // Freeing the population
            freePopulation(population);

            // Sorting the by fitness
            std::sort(offsprings, offsprings+LAMBDA, GaHelper::compareIndividual);

            // Replace the population with NUM_INDIVIDUAL's best offspring
            helper->survivorSelection(population, offsprings);

            // Freeing the offspring that will no longer be used
            freeOffsprings(offsprings);

            if (population[0]->fitness < 0.005) break;

            Individual* bestIndividualInit = population[0];
            if (bestIndividualInit->fitness < bestFitness) 
            {
                bestFitness = bestIndividualInit->fitness;
                stagnantCounter = 0;
            }
            else
            {
                stagnantCounter++;
            }

            DEBUG(bestIndividualInit->fitness);
        } while(!isComplete());

        Individual* bestIndividual = helper->findBestIndividual(population, NUM_INDIVIDUALS);
        std::cout << bestIndividual->fitness << ',' << std::flush;

        #if !PARAMETER_TUNING
        outputBestIndividual(bestIndividual);
        #endif

        freePopulation(population);

    #if PARAMETER_TUNING
    }
    #endif
}
