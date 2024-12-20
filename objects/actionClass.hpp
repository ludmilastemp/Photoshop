#ifndef STL_ACTIONSCLASS
#define STL_ACTIONSCLASS

#include <vector>
#include "object.hpp"

class Action // функтор
{
public:

    virtual ~Action () = default;

    bool operator() ()
    {
        return call();
    }

    bool operator() (Event event)
    {
        return call(event);
    }

    virtual bool call() { return true; }
    virtual bool call(Event event) 
    {
        return call ();
    }

    virtual Scene* create (std::vector<void*>* buttons) { return nullptr; }
    virtual void active() {}
};

/**************************************************************************/

#endif /* STL_ACTIONS */