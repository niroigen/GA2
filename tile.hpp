#ifndef __TILE_H__
#define __TILE_H__

struct Tile
{
    unsigned int x, y, l, w, id;
    Tile(unsigned int x, unsigned int y, unsigned int l,
         unsigned int w, unsigned int id) :
         x(x), y(y), l(l), w(w), id(id) {}
    Tile() {}
};

#endif