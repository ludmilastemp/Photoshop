#include "picture.hpp"

#include <cassert>

/**************************************************************************/

Picture::Picture (const VectorDec& init_size, const VectorDec& init_corner)
    : Object(init_size, init_corner), 
    size(init_size)
{}

Picture::Picture (const VectorDec& init_size, const VectorDec& init_corner, const char* png)
    : Object(init_size, init_corner, png), 
    size(init_size)
{}

/**************************************************************************/

void Picture::overlay (const Picture& from)
{
    for (int x = 0; x < getSize().x; x++)
    {
        for (int y = 0; y < getSize().y; y++)
        {
            color_t a = from.getPixel(x, y).a;
            if (a == 0) continue;

            setPixel (x, y, {
                getPixel(x, y).r * (1 - a) + from.getPixel(x, y).r * a, 
                getPixel(x, y).g * (1 - a) + from.getPixel(x, y).g * a, 
                getPixel(x, y).b * (1 - a) + from.getPixel(x, y).b * a, 1});
        }
    }
    update();
}

void Picture::clean ()
{
    for (int x = 0; x < getSize().x; x++)
    {
        for (int y = 0; y < getSize().y; y++)
        {
            setPixel (x, y, {0, 0, 0, 0});
        }
    }
    update ();
}

/**************************************************************************/


/**************************************************************************/
