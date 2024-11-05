#ifndef STL_PARAMETERMANAGER
#define STL_PARAMETERMANAGER

#include "object.hpp"

class ParameterManager
{
public:
    std::vector <Scene*> scenes; 
    int activeScene;

    ParameterManager () 
        :activeScene (-1)
    {}

    void addScene (Scene& scene);
    void activate (int scene);
    void deActivate ();
    void reActivate ();

    size_t getSize () { return scenes.size(); }
};

#endif /* STL_PARAMETERMANAGER */