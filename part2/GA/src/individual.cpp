#include "GA/individual.hpp"

#define DEBUG_MODE 0

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#else
#define DEBUG(x)
#endif

Individual::Individual(unsigned int* rules, std::vector<std::string> initialState, std::vector<std::string> goalState)
    : initialState(initialState), goalState(goalState), currentState(initialState)
{
    for (int i = 0; i < 32; i++)
    {
        this->rules[i] = rules[i];
    }
}