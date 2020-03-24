#pragma once

#include "GA/individual.hpp"

extern const int NUM_INDIVIDUALS;

void replacePopulation(Individual** population, Individual** offsprings, const int LAMBDA);