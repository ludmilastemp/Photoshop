#ifndef STL_CONTROLLER_PHOTOSHOP
#define STL_CONTROLLER_PHOTOSHOP

#include "MVC_Button/modelButton.hpp"

class ControllerPhotoshop
{
public:
    ModelButton& modelButton;

    ControllerPhotoshop (ModelButton& modelButton);

    void operator() (GraphicsCtx& ctx) 
    {
        return update (ctx);
    }

    void update (GraphicsCtx& ctx);
};

#endif /* STL_CONTROLLER_PHOTOSHOP */