#include "picture.hpp"

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

void Picture::setPixel (const VectorDec& coord, Color color)
{
    if (0 <= coord.x && coord.x < image.getSize().x && 
        0 <= coord.y && coord.y < image.getSize().y)
    {
        image.setPixel (coord.x, coord.y, 
            sf::Color (color.r * 255, color.g * 255, color.b * 255, color.a * 255));
    }
}

void Picture::overlay (const Picture& from)
{
    for (int x = 0; x < image.getSize().x; x++)
    {
        for (int y = 0; y < image.getSize().y; y++)
        {
            color_t a = from.image.getPixel(x, y).a / 255.0;
            if (a == 0) continue;

            image.setPixel (x, y, sf::Color (
                image.getPixel(x, y).r * (1 - a) + from.image.getPixel(x, y).r * a, 
                image.getPixel(x, y).g * (1 - a) + from.image.getPixel(x, y).g * a, 
                image.getPixel(x, y).b * (1 - a) + from.image.getPixel(x, y).b * a));
        }
    }
    
    update();
}

void Picture::update ()
{
    texture.update (image);
}

void Picture::clean ()
{
    for (int x = 0; x < image.getSize().x; x++)
    {
        for (int y = 0; y < image.getSize().y; y++)
        {
            image.setPixel (x, y, sf::Color (0, 0, 0, 0));
        }
    }
    update ();
}

/**************************************************************************/


/**************************************************************************/
