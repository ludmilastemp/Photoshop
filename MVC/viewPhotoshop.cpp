#include "viewPhotoshop.hpp" 
#include <stdio.h>
/**************************************************************************/

ViewPhotoshop::ViewPhotoshop (Scene& init_main_scene, SystemState& init_systemState)
    :main_scene(init_main_scene), systemState(init_systemState)
{}

/**************************************************************************/

void ViewPhotoshop::update (GraphicsCtx& ctx)
{
    static int tmp = 0;
    CleanWindow (ctx);

    main_scene.draw(ctx);
    for (int i = 0; i < systemState.pictures.size(); i++)
    {
        if (!tmp)
            printf ("draw %p\n", systemState.pictures[i]);
        systemState.pictures[i]->draw(ctx);
    }

    tmp++;
    DisplayWindow(ctx);    
}

/**************************************************************************/
