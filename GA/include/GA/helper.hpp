#pragma once

#include <iostream>
#include <random>
#include "GA/individual.hpp"

extern const int NUM_INDIVIDUALS;
extern const int LAMBDA;
const int k = 5;
const float CROSSOVER_RATE = 0.1;

extern std::mt19937 eng;

struct GaHelper
{
    static void evaluateFitness(Individual &individual);
    static void selectParents(Individual **matingPool, Individual **population);
    static void pickRandomIndividuals(Individual **randomIndividuals, Individual **population);
    static void createOffsprings(Individual **offsprings, Individual **matingPool);
    static Individual* getRandomParent(Individual **matingPool);
    static Individual* findBestIndividual(Individual **individuals, int numIndividuals);
    static void performCrossover(Individual *offspring1, Individual *offspring2, std::uniform_int_distribution<>& distr);
};