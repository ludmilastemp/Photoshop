#include "viewPhotoshop.hpp" 

/**************************************************************************/

ViewPhotoshop::ViewPhotoshop (Scene& init_main_scene)
    :main_scene(init_main_scene)
{}

/**************************************************************************/

void ViewPhotoshop::update (GraphicsCtx& ctx)
{
    CleanWindow (ctx);

    main_scene.draw(ctx);

    DisplayWindow(ctx);    
}

/**************************************************************************/
