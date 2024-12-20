#ifndef STL_ACTIONS_MANAGERS
#define STL_ACTIONS_MANAGERS

#include <cstdlib>
#include "objects/actionClass.hpp"
#include "MVC/modelCanvas.hpp"
#include "manager.hpp"

/**************************************************************************/

class ModelPhotoshop;

class ActionToolbar : public Action
{
private:
    ModelPhotoshop* modelPhotoshop;
    ModelCanvas& modelCanvas;
    VectorDec corner;

public:
    ActionToolbar (ModelPhotoshop* init_modelPhotoshop, ModelCanvas& init_modelCanvas, VectorDec init_corner)
        : modelPhotoshop(init_modelPhotoshop), 
          modelCanvas(init_modelCanvas), 
          corner (init_corner)
    {}

    virtual bool call (Event event) override;
};

class ActionParameterManager : public Action
{
private:
    ModelCanvas& modelCanvas;
    VectorDec corner;

public:
    ActionParameterManager (ModelCanvas& init_modelCanvas, VectorDec init_corner)
        : modelCanvas(init_modelCanvas), corner (init_corner)
    {}

    virtual bool call (Event event) override
    {
        int x = event.getCoord().x;

// 1 - постоянные параметры (color)

        if (x / (kWidthParam + kOffsetParam) < modelCanvas.parameterManager.getSize() - 1 && 
            x % (kWidthParam + kOffsetParam) <= kWidthParam)
        {
            int object = x / (kWidthParam + kOffsetParam);
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
            return true;
        }
        return false;
    }
};

class ActionColorIcon : public Action
{
public: 
    ParameterManager& parameterManager;

    ActionColorIcon (ParameterManager& init_parameterManager)
        : parameterManager (init_parameterManager)
    {}

    virtual bool call (Event event) override
    {
        if (parameterManager.activeObject == 0)
            parameterManager.deactivate ();
        else
            parameterManager.activate (0);
        return true;
    }
};

class ActionIcon : public Action
{
public:
    ModelPhotoshop* modelPhotoshop;
    int index;
    MenuManager& menuManager;

    ActionIcon (ModelPhotoshop* init_modelPhotoshop, MenuManager& init_menuManager)
        : modelPhotoshop(init_modelPhotoshop),
          menuManager (init_menuManager), 
          index (init_menuManager.objects.size() - 1)
    {}

    virtual bool call (Event event) override;
};

/**************************************************************************/

#endif /* STL_ACTIONS_MANAGERS */