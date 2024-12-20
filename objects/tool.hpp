#ifndef STL_TOOL
#define STL_TOOL

#include "GrLib/GrLibCtx.hpp"
#include "GrLib/color.hpp"
#include "objects/object.hpp"

class Tool 
{
public:
    int nParameters = 0;
    std::vector<int> parametersIndex;
    Scene parameterButtons;

    Tool ()
    {
        parameterButtons.setIsDraw (false);
    }

    virtual ~Tool () = default;

    void operator() (Event event)
    {
        apply (event);
    }

    virtual void apply (Event event) = 0;
    virtual void setColor (Color& color) {}
    virtual void setSize  (int size)    {}
    virtual Color getColor ()   { return {1, 1, 1, 1}; }
    virtual int   getSize  ()   { return 0; }
    virtual void  activate ()   { parameterButtons.setIsDraw (true); }
    virtual void  deactivate () { parameterButtons.setIsDraw (false); }
};

#endif /* STL_TOOL */