#pragma once

#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.
#include<jsoncpp/json/writer.h>
#include<string>

#include "individual.hpp"
#include "tile.hpp"

using namespace std;

extern const int NUM_INDIVIDUALS;

Individual* createBaseIndividual(int numTiles, const Json::Value &obj);
void initializePopulation(Individual **population);