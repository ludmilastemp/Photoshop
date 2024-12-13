#ifndef STL_ACTIONS_MANAGERS
#define STL_ACTIONS_MANAGERS

#include <cstdlib>
#include "../../objects/actionClass.hpp"

#include "../modelCanvas.hpp"

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
        int y = event.getCoord().y;

        if (y / (kHeightIcon + kOffsetIcon) < modelCanvas.toolbar.getSize() && 
            y % (kHeightIcon + kOffsetIcon) <= kHeightIcon)
        {
            int object = y / (kHeightIcon + kOffsetIcon);
            printf ("setActiveTool %d\n", object);
            if (modelCanvas.toolbar.activeObject == object)
            {
                modelCanvas.setActiveTool (-1);
            }
            else
            {
                modelCanvas.setActiveTool (object);
            }
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
        int y = event.getCoord().y;

        if (y / (kHeightIcon + kOffsetIcon) < modelCanvas.parameterManager.getSize() && 
            y % (kHeightIcon + kOffsetIcon) <= kHeightIcon)
        {
            int object = y / (kHeightIcon + kOffsetIcon);
            printf ("object %d\n", object);
            printf ("active tool %d\n", modelCanvas.toolbar.activeObject);
            if (object >= 0)
                object = modelCanvas.toolbar.objects[modelCanvas.toolbar.activeObject]->parametersIndex[object];
            printf ("object %d\n", object);
            if (modelCanvas.parameterManager.activeObject == object)
            {
                modelCanvas.parameterManager.deactivate ();
            }
            else
            {
                modelCanvas.parameterManager.activate (object);
            }
        }
    }
};

/**************************************************************************/

#endif /* STL_ACTIONS_MANAGERS */