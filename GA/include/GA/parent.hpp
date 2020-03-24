#pragma once

#include "GA/individual.hpp"

void tournamentSelection(Individual** matingPool, Individual** population, const int k, const int MU,
                         Individual* (*funcBestIndividual)(Individual**, int),
                         void (*funcPickRandomIndividuals)(Individual**, Individual**, int));