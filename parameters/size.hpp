#ifndef STL_PARAMETER_SIZE
#define STL_PARAMETER_SIZE

#include <cstdlib>
#include <cmath>
#include "../objects/actionClass.hpp"

#include "../MVC/modelCanvas.hpp"

/**************************************************************************/

class ActionSize : public Action
{
private:
    ModelCanvas& modelCanvas;
    Picture* pictureBackground;
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

    virtual Scene* create(std::vector<void*>* buttons) override
    {
        VectorDec size = {150, 200};
        const char* png = "img/size.png";

        pictureBackground = new Picture {size, {kCanvasXEnd - size.x, kCanvasYBegin}, png};
        pictureCurrent    = new Picture {size, {kCanvasXEnd - size.x, kCanvasYBegin}};
        Button* button    = new Button {size, {kCanvasXEnd - size.x, kCanvasYBegin}, *this};
        buttons->push_back (button);

        Scene* sceneParameter = new Scene {};
        sceneParameter->addObject (*button);
        sceneParameter->addObject (*pictureBackground);
        sceneParameter->addObject (*pictureCurrent);
        sceneParameter->setIsDraw (false);
        return sceneParameter;
    }

    virtual void active () override
    {
        int size = modelCanvas.getSize ();
        drawState (size);
    }

    virtual void call (Event event) override
    {
        VectorDec pos = {event.getCoord().x, event.getCoord().y};

        if (15 <= pos.x && pos.x <= 140 && 
            0  <= pos.y && pos.y <= 200)
        {
            int size = (int)(1.0 * (pos.x - 15) / 125 * (60 - 1) + 1);
            drawState (size);
            modelCanvas.setSize (size);
        }
    }
};

/**************************************************************************/

#endif /* STL_PARAMETER_SIZE */