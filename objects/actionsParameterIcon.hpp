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
        if (scene.getIsDraw () == true)
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
        if (scene.getIsDraw () == true)
            parameterManager.deActivate ();
        else
            parameterManager.activate (scene);
    }
};

/**************************************************************************/

#endif /* STL_ACTIONSPARAMETERICON */