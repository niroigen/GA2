#pragma once

#include <vector>
#include "GA/individual.hpp"

typedef std::vector<std::vector<std::vector<Tile*>>> TileMatrix;

void defaultFitnessFunction(Individual*);
// void calculateOverlap(const Tile&, int*, std::vector<Tile*>*, const int, const int);