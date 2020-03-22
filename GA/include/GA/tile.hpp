#ifndef __TILE_H__
#define __TILE_H__

#include <iostream>

struct Tile
{
    unsigned int x, y, l, w;
    Tile(unsigned int x, unsigned int y, unsigned int l,
         unsigned int w) :
         x(x), y(y), l(l), w(w) {}
    Tile() {}
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

#endif