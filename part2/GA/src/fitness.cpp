#include "GA/fitness.hpp"

void defaultFitnessFunction(Individual* individual)
{
    int fitness_table[9][9] = {0};

    for (int row = 0; row < 9; row++)
    {
        fitness_table[row][0] = row;
    }

    for (int col = 0; col < 9; col++)
    {
        fitness_table[0][col] = col;
    }

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (row != 0 && col != 0)
            {
                int val1 = individual->initialState & (1 << (row - 1));
                int val2 = individual->goalState & (1 << (col - 1));
                if ((val1 > 0) == (val2 > 0))
                {
                    fitness_table[row][col] = fitness_table[row-1][col-1];
                }
                else
                {
                    fitness_table[row][col] = std::min({fitness_table[row-1][col] + 1, fitness_table[row][col-1] + 1, fitness_table[row-1][col-1] + 2});
                }
            }
        }
    }
    
    individual->fitness = fitness_table[8][8];
}