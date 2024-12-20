#ifndef STL_MANAGER
#define STL_MANAGER

#include "objects/object.hpp"

template <class T>
class Manager
{
public:
    std::vector <T*> objects; 
    int activeObject = -1;

    Manager () 
        :activeObject (-1)
    {}

    size_t getSize () { return objects.size(); }

    void add (T& object)
    {
        objects.push_back(&object);
    }
    
    void activate (int object)
    {
        printf ("activate %d %d\n", activeObject, object);
        deactivate ();

        if (0 <= object && object < objects.size())
        {
            activeObject = object;
            objects[object]->activate ();
        }
    }

    void deactivate ()
    {
        printf ("deactivate %d\n", activeObject);
        if (0 <= activeObject && activeObject < objects.size())
        {
            objects[activeObject]->deactivate ();
        }
        activeObject = -1;
    }

    void reActivate ()
    {
        printf ("reActivate %d\n", activeObject);
        if (0 <= activeObject && activeObject < objects.size())
        {
            int object = activeObject;
            activate (object);
        }
    }
};

using MenuManager = Manager<Scene>;

#endif /* STL_MANAGER */