#pragma once

#include "GA/individual.hpp"

extern const int MU;
extern const int k;

void tournamentSelection(Individual **matingPool, Individual **population, 
                         Individual* (*funcBestIndividual)(Individual**, int),
                         void (*funcPickRandomIndividuals)(Individual**, Individual**));