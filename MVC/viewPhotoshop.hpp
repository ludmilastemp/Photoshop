#ifndef STL_VIEW_PHOTOSHOP
#define STL_VIEW_PHOTOSHOP

#include "systemState.hpp"
#include "GrLib/GrLib.hpp"

class ViewPhotoshop
{
public:
    Scene& main_scene;
    SystemState& systemState;

    ViewPhotoshop (Scene& main_scene, SystemState& systemState);

    void operator() (GraphicsCtx& ctx)
    {
        update (ctx);
    }

    void update (GraphicsCtx& ctx);
};

#endif /* STL_VIEW_PHOTOSHOP */