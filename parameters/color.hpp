#ifndef STL_PARAMETER_COLOR
#define STL_PARAMETER_COLOR

#include <cstdlib>
#include <cmath>
#include "../objects/actionClass.hpp"

#include "../MVC/modelCanvas.hpp"

/**************************************************************************/

class ActionColor : public Action
{
private:
    ModelCanvas& modelCanvas;
    Picture* pictureCurrent;
    Picture* pictureBackground;
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
    
    virtual Scene* create(std::vector<void*>* buttons) override
    {
        VectorDec size = {150, 150};
        const char* png = "img/colorwheel.png";

        pictureBackground = new Picture {size, {kCanvasXEnd - size.x, kCanvasYBegin}, png};
        pictureCurrent    = new Picture {size, {kCanvasXEnd - size.x, kCanvasYBegin}};
        Button* button = new Button {size, {kCanvasXEnd - size.x, kCanvasYBegin}, *this, png};
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
        Color color = modelCanvas.getColor ();
        drawState (color);
    }

    virtual void call (Event event) override
    {
        VectorDecUint32 corner = pictureBackground->getPosition();       
        Color color = pictureBackground->getPixel (event.getCoord().x - corner.x, event.getCoord().y - corner.y);
        drawState (color);
        modelCanvas.setColor (color);
    }
};

/**************************************************************************/

#endif /* STL_PARAMETER_COLOR */