#ifndef STL_MANAGER
#define STL_MANAGER

#include "../../objects/object.hpp"

template <class T>
class Manager
{
public:
    std::vector <T*> objects; 
    int activeObject;

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
        deactivate ();

        if (-1 <= object && object < objects.size())
        {
            activeObject = object;
            objects[object]->activate ();
        }
    }

    void deactivate ()
    {
        if (0 <= activeObject && activeObject < objects.size())
        {
            objects[activeObject]->deactivate ();
        }
        activeObject = -1;
    }

    void reActivate ()
    {
        if (0 <= activeObject && activeObject < objects.size())
        {
            int object = activeObject;
            deactivate ();
            activate (object);
        }
    }
};

#endif /* STL_MANAGER */