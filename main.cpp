#include <iostream>

#include <SFML/Graphics.hpp>

#include "GrLib/GrLib.hpp"
#include "MVC/modelPhotoshop.hpp"
#include "MVC/controllerCanvas.hpp"
#include "MVC/viewPhotoshop.hpp"
#include "tools/brush.hpp"
#include "tools/eraser.hpp"
#include "tools/line.hpp"

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
    ControllerCanvas controllerCanvas {modelPhotoshop.modelButton};

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

    modelPhotoshop.addParameter (actionColor, {150, 150}, "img/colorwheel.png", "img/colorwheel_icon.png");
    modelPhotoshop.addParameter (actionSize,  {150, 200}, "img/size.png",       "img/size_icon.png");
    modelPhotoshop.addParameter (actionScale, {600, 400}, "img/scale2.png",     "img/1.png");

/*
 * Начало программы
 */

    while (IsWindowOpen(ctx))
    {
        if (ctx.event () == false) continue;
        if (CheckEventCloseWindow (ctx)) break;

        /*
         * MVC
         */ 
            controllerCanvas (ctx);
            modelCanvas (ctx.event);
            viewPhotoshop (ctx);   
    }

    printf ("End\n");

    return 0;
}
