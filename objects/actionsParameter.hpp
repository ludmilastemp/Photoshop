#ifndef STL_ACTIONSPARAMETER
#define STL_ACTIONSPARAMETER

#include <cstdlib>
#include <cmath>
#include "actionClass.hpp"

#include "../MVC/modelCanvas.hpp"

/**************************************************************************/

class ActionParam : public Action
{
public:
    virtual void setPictureCurrent (Picture& picture) {}
};

class ActionColor : public ActionParam
{
private:
    ModelCanvas& modelCanvas;
    Picture* pictureCurrent;
    int size = 30;
    const int min_size = 1;
    const int max_size = 60;

public:
    ActionColor (ModelCanvas& init_modelPhotoshop)
        : modelCanvas(init_modelPhotoshop)
    { }

    void drawState (Color color)
    {
        for (int r_x = -size; r_x < size; r_x++)
        {
            for (int r_y = -size; r_y < size; r_y++)
            {
                if (r_x * r_x + r_y * r_y <= size * size)
                {
                    pictureCurrent->setPixel (75 + r_x, 75 + r_y, color);
                }
            }
        }
        pictureCurrent->update ();
    }

    virtual void setPictureCurrent (Picture& picture) override
    {
        pictureCurrent = &picture;
    }

    virtual void active () override
    {
        assert (pictureCurrent);
        Color color = modelCanvas.getColor ();
        drawState (color);
    }

    virtual void call (Event event) override
    {
        assert (pictureCurrent);
        VectorDecUint32 corner = pictureCurrent->getPosition();       
        Color color = pictureCurrent->getPixel (event.getCoord().x - corner.x, event.getCoord().y - corner.y);
        drawState (color);
        modelCanvas.setColor (color);
    }
};

class ActionSize : public ActionParam
{
private:
    ModelCanvas& modelCanvas;
    Picture* pictureCurrent;

public:
    ActionSize (ModelCanvas& init_modelPhotoshop)
        : modelCanvas(init_modelPhotoshop)
    { }

    void drawState (int size)
    {
        pictureCurrent->clean ();
        for (int r_x = 0; r_x < size; r_x++)
        {
            int r_y = sqrt (size * size - r_x * r_x);
            pictureCurrent->setPixel (75 + r_x, 75 + r_y, {0, 0, 0, 1});
            pictureCurrent->setPixel (75 + r_x, 75 - r_y, {0, 0, 0, 1});
            pictureCurrent->setPixel (75 - r_x, 75 + r_y, {0, 0, 0, 1});
            pictureCurrent->setPixel (75 - r_x, 75 - r_y, {0, 0, 0, 1});
            pictureCurrent->setPixel (75 + r_y, 75 + r_x, {0, 0, 0, 1});
            pictureCurrent->setPixel (75 + r_y, 75 - r_x, {0, 0, 0, 1});
            pictureCurrent->setPixel (75 - r_y, 75 + r_x, {0, 0, 0, 1});
            pictureCurrent->setPixel (75 - r_y, 75 - r_x, {0, 0, 0, 1});
        }
        pictureCurrent->update ();
    }

    virtual void setPictureCurrent (Picture& picture) override
    {
        pictureCurrent = &picture;
    }

    virtual void active () override
    {
        int size = modelCanvas.getSize ();
        drawState (size);
    }

    virtual void call (Event event) override
    {
        VectorDecUint32 corner = pictureCurrent->getPosition();
        VectorDec pos = {event.getCoord().x - (int)corner.x, event.getCoord().y - (int)corner.y};

        if (15 <= pos.x && pos.x <= 140 && 
            0  <= pos.y && pos.y <= 200)
        {
            int size = (int)(1.0 * (pos.x - 15) / 125 * (60 - 1) + 1);
            drawState (size);
            modelCanvas.setSize (size);
        }
    }
};

class ActionScale : public ActionParam
{
private:
    ModelCanvas& modelCanvas;
    Picture* pictureCurrent;

public:
    ActionScale (ModelCanvas& init_modelPhotoshop)
        : modelCanvas(init_modelPhotoshop)
    { }

    void drawState (int size)
    {
        // pictureCurrent->clean ();
        // for (int r_x = 0; r_x < size; r_x++)
        // {
        //     int r_y = sqrt (size * size - r_x * r_x);
        //     pictureCurrent->setPixel (75 + r_x, 75 + r_y, {0, 0, 0, 1});
        //     pictureCurrent->setPixel (75 + r_x, 75 - r_y, {0, 0, 0, 1});
        //     pictureCurrent->setPixel (75 - r_x, 75 + r_y, {0, 0, 0, 1});
        //     pictureCurrent->setPixel (75 - r_x, 75 - r_y, {0, 0, 0, 1});
        //     pictureCurrent->setPixel (75 + r_y, 75 + r_x, {0, 0, 0, 1});
        //     pictureCurrent->setPixel (75 + r_y, 75 - r_x, {0, 0, 0, 1});
        //     pictureCurrent->setPixel (75 - r_y, 75 + r_x, {0, 0, 0, 1});
        //     pictureCurrent->setPixel (75 - r_y, 75 - r_x, {0, 0, 0, 1});
        // }
        // pictureCurrent->update ();
    }

    virtual void setPictureCurrent (Picture& picture) override
    {
        pictureCurrent = &picture;
    }

    virtual void active () override
    {
        // int size = modelCanvas.getSize ();
        // drawState (size);
    }

    virtual void call (Event event) override
    {
        // VectorDecUint32 corner = pictureCurrent->getPosition();
        // VectorDec pos = {event.getCoord().x - (int)corner.x, event.getCoord().y - (int)corner.y};

        // if (15 <= pos.x && pos.x <= 140 && 
        //     0  <= pos.y && pos.y <= 200)
        // {
        //     int size = (int)(1.0 * (pos.x - 15) / 125 * (60 - 1) + 1);
        //     drawState (size);
        //     modelCanvas.setSize (size);
        // }
    }
};

/**************************************************************************/

#endif /* STL_ACTIONSPARAMETER */