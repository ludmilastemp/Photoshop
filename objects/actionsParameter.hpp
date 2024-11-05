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
    int min_size = 2;
    int max_size = 60;

public:
    ActionColor (ModelPhotoshop& init_modelPhotoshop, Picture& init_pictureCurrent)
        : modelPhotoshop(init_modelPhotoshop), pictureCurrent(init_pictureCurrent)
    { }

    virtual void active () override
    {
        Color color = modelPhotoshop.getColor ();
        for (int r_x = -size; r_x < size; r_x++)
        {
            for (int r_y = -size; r_y < size; r_y++)
            {
                if (r_x * r_x + r_y * r_y <= size * size)
                {
                    pictureCurrent.setPixel (75 + r_x, 75 + r_y, color);
                }
            }
        }
        pictureCurrent.update ();
    }

    virtual void call (Event event) override
    {
        VectorDecUint32 corner = pictureCurrent.getPosition();       
        Color color = pictureCurrent.getPixel (event.getCoord().x - corner.x, event.getCoord().y - corner.y);

        for (int r_x = -size; r_x < size; r_x++)
        {
            for (int r_y = -size; r_y < size; r_y++)
            {
                if (r_x * r_x + r_y * r_y <= size * size)
                {
                    pictureCurrent.setPixel (75 + r_x, 75 + r_y, color);
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

    virtual void active () override
    {
        int size = modelPhotoshop.getSize ();
        pictureCurrent.clean ();
        for (int r_x = 0; r_x < size; r_x++)
        {
            int r_y = sqrt (size * size - r_x * r_x);
            pictureCurrent.setPixel (75 + r_x, 75 + r_y, {0, 0, 0, 1});
            pictureCurrent.setPixel (75 + r_x, 75 - r_y, {0, 0, 0, 1});
            pictureCurrent.setPixel (75 - r_x, 75 + r_y, {0, 0, 0, 1});
            pictureCurrent.setPixel (75 - r_x, 75 - r_y, {0, 0, 0, 1});
            pictureCurrent.setPixel (75 + r_y, 75 + r_x, {0, 0, 0, 1});
            pictureCurrent.setPixel (75 + r_y, 75 - r_x, {0, 0, 0, 1});
            pictureCurrent.setPixel (75 - r_y, 75 + r_x, {0, 0, 0, 1});
            pictureCurrent.setPixel (75 - r_y, 75 - r_x, {0, 0, 0, 1});
        }
        pictureCurrent.update ();
    }

    virtual void call (Event event) override
    {
        VectorDecUint32 corner = pictureCurrent.getPosition();
        VectorDec pos = {event.getCoord().x - (int)corner.x, event.getCoord().y - (int)corner.y};

        if (15 <= pos.x && pos.x <= 140 && 
            0  <= pos.y && pos.y <= 200)
        {
            int size = (int)(1.0 * (pos.x - 15) / 125 * (60 - 1) + 1);
            pictureCurrent.clean ();
            for (int r_x = 0; r_x < size; r_x++)
            {
                int r_y = sqrt (size * size - r_x * r_x);
                pictureCurrent.setPixel (75 + r_x, 75 + r_y, {0, 0, 0, 1});
                pictureCurrent.setPixel (75 + r_x, 75 - r_y, {0, 0, 0, 1});
                pictureCurrent.setPixel (75 - r_x, 75 + r_y, {0, 0, 0, 1});
                pictureCurrent.setPixel (75 - r_x, 75 - r_y, {0, 0, 0, 1});
                pictureCurrent.setPixel (75 + r_y, 75 + r_x, {0, 0, 0, 1});
                pictureCurrent.setPixel (75 + r_y, 75 - r_x, {0, 0, 0, 1});
                pictureCurrent.setPixel (75 - r_y, 75 + r_x, {0, 0, 0, 1});
                pictureCurrent.setPixel (75 - r_y, 75 - r_x, {0, 0, 0, 1});
            }
            pictureCurrent.update ();

            modelPhotoshop.setSize (size);
        }
    }
};

/**************************************************************************/

#endif /* STL_ACTIONSPARAMETER */