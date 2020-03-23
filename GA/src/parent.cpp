#include "GA/parent.hpp"

void tournamentSelection(Individual **matingPool, Individual **population, 
                         Individual* (*funcBestIndividual)(Individual**, int),
                         void (*funcPickRandomIndividuals)(Individual**, Individual**))
{
    unsigned int currentMember = 0;

    while(currentMember < MU)
    {
        Individual *randomIndividuals[k];

        (*funcPickRandomIndividuals)(randomIndividuals, population);

        Individual* bestIndividual = (*funcBestIndividual)(randomIndividuals, k);

        #if DEBUG
        std::cout << bestIndividual->fitness << '\n';
        #endif

        matingPool[currentMember] = bestIndividual;
        currentMember++;
    }
}