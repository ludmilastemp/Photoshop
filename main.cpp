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
 * Начало программы
 */
    StlPsSPI psspi {modelPhotoshop, modelCanvas, ctx};

    std::vector <void*> dll;
    for (int i = 1; i < argc; i++)
    {
        void* ptr = dlopen(argv[i], RTLD_NOW | RTLD_LOCAL);
        if (!ptr) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }
        dll.push_back(ptr);

        void (*func)(PsSPI*) = (void (*)(PsSPI*)) dlsym (ptr, "loadPlugin");
        (*func)( &psspi );
    }

    int i = 0;
    while (IsWindowOpen(ctx))
    {
        // if (i++ == 1000) loadPlugin ();
        if (ctx.event () == false) continue;
        if (CheckEventCloseWindow (ctx)) break;

        /*
         * MVC
         */ 
            controllerPhotoshop (ctx);
            modelCanvas (ctx.event);
            viewPhotoshop (ctx);   
    }

    for (void* ptr : dll)
        dlclose(ptr);

    printf ("End\n");

    return 0;
}
