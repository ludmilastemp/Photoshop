#ifndef STL_PARAMETERMANAGER
#define STL_PARAMETERMANAGER

#include "object.hpp"

class ParameterManager
{
public:
    std::vector <Scene*> scenes; //?
    Scene* activeScene;

    ParameterManager () 
        :activeScene (nullptr)
    {}

    void addScene (Scene& scene);
    void activate (Scene& scene);
    void deActivate ();
    void reActivate ();
};

#endif /* STL_PARAMETERMANAGER */