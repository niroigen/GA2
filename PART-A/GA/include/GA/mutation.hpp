#pragma once

#include <random>
#include <vector>
#include <thread>
#include "GA/individual.hpp"

extern std::mt19937 eng;

void resetGene(Individual*, const int, const float);
void randomResetting(Individual*, const float);