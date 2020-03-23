#pragma once

#include "GA/individual.hpp"

extern const int NUM_INDIVIDUALS;
extern const int LAMBDA;

void replacePopulation(Individual **population, Individual **offsprings);