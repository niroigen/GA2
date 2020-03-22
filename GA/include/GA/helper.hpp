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
    static void createOffsprings(Individual **offsprings, Individual **matingPool);
    static Individual* getRandomParent(Individual **matingPool);
    static Individual* findBestIndividual(Individual **individuals, int numIndividuals);
};