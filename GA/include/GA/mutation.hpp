#pragma once

#include <random>
#include "GA/individual.hpp"

extern const float MUTATION_RATE;
extern std::mt19937 eng;

void randomResetting(Individual *offspring);