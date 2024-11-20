#ifndef STL_ACTIONSCLASS
#define STL_ACTIONSCLASS

#include <vector>
#include "object.hpp"

class Action // функтор
{
public:

    virtual ~Action () = default;

    void operator() ()
    {
        call();
    }

    void operator() (Event event)
    {
        call(event);
    }

    virtual void call() {}
    virtual void call(Event event) 
    {
        call ();
    }

    virtual Scene* create (std::vector<void*>* buttons) { return nullptr; }
    virtual void active() {}
};

/**************************************************************************/

#endif /* STL_ACTIONS */