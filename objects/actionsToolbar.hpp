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

        if (y / 60 < modelCanvas.toolbar.getSize() && 
            y % 60 <= 50)
        {
            printf ("setActiveTool %d\n", y / 60);
            modelCanvas.setActiveTool (y / 60);
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

        if (y / 60 < modelCanvas.parameterManager.getSize() && 
            y % 60 <= 50)
        {
            int scene = y / 60;
            if (modelCanvas.parameterManager.scenes[scene]->getIsDraw () == true)
                modelCanvas.parameterManager.deActivate ();
            else
                modelCanvas.parameterManager.activate (scene);
        }
    }
};



/**************************************************************************/

#endif /* STL_ACTIONSTOOL */