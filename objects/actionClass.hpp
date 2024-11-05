#ifndef STL_ACTIONSCLASS
#define STL_ACTIONSCLASS

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

    virtual void active() {}
};

/**************************************************************************/

#endif /* STL_ACTIONS */