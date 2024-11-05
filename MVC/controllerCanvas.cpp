#include "controllerCanvas.hpp"

/**************************************************************************/

ControllerCanvas::ControllerCanvas (ModelButton& init_modelButton)
    : modelButton(init_modelButton)
{}

/**************************************************************************/

void ControllerCanvas::update (GraphicsCtx& ctx)
{
    if ((ctx.event.getType () == -1 || ctx.event.getType () == Event::event_controller) &&
        ctx.event.getMousePressed ())
    {
        VectorDec pos = ctx.event.getCoord();

        if (modelButton (pos, ctx.event))
            ctx.event.setType (Event::event_controller);
    }
}

/**************************************************************************/
