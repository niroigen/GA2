#pragma once

#include <random>
#include "GA/individual.hpp"

extern std::mt19937 eng;

void uniformCrossover(Individual *offspring1, Individual *offspring2,
                      std::uniform_int_distribution<>& distr);
void twoPointCrossover(Individual *offspring1, Individual *offspring2,
                      std::uniform_int_distribution<>& distr);