#ifndef STL_PARAMETER_SCALE
#define STL_PARAMETER_SCALE

#include <cstdlib>
#include <cmath>
#include "../objects/actionClass.hpp"

#include "../MVC/modelCanvas.hpp"

/**************************************************************************/

class ActionScrollVertically : public Action
{
private:
    ModelCanvas& modelCanvas;
    Picture* pictureCurrent;

public:
    ActionScrollVertically (ModelCanvas& init_modelPhotoshop)
        : modelCanvas(init_modelPhotoshop)
    { }

    void drawState (int pos, int length)
    {
        printf ("%d %d\n", pos, length);
        length -= 5;
        pictureCurrent->clean ();
        int centerY = pos - length;
        for (int r_x = -6; r_x < 6; r_x++)
        {
            for (int r_y = -5; r_y < 5; r_y++)
            {
                if (r_x * r_x + r_y * r_y <= 30)
                {
                    if (590 <= 594     + r_x && 594     + r_x <= 598 && 
                        10  <= centerY + r_y && centerY + r_y <= 390)
                        pictureCurrent->setPixel (594 + r_x, centerY + r_y, {0.45, 0.45, 0.45, 1});
                }
            }
        }
        centerY = pos + length;
        for (int r_x = -6; r_x < 6; r_x++)
        {
            for (int r_y = -5; r_y < 5; r_y++)
            {
                if (r_x * r_x + r_y * r_y <= 30)
                {
                    if (590 <= 594     + r_x && 594     + r_x <= 598 && 
                        10  <= centerY + r_y && centerY + r_y <= 390)
                        pictureCurrent->setPixel (594 + r_x, centerY + r_y, {0.45, 0.45, 0.45, 1});
                }
            }
        }
        centerY = pos;
        for (int r_x = -6; r_x < 6; r_x++)
        {
            for (int r_y = -length; r_y < length; r_y++)
            {
                if (590 <= 594     + r_x && 594     + r_x <= 598 && 
                    10  <= centerY + r_y && centerY + r_y <= 390)
                    pictureCurrent->setPixel (594 + r_x, centerY + r_y, {0.45, 0.45, 0.45, 1});
            }
        }
        pictureCurrent->update ();
    }

    virtual Scene* create(std::vector<void*>* buttons) override
    {
        VectorDec size  = {600, 400};

        pictureCurrent = new Picture {size, {kCanvasXEnd - size.x, kCanvasYBegin}};
        Button* button = new Button {{10, 380}, {kCanvasXEnd - 9, kCanvasYBegin + 10}, *this};
        buttons->push_back (button);

        Scene* sceneParameter = new Scene {};
        sceneParameter->addObject (*button);
        sceneParameter->addObject (*pictureCurrent);
        sceneParameter->setIsDraw (false);
        return sceneParameter;
    }

    virtual void call (Event event) override
    {        
        VectorDec pos = {event.getCoord().x, event.getCoord().y};

        if (590 <= pos.x && pos.x <= 600 && 
            10  <= pos.y && pos.y <= 390)
        {} else return;

        int y = pos.y - 10;

        double scale = modelCanvas.getScale ();
        int length = 600 / scale / 2;
        int shiftY = 0;
        if (scale > 1.0) 
        {            
            if (y < length) 
            {
                shiftY = 0;
                drawState (length, length);
            }
            else if (y > 380 - length) 
            {
                shiftY = 400 - 400 / scale;
                drawState (380 - length, length);
            }
            else
            {
                y -= length;
                shiftY = 1.0 * (400 - 1.0 * 400 / scale) * y / (380 - length * 2);
                drawState (pos.y, length);
            }
        }
        else
        {
            length = (390 - 10) / 2;
            drawState (10 + length, length);
        }
        modelCanvas.setShiftY (shiftY);
    }
};

class ActionScrollHorizontally : public Action
{
private:
    ModelCanvas& modelCanvas;
    Picture* pictureCurrent;

public:
    ActionScrollHorizontally (ModelCanvas& init_modelPhotoshop)
        : modelCanvas(init_modelPhotoshop)
    { }

    virtual Scene* create(std::vector<void*>* buttons) override
    {
        VectorDec size  = {600, 400};

        pictureCurrent = new Picture {size, {kCanvasXEnd - size.x, kCanvasYBegin}};
        Button* button = new Button {{580, 10},  {kCanvasYBegin + 10, 500 - 10}, *this};
        buttons->push_back (button);

        Scene* sceneParameter = new Scene {};
        sceneParameter->addObject (*button);
        sceneParameter->addObject (*pictureCurrent);
        sceneParameter->setIsDraw (false);
        return sceneParameter;
    }

    virtual void call (Event event) override
    {        
        VectorDec pos = {event.getCoord().x, event.getCoord().y};

        if (10  <= pos.x && pos.x <= 590 && 
            390 <= pos.y && pos.y <= 400)
        {} else return;

        int shiftX = 0;
        double scale = modelCanvas.getScale ();
        if (scale > 1.0) 
        {            
            shiftX = 1.0 * (600 - 1.0 * 600 / scale) * (pos.x - 10) / 580;
        }
        modelCanvas.setShiftX (shiftX);
        // drawState (scale);
    }
};

class ActionScale : public Action
{
private:
    ModelCanvas& modelCanvas;
    ActionScrollVertically   actionScrollVertically;
    ActionScrollHorizontally actionScrollHorizontally;
    Picture* pictureBackground;
    Picture* pictureCurrent;

public:
    ActionScale (ModelCanvas& init_modelPhotoshop)
        : modelCanvas(init_modelPhotoshop), 
          actionScrollVertically   (init_modelPhotoshop),
          actionScrollHorizontally (init_modelPhotoshop)
    { }

    virtual Scene* create(std::vector<void*>* buttons) override
    {
        VectorDec size  = {600, 400};
        const char* png = "img/scale2.png";

        pictureCurrent = new Picture {size, {kCanvasXEnd - size.x, kCanvasYBegin}, png};
        Button* button = new Button {{140, 160}, {kCanvasXBegin + 448, kCanvasYBegin}, *this};
        buttons->push_back (button);

        Scene* sceneParameter = new Scene {};
        sceneParameter->addObject (*button);
        sceneParameter->addObject (*pictureCurrent);
        sceneParameter->setIsDraw (false);

        Scene* sceneScrollVertically   = actionScrollVertically.create   (buttons);
        Scene* sceneScrollHorizontally = actionScrollHorizontally.create (buttons);
        sceneParameter->addScene (*sceneScrollVertically);
        sceneParameter->addScene (*sceneScrollHorizontally);
        
        return sceneParameter;
    }

    virtual void call (Event event) override
    {
        VectorDec pos = {event.getCoord().x, event.getCoord().y};

        if (450 <= pos.x && pos.x <= 515 && 
            0   <= pos.y && pos.y <= 70)
        {
            double scale = modelCanvas.getScale () * 2;
            if (scale >= 10) return;
            modelCanvas.setScale (scale);
            // drawState (scale);
        }
        if (520 <= pos.x && pos.x <= 585 && 
            0   <= pos.y && pos.y <= 70)
        {
            double scale = modelCanvas.getScale () / 2;
            if (scale <= 0.2) return;
            modelCanvas.setScale (scale);
            // drawState (scale);
        }
    }
};

/**************************************************************************/

#endif /* STL_PARAMETER_SCALE */