#pragma once

#include <iostream>
#include <vector>
#include <string>

struct Individual
{
    unsigned int rules[32];
    // TODO: change this to current state
    std::vector<std::string> initialState;

    // TODO: change this to next state
    std::vector<std::string> goalState;
    std::vector<std::string> currentState;
    float fitness = 0;

    Individual() {}
    Individual(unsigned int*, std::vector<std::string>, std::vector<std::string>);

    // Individual(Tile*, unsigned int,
    //            unsigned int, unsigned int);
    // Individual(Tile*, unsigned int, const Individual*, unsigned int, unsigned int);
    Individual(const Individual&);
    // Individual& operator=(const Individual&);
    // ~Individual();


    // bool isIdxListed(int);
    // bool areTilesEqual(const Tile&, const Tile&, const int);
    // int findExistingTile(const Tile&);
};