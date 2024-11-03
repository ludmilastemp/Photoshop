#ifndef STL_PARAMETERMANAGER
#define STL_PARAMETERMANAGER

#include "object.hpp"

class ParameterManager
{
public:
    std::vector <Scene*> scenes; 

    Scene* activeScene;

    void addScene (Scene& scene);
    void activate (Scene& scene);
    void deActivate ();
};

#endif /* STL_PARAMETERMANAGER */