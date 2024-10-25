#include "viewPhotoshop.hpp" 

/**************************************************************************/

ViewPhotoshop::ViewPhotoshop (SystemState& init_systemState)
    :systemState (&init_systemState)
{}

/**************************************************************************/

void ViewPhotoshop::update (GraphicsCtx& ctx)
{
    // CleanWindow (ctx);

    ctx.window.draw (systemState->background.sprite);
    ctx.window.draw (systemState->base.sprite);
    ctx.window.draw (systemState->tmp.sprite);

    // DisplayWindow(ctx);    
}

/**************************************************************************/
