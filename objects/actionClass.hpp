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

    virtual void call() = 0;
};

/**************************************************************************/

#endif /* STL_ACTIONS */