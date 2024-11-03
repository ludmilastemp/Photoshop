#ifndef STL_ACTIONSPARAMETERICON
#define STL_ACTIONSPARAMETERICON

#include <cstdlib>
#include "actionClass.hpp"
#include "object.hpp"
#include "parameterManager.hpp"

/**************************************************************************/

class ActionColorIcon : public Action
{
private:
    ParameterManager& parameterManager;
    Scene& scene;

public:
    ActionColorIcon (ParameterManager& init_parameterManager, Scene& init_scene)
        : parameterManager (init_parameterManager), scene(init_scene)
    {}

    virtual void call () override
    {
        if (scene.isDraw == true)
            parameterManager.deActivate ();
        else
            parameterManager.activate (scene);
    }
};

class ActionSizeIcon : public Action
{
private:
    ParameterManager& parameterManager;
    Scene& scene;

public:
    ActionSizeIcon (ParameterManager& init_parameterManager, Scene& init_scene)
        : parameterManager (init_parameterManager), scene(init_scene)
    {}

    virtual void call () override
    {
        if (scene.isDraw == true)
            parameterManager.deActivate ();
        else
            parameterManager.activate (scene);
    }
};

// class ActionEraser : public Action
// {
// private:
//     ModelPhotoshop& modelPhotoshop;

// public:
//     ActionEraser (ModelPhotoshop& init_modelPhotoshop)
//         : modelPhotoshop(init_modelPhotoshop)
//     {}

//     virtual void call () override
//     {
//         std::cout << "setActiveTool 1\n";
//         modelPhotoshop.setActiveTool (1);
//     }
// };

// class ActionLine : public Action
// {
// private:
//     ModelPhotoshop& modelPhotoshop;

// public:
//     ActionLine (ModelPhotoshop& init_modelPhotoshop)
//         : modelPhotoshop(init_modelPhotoshop)
//     {}

//     virtual void call () override
//     {
//         std::cout << "setActiveTool 2\n";
//         modelPhotoshop.setActiveTool (2);
//     }
// };

/**************************************************************************/

#endif /* STL_ACTIONSPARAMETERICON */