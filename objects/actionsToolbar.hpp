#ifndef STL_ACTIONSTOOL
#define STL_ACTIONSTOOL

#include <cstdlib>
#include "actionClass.hpp"

#include "../MVC/modelCanvas.hpp"

/**************************************************************************/

class ActionToolbar : public Action
{
private:
    ModelCanvas& modelCanvas;
    VectorDec corner;

public:
    ActionToolbar (ModelCanvas& init_modelPhotoshop, VectorDec init_corner)
        : modelCanvas(init_modelPhotoshop), corner (init_corner)
    {}

    virtual void call (Event event) override
    {
        int y = event.getCoord().y - corner.y;

        if (y / (kHeightIcon + kOffsetIcon) < modelCanvas.toolbar.getSize() && 
            y % (kHeightIcon + kOffsetIcon) <= kHeightIcon)
        {
            printf ("setActiveTool %d\n", y / (kHeightIcon + kOffsetIcon));
            modelCanvas.setActiveTool (y / (kHeightIcon + kOffsetIcon));
        }
    }
};

class ActionParameterManager : public Action
{
private:
    ModelCanvas& modelCanvas;
    VectorDec corner;

public:
    ActionParameterManager (ModelCanvas& init_modelPhotoshop, VectorDec init_corner)
        : modelCanvas(init_modelPhotoshop), corner (init_corner)
    {}

    virtual void call (Event event) override
    {
        int y = event.getCoord().y - corner.y;

        if (y / (kHeightIcon + kOffsetIcon) < modelCanvas.parameterManager.getSize() && 
            y % (kHeightIcon + kOffsetIcon) <= kHeightIcon)
        {
            int scene = y / (kHeightIcon + kOffsetIcon);
            if (modelCanvas.parameterManager.objects[scene]->getIsDraw () == true)
                modelCanvas.parameterManager.deActivate ();
            else
                modelCanvas.parameterManager.activate (scene);
        }
    }
};

/**************************************************************************/

#endif /* STL_ACTIONSTOOL */