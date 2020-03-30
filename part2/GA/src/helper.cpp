#include "GA/helper.hpp"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#define WAIT
#endif

void GaHelper::evaluatePopulation(Individual** population, int size)
{
    for (int i = 0; i < size; i++)
    {
        evaluateFitness(population[i]);
    }
}

void GaHelper::evaluateFitness(Individual* individual)
{
    defaultFitnessFunction(individual);
}

void GaHelper::survivorSelection(Individual** population, Individual** offsprings)
{
    replacePopulation(population, offsprings, LAMBDA);
}

void GaHelper::pickRandomIndividuals(Individual** randomIndividuals, Individual** population, int k)
{
    std::uniform_int_distribution<> distr(0, NUM_INDIVIDUALS - 1);

    for (int i = 0; i < k; i++)
    {
        int randIdx = distr(eng);

        randomIndividuals[i] = population[randIdx];
    }
}

Individual* GaHelper::findBestIndividual(Individual** individuals, int numIndividuals)
{
    unsigned int bestIdx = 0;
    float bestFitness = individuals[0]->fitness;
    for (int i = 1; i < numIndividuals; i++)
    {
        if(individuals[i]->fitness < bestFitness)
        {
            bestIdx = i;
            bestFitness = individuals[i]->fitness;
        }
    }

    return individuals[bestIdx];
}

void GaHelper::selectParents(Individual** matingPool, Individual** population)
{
    tournamentSelection(matingPool, population, k, MU, findBestIndividual, pickRandomIndividuals);
}

Individual* GaHelper::getRandomParent(Individual** matingPool)
{
    std::uniform_int_distribution<> distr(0, MU - 1);

    Individual* test = matingPool[distr(eng)];

    return matingPool[distr(eng)];
}

bool GaHelper::compareIndividual(const Individual* i1, const Individual* i2)
{
    return i1->fitness < i2->fitness;
}

void GaHelper::createOffsprings(Individual** offsprings, Individual** matingPool)
{
    int i = 0;

    std::uniform_real_distribution<> dist(0, 1);
    
    std::uniform_int_distribution<> distr(0, 31);

    while(i < LAMBDA)
    {
        Individual* parent1 = GaHelper::getRandomParent(matingPool);
        Individual* parent2 = GaHelper::getRandomParent(matingPool);

        float r = dist(eng);

        Individual* offspring1 = new Individual(*parent1);
        Individual* offspring2 = new Individual(*parent2);

        if (r <= CROSSOVER_RATE)
        {
            GaHelper::performCrossover(offspring1, offspring2, distr);
        }

        GaHelper::performMutation(offspring1);
        GaHelper::performMutation(offspring2);

        offsprings[i++] = offspring1;
        offsprings[i++] = offspring2;
    }
}

void GaHelper::performCrossover(Individual *offspring1, Individual *offspring2,
                                std::uniform_int_distribution<>& distr)
{
    twoPointCrossover(offspring1, offspring2, distr);
}

void GaHelper::performMutation(Individual *offspring)
{
    randomResetting(offspring, MUTATION_RATE);
}

std::string GaHelper::getWindow(int startIdx, std::vector<std::string> currentState)
{
    std::string res = "00000";

    // DEBUG(startIdx)

    for (int i = 0; i < 5; i++)
    {
        res[i] = currentState[(startIdx + i) % currentState.size()][0];
    }

//         DEBUG("inSIDE")
//     std::string ans;

//     for (int i = 0; i < currentState.size(); i++)
//     {
//         ans += currentState[i];
//     }

//     DEBUG(ans)

// WAIT;

    return res;
}

bool isGoalStateEqualToCurrentState(std::vector<std::string> currentState,std::vector<std::string> goalState)
{
    if (currentState.size() != goalState.size()) return false;
    else
    {
        for (int i = 0; i < currentState.size(); i++)
        {
            if (currentState[i] != goalState[i]) return false;
        }

        return true;
    }
}

void GaHelper::attemptRules(Individual** population)
{
    bool solutionFound = false;
    for (int i = 0; i < NUM_INDIVIDUALS && !solutionFound; i++)
    {
        Individual* currentIndividual = population[i];

        for (int test = 0; test < 30 && !solutionFound; test++)
        {
            std::vector<std::string> currentState = currentIndividual->initialState;
            std::vector<std::string> nextState = currentIndividual->currentState;

            int currStateIdx = 0;
            int middleIdx = 0;

            for (int startIdx = 0; startIdx < currentState.size() && !solutionFound; startIdx++)
            {
                auto window = GaHelper::getWindow(startIdx, currentState);

                const int rule = std::stoi(window, nullptr, 2);

                int rule_to_perform = currentIndividual->rules[rule];

                if (nextState.size() == 0) break;

                int middleIdx = (startIdx + 2) % currentState.size();

                if (middleIdx + currStateIdx >= 0 && middleIdx + currStateIdx < nextState.size())
                {
                    switch(rule_to_perform)
                    {
                        case 0:
                        nextState[middleIdx + currStateIdx] = "0";
                        break;
                        case 1:
                        nextState[middleIdx + currStateIdx] = "1";
                        break;
                        case 2:
                        nextState.erase(nextState.begin() + middleIdx + currStateIdx);
                        currStateIdx--;
                        break;
                        case 3:
                        std::string val = currentState[middleIdx];
                        nextState.insert(nextState.begin() + middleIdx + currStateIdx, val);
                        currStateIdx++;
                        break;
                    }

                    solutionFound = isGoalStateEqualToCurrentState(nextState, currentIndividual->goalState);
                }
            }

            currentIndividual->currentState = nextState;
        }
    }
}
