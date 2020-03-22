#pragma once

#include <iostream>
#include <random>
#include "GA/individual.hpp"

extern const int NUM_INDIVIDUALS;
extern const int LAMBDA;
const int k = 5;

struct GaHelper
{
    static void evaluateFitness(Individual &individual);
    static void selectParents(Individual **matingPool, Individual **population);
    static void pickRandomIndividuals(Individual **randomIndividuals, Individual **population);
};