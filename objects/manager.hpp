#ifndef STL_MANAGER
#define STL_MANAGER

#include "object.hpp"

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
        deActivate ();

        if (-1 <= object && object < objects.size())
        {
            activeObject = object;
            objects[object]->activate ();
        }
    }

    void deActivate ()
    {
        if (0 <= activeObject && activeObject < objects.size())
        {
            objects[activeObject]->deActivate ();
        }
        activeObject = -1;
    }

    void reActivate ()
    {
        if (0 <= activeObject && activeObject < objects.size())
        {
            int object = activeObject;
            deActivate ();
            activate (object);
        }
    }
};

#endif /* STL_MANAGER */