#pragma once

#include <vector>
#include "GA/individual.hpp"

typedef std::vector<std::vector<std::vector<Tile*>>> TileMatrix;
typedef std::vector<std::vector<int>> Matrix;

void defaultFitnessFunction(Individual*);
void calculateOverlap(Tile&, Matrix&, TileMatrix&, const int, const int);