#ifndef STL_ACTIONSPARAMETER
#define STL_ACTIONSPARAMETER

#include <cstdlib>
#include <cmath>
#include "actionClass.hpp"

#include "../MVC/modelPhotoshop.hpp"

/**************************************************************************/

class ActionColor : public Action
{
private:
    ModelPhotoshop& modelPhotoshop;
    Picture& pictureCurrent;
    int size = 30;

public:
    Object* button;
    ActionColor (ModelPhotoshop& init_modelPhotoshop, Picture& init_pictureCurrent)
        : modelPhotoshop(init_modelPhotoshop), pictureCurrent(init_pictureCurrent)
    { }

    virtual void call (sf::Event event) override
    {
        if (button == nullptr) return;

        sf::Vector2f corner = button->sprite.getPosition();       

        // sf::Vector2i position = sf::Mouse::getPosition();
        // int x = position.x - kWidthCanvasCorner;
        // int y = position.y - kHeightCanvasCorner;
        // sf::Color c = button->image.getPixel (x - corner.x, y - corner.y);

        sf::Color c = button->image.getPixel (event.mouseButton.x - corner.x, event.mouseButton.y - corner.y);
        Color color = Color (c.r, c.g, c.b, 255) / 255;

        printf ("\n%f %f\n", event.mouseButton.x - corner.x, event.mouseButton.y - corner.y);
        printf ("%d %d %d\n", c.r, c.g, c.b);
        pictureCurrent.clean ();
        for (int r_x = -size; r_x < size; r_x++)
        {
            for (int r_y = -size; r_y < size; r_y++)
            {
                if (r_x * r_x + r_y * r_y <= size * size)
                {
                    pictureCurrent.image.setPixel (75 + r_x, 75 + r_y, c);
                }
            }
        }
        pictureCurrent.update ();

        modelPhotoshop.setColor (color);
    }
};

class ActionSize : public Action
{
private:
    ModelPhotoshop& modelPhotoshop;
    Picture& pictureCurrent;

public:
    ActionSize (ModelPhotoshop& init_modelPhotoshop, Picture& init_pictureCurrent)
        : modelPhotoshop(init_modelPhotoshop), pictureCurrent(init_pictureCurrent)
    { }

    virtual void call (sf::Event event) override
    {
        sf::Vector2f corner = pictureCurrent.sprite.getPosition();
        VectorDec pos = {event.mouseButton.x - (int)corner.x, event.mouseButton.y - (int)corner.y};

        if (15 <= pos.x && pos.x <= 140 && 
            0  <= pos.y && pos.y <= 200)
        {
            int size = (int)(1.0 * (pos.x - 15) / 125 * (60 - 10) + 10);
            pictureCurrent.clean ();
            for (int r_x = 0; r_x < size; r_x++)
            {
                int r_y = sqrt (size * size - r_x * r_x);
                pictureCurrent.image.setPixel (75 + r_x, 75 + r_y, sf::Color::Black);
                pictureCurrent.image.setPixel (75 + r_x, 75 - r_y, sf::Color::Black);
                pictureCurrent.image.setPixel (75 - r_x, 75 + r_y, sf::Color::Black);
                pictureCurrent.image.setPixel (75 - r_x, 75 - r_y, sf::Color::Black);
                pictureCurrent.image.setPixel (75 + r_y, 75 + r_x, sf::Color::Black);
                pictureCurrent.image.setPixel (75 + r_y, 75 - r_x, sf::Color::Black);
                pictureCurrent.image.setPixel (75 - r_y, 75 + r_x, sf::Color::Black);
                pictureCurrent.image.setPixel (75 - r_y, 75 - r_x, sf::Color::Black);
            }
            pictureCurrent.update ();

            modelPhotoshop.setSize (size);
        }
    }
};

/**************************************************************************/

#endif /* STL_ACTIONSPARAMETER */