#ifndef STL_ACTIONSPARAMETERICON
#define STL_ACTIONSPARAMETERICON

#include <cstdlib>
#include "actionClass.hpp"
#include "object.hpp"
#include "parameterManager.hpp"

/**************************************************************************/

class ActionIcon : public Action
{
private:
    ParameterManager& parameterManager;
    int scene;

public:
    ActionIcon (ParameterManager& init_parameterManager, int init_scene)
        : parameterManager (init_parameterManager), scene(init_scene)
    {}

    virtual void call () override
    {
        if (parameterManager.scenes[scene]->getIsDraw () == true)
            parameterManager.deActivate ();
        else
            parameterManager.activate (scene);
    }
};

/**************************************************************************/

#endif /* STL_ACTIONSPARAMETERICON */