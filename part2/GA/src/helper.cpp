#include "GA/helper.hpp"

#define DEBUG_MODE 0

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#else
#define DEBUG(x)
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
        #if DEBUG
        std::cout << distr(eng) << '\n';
        #endif

        int randIdx = distr(eng);

        randomIndividuals[i] = population[randIdx];

        #if DEBUG
        std::cout << randomIndividuals[i]->fitness << ' ' << population[randIdx]->fitness << '\n';
        #endif
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
    DEBUG("Getting random parent")

    std::uniform_int_distribution<> distr(0, MU - 1);

    Individual* test = matingPool[distr(eng)];
    DEBUG(test->size);

    return matingPool[distr(eng)];
}

bool GaHelper::compareIndividual(const Individual* i1, const Individual* i2)
{
    return i1->fitness < i2->fitness;
}

void GaHelper::createOffsprings(Individual** offsprings, Individual** matingPool)
{
    DEBUG("Starting the creation of offsprings")
    int i = 0;

    DEBUG("Initializing the randomness")

    std::uniform_real_distribution<> dist(0, 1);
    
    DEBUG("Mating pool")
    std::uniform_int_distribution<> distr(0, 31);

    while(i < LAMBDA)
    {
        DEBUG("Getting random parents");

        Individual* parent1 = GaHelper::getRandomParent(matingPool);
        Individual* parent2 = GaHelper::getRandomParent(matingPool);

        DEBUG(matingPool[0]->size)
        DEBUG(parent1->size)

        DEBUG("Got random parents");

        float r = dist(eng);

        DEBUG("Creating offsprings from parent");

        DEBUG(parent1)

        DEBUG(parent1->size)
        DEBUG(parent2->size)

        Individual* offspring1 = new Individual(*parent1);

        DEBUG("Created first offspring");

        Individual* offspring2 = new Individual(*parent2);

        DEBUG("Created offsprings from parent");

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
    uniformCrossover(offspring1, offspring2, distr);
}

void GaHelper::performMutation(Individual *offspring)
{
    randomResetting(offspring, MUTATION_RATE);
}

// void performRule(std::vector<std::uint8_t> currentState, std::uint8_t* rules)
// {
//     std::uint8_t rule = rules[]    
// }

std::string GaHelper::getWindow(int startIdx, std::vector<std::string> currentState)
{
    std::string res = "00000";

    for (int i = 0; i < 5; i++)
    {
        DEBUG(typeid(res[i]).name());
        DEBUG(typeid(currentState[startIdx % 5]).name());
        // res[i] = currentState[startIdx % 5];
        startIdx++;
    }

    return res;
}

void GaHelper::attemptRules(Individual** population)
{
    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        Individual* currentIndividual = population[i];
        std::vector<std::string> currentState = currentIndividual->initialState;
        auto nextState = currentIndividual->currentState;

        for (int startIdx = 0; i < currentState.size(); startIdx++)
        {
            auto window = GaHelper::getWindow(startIdx, currentState);
            const int rule = std::stoi(window, nullptr, 2);
            int rule_to_perform = currentIndividual->rules[rule];
            int middleIdx = (startIdx + 2) % currentState.size();
            switch(rule_to_perform)
            {
                case 0:
                nextState[middleIdx] = "0";
                break;
                case 1:
                break;
                case 2:
                break;
                case 3:
                break;
                default:
                break;
            }
        }
    }
}
