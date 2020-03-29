#include "GA/ga.hpp"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
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

        helper->attemptRules(population);

        DEBUG("Initialized population")
        helper->evaluatePopulation(population);

        #if DEBUG_MODE
        Individual* bestIndividualInit = GaHelper::findBestIndividual(population, NUM_INDIVIDUALS);
        DEBUG("BEST INDIVIDUAL");
        DEBUG(bestIndividualInit->fitness);
        #endif

        for (generation = 0; generation < 1000; generation++)
        {
            // Selecting parents for next generation
            helper->selectParents(matingPool, population);
            // Creating offsprings off of the potential parents

            helper->createOffsprings(offsprings, matingPool);

            helper->attemptRules(offsprings);

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

            // DEBUG("Attempting rules");
            // DEBUG(population);
            // DEBUG(helper);
            // helper->attemptRules(population);


            #if DEBUG_MODE
            Individual* bestIndividualInit = population[0];
            DEBUG(bestIndividualInit->fitness);

            if(bestIndividualInit->fitness == 0) break;

            std::string ans;

            for (int i = 0; i < bestIndividualInit->currentState.size(); i++)
            {
                ans += bestIndividualInit->currentState[i];
            }
            DEBUG(ans)
            #endif
        }

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
