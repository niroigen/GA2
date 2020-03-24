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
extern std::mt19937 eng;

struct GaHelper
{
    const int MU;
    const int LAMBDA;
    const int k;
    const float CROSSOVER_RATE;
    const float MUTATION_RATE;

    GaHelper(const int MU, const int LAMBDA, const int k, const float CROSSOVER_RATE, const float MUTATION_RATE)
         : MU(MU), LAMBDA(LAMBDA), k(k), CROSSOVER_RATE(CROSSOVER_RATE), MUTATION_RATE(MUTATION_RATE)
    {}

    void evaluateFitness(Individual* individual);
    void evaluatePopulation(Individual** population, int size = NUM_INDIVIDUALS);
    void selectParents(Individual** matingPool, Individual** population);
    static void pickRandomIndividuals(Individual** randomIndividuals, Individual** population, int k);
    void createOffsprings(Individual** offsprings, Individual** matingPool);
    void survivorSelection(Individual** population, Individual** offsprings);
    Individual* getRandomParent(Individual** matingPool);
    static Individual* findBestIndividual(Individual** individuals, int numIndividuals);
    void performCrossover(Individual* offspring1, Individual* offspring2, std::uniform_int_distribution<>& distr);
    void performMutation(Individual* offspring);
    static bool compareIndividual(const Individual* i1, const Individual* i2);
};