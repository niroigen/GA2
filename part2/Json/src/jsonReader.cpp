#include "Json/jsonReader.hpp"

void initializePopulation(Individual** population) {
    ifstream ifs("automata-population.json");

    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings

    uint8_t initialState = stoi(obj[0]["Initial State"].asString(), nullptr, 2);
    uint8_t goalState = stoi(obj[1]["Goal State"].asString(), nullptr, 2);

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