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
    Scene setting;

    Filter ()
    {
        setting.setIsDraw (false);
    }

    virtual ~Filter () = default;

    void operator() (Event event)
    {
        apply (event);
    }

    virtual void apply (Event event) = 0;
    virtual void activate ()   { setting.setIsDraw (true); }
    virtual void deactivate () { setting.setIsDraw (false); }
};

#endif /* STL_FILTER */