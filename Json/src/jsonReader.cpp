#include "Json/jsonReader.hpp"

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
            tilesTest[j].x = obj[to_string(i)]["puzzle"][j][0].asInt();
            tilesTest[j].y = obj[to_string(i)]["puzzle"][j][1].asInt();
            tilesTest[j].l = obj[to_string(i)]["puzzle"][j][2].asInt();
            tilesTest[j].w = obj[to_string(i)]["puzzle"][j][3].asInt();
        }

        int frameLength = obj[to_string(i)]["length"].asInt();
        int frameWidth = obj[to_string(i)]["width"].asInt();

        #if DEBUG
        cout << frameLength << " " << frameWidth;
        #endif

        population[i] = new Individual(tilesTest, numTiles, baseIndividual, frameLength, frameWidth);
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

    int frameLength = obj["0"]["length"].asInt();
    int frameWidth = obj["0"]["width"].asInt();

    return new Individual(tiles, numTiles, frameLength, frameWidth);
}