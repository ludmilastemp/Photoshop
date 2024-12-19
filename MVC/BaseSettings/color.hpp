#ifndef STL_PARAMETER_COLOR
#define STL_PARAMETER_COLOR

#include <cstdlib>
#include <cmath>
#include "../../objects/actionClass.hpp"
#include "../../objects/button.hpp"

#include "../modelCanvas.hpp"

/**************************************************************************/

class ActionColor : public Action
{
private:
    ModelCanvas& modelCanvas;
    Picture* pictureBackground;
    int size = 30;
    Color colorConst;
    Color colorTmp;

public:
    ActionColor (ModelCanvas& init_modelPhotoshop)
        : modelCanvas(init_modelPhotoshop)
    { }

    void drawState ()
    {
        for (int r_x = -size; r_x < size; r_x++)
        {
            for (int r_y = -size; r_y < 0; r_y++)
            {
                if (r_x * r_x + r_y * r_y <= size * size)
                {
                    pictureBackground->setPixel (75 + r_x, 75 + r_y, colorConst);
                }
            }
            for (int r_y = 0; r_y < size; r_y++)
            {
                if (r_x * r_x + r_y * r_y <= size * size)
                {
                    pictureBackground->setPixel (75 + r_x, 75 + r_y, colorTmp);
                }
            }
        }
        pictureBackground->update ();
    }
    
    virtual Scene* create (std::vector<void*>* buttons) override
    {
        VectorDec size = {150, 150};
        const char* png = "img/colorwheel.png";

        pictureBackground = new Picture {size, {kCanvasXEnd - size.x, kCanvasYBegin}, png};
        Button* button    = new Button  {size, {kCanvasXEnd - size.x, kCanvasYBegin}, *this, png};
        buttons->push_back (button);

        Scene* sceneParameter = new Scene {};
        sceneParameter->addObject (*button);
        sceneParameter->addObject (*pictureBackground);
        sceneParameter->setIsDraw (false);
        return sceneParameter;
    }

    virtual void active () override
    {
        colorTmp = modelCanvas.getColor ();
        drawState ();
    }

    virtual void call (Event event) override
    {
        colorConst = pictureBackground->getPixel (event.getCoord().x, event.getCoord().y);
        colorTmp = colorConst;
        modelCanvas.setColor (colorConst);
        drawState ();
    }

    void setColor (Color new_color)
    {
        colorConst = new_color;
        colorTmp = colorConst;
        drawState ();
    }
};

/**************************************************************************/

#endif /* STL_PARAMETER_COLOR */