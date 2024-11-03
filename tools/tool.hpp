#ifndef STL_TOOL
#define STL_TOOL

#include "../GrLib/GrLibCtx.hpp"

class Tool 
{
public:

    virtual ~Tool () = default;

    void operator() (sf::Event event)
    {
        active (event);
    }

    virtual void active (sf::Event event) = 0;
    virtual void setColor (Color& color) {}
    virtual void setSize  (int size)    {}
    virtual void stop   () {}
};

#endif /* STL_TOOL */