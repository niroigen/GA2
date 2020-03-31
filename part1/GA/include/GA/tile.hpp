#pragma once

#include <iostream>

struct Tile
{
    unsigned int x, y, l, w;
    float fitness;
    Tile(unsigned int x, unsigned int y, unsigned int l,
         unsigned int w) :
         x(x), y(y), l(l), w(w) {}
    Tile() {}
    Tile(const Tile& tile)
    {
        x = tile.x;
        y = tile.y;
        l = tile.l;
        w = tile.w;
        fitness = tile.fitness;

        #if DEBUG
        std::cout << "Tile Copy Constructor"<< std::endl;
        #endif
    }

    Tile& operator=(const Tile& tile)
    {
        if (this != &tile)
        {
            x = tile.x;
            y = tile.y;
            l = tile.l;
            w = tile.w;
            fitness = tile.fitness;
        }

        #if DEBUG
        std::cout << "Tile Copy Assignment Operator"<< std::endl;
        #endif

        return *this;
    }
    ~Tile() 
    {
        #if DEBUG
        std::cout << "class Tile destroyed\n";
        #endif
    }
    friend bool operator==(const Tile& l, const Tile& r)
    {
        return ((l.l == r.l) && (l.w == r.w)) ||
               ((l.l == r.w) && (l.w == r.l));
    }
};