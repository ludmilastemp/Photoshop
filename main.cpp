#include <iostream>

#include <SFML/Graphics.hpp>

#include "MVC/modelPhotoshop.hpp"
#include "MVC/controllerPhotoshop.hpp"
#include "MVC/viewPhotoshop.hpp"
#include "tools/brush.hpp"
#include "tools/eraser.hpp"
#include "tools/line.hpp"
#include "parameters/color.hpp"
#include "parameters/size.hpp"
#include "parameters/scale.hpp"

#include "Standard/PsSPI-impl.hpp"

StlPsSPI* tmp_psspi = nullptr;

PsSPI* getPsSPI ()
{
    return (PsSPI*)tmp_psspi;
}

using namespace std;

int main ()
{
    printf ("Start\n");

    GraphicsCtx ctx {};
    Scene main_scene {};

/*
 * MVC photoshop
 */
    ModelPhotoshop modelPhotoshop {main_scene};
    ViewPhotoshop  viewPhotoshop  {main_scene};
    ModelCanvas&   modelCanvas = modelPhotoshop.modelCanvas;
    ControllerPhotoshop controllerPhotoshop {modelPhotoshop.modelButton};

/*
 * Добавление тулов
 */
    ToolBrush  brush  (modelCanvas, ctx);
    ToolEraser eraser (modelCanvas, ctx);
    ToolLine   line   (modelCanvas, ctx);

    modelPhotoshop.addTool (brush,  "img/brush.png");
    modelPhotoshop.addTool (eraser, "img/eraser.png");
    modelPhotoshop.addTool (line,   "img/line.png");

/*
 * Добавление параметров
 */
    ActionColor actionColor (modelCanvas);
    ActionSize  actionSize  (modelCanvas);
    ActionScale actionScale (modelCanvas);

    modelPhotoshop.addParameter (actionColor, "img/colorwheel_icon.png");
    modelPhotoshop.addParameter (actionSize,  "img/size_icon.png");
    modelPhotoshop.addParameter (actionScale, "img/1.png");

    StlPsSPI psspi {modelPhotoshop, modelCanvas, ctx};
    tmp_psspi = &psspi;

    // loadPlugin ();

/*
 * Начало программы
 */

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

    printf ("End\n");

    return 0;
}
