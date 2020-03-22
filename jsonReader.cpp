#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.
#include<jsoncpp/json/writer.h>
#include<string>

#include "individual.hpp"
#include "tile.hpp"

using namespace std;

Individual* createBaseIndividual(int numTiles, const Json::Value &obj);

int main() {
    ifstream ifs("population.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings

    unsigned int numTiles = obj["0"]["pieces"].asInt();

    Individual *baseIndividual = createBaseIndividual(numTiles, obj);

    const int NUM_INDIVIDUALS = 100;

    Individual *pop[NUM_INDIVIDUALS];

    pop[0] = baseIndividual;

    for (int i = 1; i < NUM_INDIVIDUALS; i++)
    {
        Tile *tilesTest = new Tile[numTiles];

        for (int j = 0; j < numTiles; j++)
        {
            unsigned int x = obj[to_string(j)]["puzzle"][j][0].asInt();
            unsigned int y = obj[to_string(j)]["puzzle"][j][1].asInt();
            unsigned int l = obj[to_string(j)]["puzzle"][j][2].asInt();
            unsigned int w = obj[to_string(j)]["puzzle"][j][3].asInt();

            tilesTest[j].x = x;
            tilesTest[j].y = y;
            tilesTest[j].l = l;
            tilesTest[j].w = w;
        }

        pop[i] = new Individual(tilesTest, numTiles, baseIndividual);
    }

    for (int i = 0; i < NUM_INDIVIDUALS; i++)
    {
        delete pop[i];
    }

    return 0;
}

Individual* createBaseIndividual(int numTiles, const Json::Value &obj)
{
    Tile *tiles = new Tile[numTiles];

    for (int i = 0; i < numTiles; i++)
    {
        unsigned int x = obj["0"]["puzzle"][i][0].asInt();
        unsigned int y = obj["0"]["puzzle"][i][1].asInt();
        unsigned int l = obj["0"]["puzzle"][i][2].asInt();
        unsigned int w = obj["0"]["puzzle"][i][3].asInt();

        tiles[i].x = x;
        tiles[i].y = y;
        tiles[i].l = l;
        tiles[i].w = w;
    }

    return new Individual(tiles, numTiles);
}