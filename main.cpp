#include <iostream>

#include <SFML/Graphics.hpp>
#include <dlfcn.h>

#include "MVC/modelPhotoshop.hpp"
#include "MVC/controllerPhotoshop.hpp"
#include "MVC/viewPhotoshop.hpp"

#include "Standard/PsSPI-impl.hpp"
#include "objects/button.hpp"

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

    Button buttonFile   {{57, 50},  {0, 0},   "img/menu/file.png"};
    Button buttonEdit   {{63, 50},  {57, 0},  "img/menu/edit.png"};
    Button buttonImage  {{83, 50},  {120, 0}, "img/menu/image.png"};
    Button buttonLayer  {{76, 50},  {203, 0}, "img/menu/layer.png"};
    Button buttonSelect {{82, 50},  {279, 0}, "img/menu/select.png"};
    Button buttonFilter {{72, 50},  {361, 0}, "img/menu/filter.png"};
    Button buttonView   {{69, 50},  {433, 0}, "img/menu/view.png"};
    Button buttonWindow {{102, 50}, {502, 0}, "img/menu/window.png"};
    Button buttonMore   {{75, 50},  {604, 0}, "img/menu/more.png"};
    main_scene.addObject (buttonFile);
    main_scene.addObject (buttonEdit);
    main_scene.addObject (buttonImage);
    main_scene.addObject (buttonLayer);
    main_scene.addObject (buttonSelect);
    main_scene.addObject (buttonFilter);
    main_scene.addObject (buttonView);
    main_scene.addObject (buttonWindow);
    main_scene.addObject (buttonMore);

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
