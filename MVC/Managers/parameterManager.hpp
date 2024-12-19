#ifndef STL_PARAMETER_MANAGER
#define STL_PARAMETER_MANAGER

#include "manager.hpp"
#include "../../objects/actionClass.hpp"

class ParameterManager : public Manager<Scene>
{
public:
    Action* color;

    ParameterManager () 
        :Manager ()
    {}

    void update ()
    {
        printf ("ParameterManager update\n");
        if (activeObject > 0)
            deactivate();
        color->active();
    }
};

#endif /* STL_PARAMETER_MANAGER */