#include "Json/jsonReader.hpp"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#else
#define DEBUG(x)
#endif

void initializePopulation(Individual** population) {
    ifstream ifs("automata-population.json");

    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings

    DEBUG("HELLO");

    std::string initialStateStr = obj[0]["Initial State"].asString();
    std::string goalStateStr = obj[1]["Goal State"].asString();

    DEBUG("BELLO");

    std::vector<std::string> initialState(8, "0");
    std::vector<std::string> goalState(8, "0");

    DEBUG("Starting to get all values");

    for (int i = 0; i < 8; i++)
    {
        initialState[i] = initialStateStr[i];
        goalState[i] = goalStateStr[i];
    }

    DEBUG("Got all values");

    unsigned int rules[32];

    for (int i = 0; i <  NUM_INDIVIDUALS; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            int rule;
            for (auto const& id : obj[i+2][j].getMemberNames())
            {
                rule = obj[i+2][j][id].asInt();
            }

            rules[j] = rule;
        }

        Individual* originalIndividual = new Individual(rules, initialState, goalState);

        population[i] = originalIndividual;
    }
}