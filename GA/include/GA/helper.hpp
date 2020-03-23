#pragma once

#include <iostream>
#include <random>
#include <algorithm>
#include "GA/individual.hpp"
#include "GA/crossover.hpp"
#include "GA/mutation.hpp"
#include "GA/fitness.hpp"
#include "GA/parent.hpp"
#include "GA/survivor.hpp"

extern const int NUM_INDIVIDUALS;
extern const int LAMBDA;
extern const int MU;
extern const int k;
extern const float CROSSOVER_RATE;
extern const float MUTATION_RATE;

extern std::mt19937 eng;

struct GaHelper
{
    static void evaluateFitness(Individual &individual);
    static void evaluatePopulation(Individual **population, int size = NUM_INDIVIDUALS);
    static void selectParents(Individual **matingPool, Individual **population);
    static void pickRandomIndividuals(Individual **randomIndividuals, Individual **population);
    static void createOffsprings(Individual **offsprings, Individual **matingPool);
    static void survivorSelection(Individual **population, Individual **offsprings);
    static Individual* getRandomParent(Individual **matingPool);
    static Individual* findBestIndividual(Individual **individuals, int numIndividuals);
    static void performCrossover(Individual *offspring1, Individual *offspring2, std::uniform_int_distribution<>& distr);
    static void performMutation(Individual *offspring);
    static bool compareIndividual(const Individual* i1, const Individual* i2);
};