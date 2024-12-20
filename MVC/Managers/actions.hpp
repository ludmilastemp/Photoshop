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

    virtual bool call (Event event) override
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
            return true;
        }
        return false;
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
    Scene& scene;

    ActionIcon (Scene& init_scene)
        : scene (init_scene)
    {}

    virtual bool call (Event event) override
    {
        if (scene.getIsDraw())
            scene.setIsDraw(false);
        else
            scene.setIsDraw(true);
        return true;
    }
};

/**************************************************************************/

#endif /* STL_ACTIONS_MANAGERS */