#include <iostream>

#include <SFML/Graphics.hpp>
#include <dlfcn.h>

#include "MVC/BaseSettings/create.hpp"
#include "MVC/modelPhotoshop.hpp"
#include "MVC/controllerPhotoshop.hpp"
#include "MVC/viewPhotoshop.hpp"

#include "Standard/PsSPI-impl.hpp"

using namespace std;

int main (int argc, char **argv)
{
    printf ("Start\n");

    GraphicsCtx ctx {};
    Scene main_scene {};

/*
 * MVC photoshop
 */
    ModelPhotoshop modelPhotoshop {main_scene};
    ModelCanvas&   modelCanvas = modelPhotoshop.modelCanvas;
    ViewPhotoshop  viewPhotoshop  {main_scene, modelCanvas.systemState};
    ControllerPhotoshop controllerPhotoshop {modelPhotoshop.modelButton};
    CreateBaseSettings (modelPhotoshop);

/*
 * Добавление plugins
 */
    StlPsSPI psspi {modelPhotoshop, modelCanvas, ctx};
    modelPhotoshop.setPsspi (&psspi);

    for (int i = 1; i < argc; i++)
    {
        modelPhotoshop.addPlugin(argv[i]);
    }

/*
 * Начало программы
 */
    int i = 0;
    while (IsWindowOpen(ctx))
    {
        if (i++ == 100000) {}
        if (ctx.event () == false) continue;
        if (CheckEventCloseWindow (ctx)) break;

        /*
         * MVC
         */ 
            controllerPhotoshop (ctx);
            modelCanvas (ctx.event);
            viewPhotoshop (ctx);   
    }

    modelPhotoshop.closePlugins ();
    printf ("End\n");

    return 0;
}
