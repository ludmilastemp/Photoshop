#ifndef STL_TOOL
#define STL_TOOL

#include "../GrLib/GrLibCtx.hpp"
#include "../GrLib/color.hpp"

class Tool 
{
public:

    virtual ~Tool () = default;

    void operator() (Event event)
    {
        apply (event);
    }

    virtual void apply (Event event) = 0;
    virtual void setColor (Color& color) {}
    virtual void setSize  (int size)    {}
    virtual Color getColor () { return {1, 1, 1, 1}; }
    virtual int   getSize  () { return 0; }
    virtual void  activate () {}
    virtual void  deActivate () {}
};

#endif /* STL_TOOL */