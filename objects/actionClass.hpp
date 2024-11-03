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

    void operator() (sf::Event event)
    {
        call(event);
    }

    virtual void call() {}
    virtual void call(sf::Event event) 
    {
        call ();
    }
};

/**************************************************************************/

#endif /* STL_ACTIONS */