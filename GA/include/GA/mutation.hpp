#pragma once

#include <random>
#include "GA/individual.hpp"

extern std::mt19937 eng;

void randomResetting(Individual *offspring, const float MUTATION_RATE);