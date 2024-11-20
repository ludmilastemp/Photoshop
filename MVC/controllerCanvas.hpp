#ifndef STL_CONTROLLER_CANVAS
#define STL_CONTROLLER_CANVAS

#include "Controller/modelButton.hpp"

class ControllerCanvas
{
public:
    ModelButton& modelButton;

    ControllerCanvas (ModelButton& modelButton);

    void operator() (GraphicsCtx& ctx) 
    {
        return update (ctx);
    }

    void update (GraphicsCtx& ctx);
};

#endif /* STL_CONTROLLER_CANVAS */