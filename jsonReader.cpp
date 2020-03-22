#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.
#include<jsoncpp/json/writer.h>
#include<string>

#include "individual.hpp"
#include "tile.hpp"

using namespace std;

const int NUM_INDIVIDUALS = 100;

Individual* createBaseIndividual(int numTiles, const Json::Value &obj);

void initializePopulation(Individual **population) {
    ifstream ifs("population.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings

    unsigned int numTiles = obj["0"]["pieces"].asInt();

    Individual *baseIndividual = createBaseIndividual(numTiles, obj);

    population[0] = baseIndividual;

    for (int i = 1; i < NUM_INDIVIDUALS; i++)
    {
        Tile *tilesTest = new Tile[numTiles];

        for (int j = 0; j < numTiles; j++)
        {
            tilesTest[j].x = obj[to_string(j)]["puzzle"][j][0].asInt();
            tilesTest[j].y = obj[to_string(j)]["puzzle"][j][1].asInt();
            tilesTest[j].l = obj[to_string(j)]["puzzle"][j][2].asInt();
            tilesTest[j].w = obj[to_string(j)]["puzzle"][j][3].asInt();
        }

        population[i] = new Individual(tilesTest, numTiles, baseIndividual);
    }
}

int main()
{
    Individual *population[NUM_INDIVIDUALS];
    initializePopulation(population);

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete population[i];
    }
}

Individual* createBaseIndividual(int numTiles, const Json::Value &obj)
{
    Tile *tiles = new Tile[numTiles];

    for (int i = 0; i < numTiles; i++)
    {
        tiles[i].x = obj["0"]["puzzle"][i][0].asInt();
        tiles[i].y = obj["0"]["puzzle"][i][1].asInt();
        tiles[i].l = obj["0"]["puzzle"][i][2].asInt();
        tiles[i].w = obj["0"]["puzzle"][i][3].asInt();
    }

    return new Individual(tiles, numTiles);
}