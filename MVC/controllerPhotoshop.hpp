#ifndef STL_CONTROLLER_PHOTOSHOP
#define STL_CONTROLLER_PHOTOSHOP

#include "MVC_Button/modelButton.hpp"
#include "MVC_Button/viewButton.hpp"

class ControllerPhotoshop
{
public:
    ModelButton& modelButton;
    ViewButton&  viewButton;

    ControllerPhotoshop (ModelButton& modelButton, ViewButton&  viewButton);

    void operator() (GraphicsCtx& ctx) 
    {
        return update (ctx);
    }

    void update (GraphicsCtx& ctx);
};

#endif /* STL_CONTROLLER_PHOTOSHOP */