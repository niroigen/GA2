#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.
#include<jsoncpp/json/writer.h>
#include<string>

#include "individual.hpp"
#include "tile.hpp"

using namespace std;

int main() {
    ifstream ifs("population.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings
    //cout << "0" << obj["0"]["puzzle"] << endl;
    Json::FastWriter fastWriter;

    std::string output;
    for (int i = 0; i < 4; i++){
        output = fastWriter.write(obj[to_string(i)]["puzzle"]);
        cout << to_string(i) << output;
        cout << endl;
    }

    Json::Value population;
    population["0"]["puzzle"] = obj["0"]["puzzle"];
    population["0"]["length"] = obj["0"]["length"];
    population["0"]["width"] = obj["0"]["width"];
    population["0"]["pieces"] = obj["0"]["pieces"];
    
    std::ofstream file_id;
    file_id.open("outJsonfromcpp.json");
    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(population);
    file_id.close();

    unsigned int numTiles = population["0"]["pieces"].asInt();

    Tile *tiles = new Tile[numTiles];

    for (int i = 0; i < numTiles; i++)
    {
        unsigned int x = population["0"]["puzzle"][i][0].asInt();
        unsigned int y = population["0"]["puzzle"][i][1].asInt();
        unsigned int l = population["0"]["puzzle"][i][2].asInt();
        unsigned int w = population["0"]["puzzle"][i][3].asInt();

        unsigned int id = i;

        Tile tile(x,y,l,w,id);

        tiles[i] = tile;
    }

    Individual individual(tiles, numTiles);

    for (int i = 0; i < individual.size; i++)
    {
        printf("%d,%d,%d,%d,%d\n",
        individual.tiles[i].x,
        individual.tiles[i].y,
        individual.tiles[i].l,
        individual.tiles[i].w,
        individual.tiles[i].id);
    }
}