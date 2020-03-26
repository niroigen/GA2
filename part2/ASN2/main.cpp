#include <chrono>
#include "GA/ga.hpp"

#define DEBUG 1
#define PARAMETER_TUNING 0

const int NUM_INDIVIDUALS = 5;
auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 eng {seed};
int generation;

int main()
{
    GA ga1(3, 6 * 3, 3, 0.65, 0.05);

    ga1.run();
}