#ifndef STL_FILTER
#define STL_FILTER

#include "GrLib/GrLibCtx.hpp"
#include "GrLib/color.hpp"
#include "objects/object.hpp"

class Filter
{
public:
    int nParameters = 0;
    std::vector<int> parametersIndex;
    Scene parameterButtons;

    Filter ()
    {
        parameterButtons.setIsDraw (false);
    }

    virtual ~Filter () = default;

    void operator() (Event event)
    {
        apply (event);
    }

    virtual void apply (Event event) = 0;
    virtual void activate ()   { parameterButtons.setIsDraw (true); }
    virtual void deactivate () { parameterButtons.setIsDraw (false); }
};

#endif /* STL_FILTER */