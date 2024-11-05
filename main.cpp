#include <iostream>

#include <SFML/Graphics.hpp>

#include "GrLib/GrLib.hpp"
#include "MVC/controllerPhotoshop.hpp"
#include "MVC/modelPhotoshop.hpp"
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

/*
 * Добавление тулов
 */
    ToolBrush  brush  (modelPhotoshop, ctx);
    ToolEraser eraser (modelPhotoshop, ctx);
    ToolLine   line   (modelPhotoshop, ctx);

    modelPhotoshop.addTool (brush);
    modelPhotoshop.addTool (eraser);
    modelPhotoshop.addTool (line);

/*
 * MVC для кнопок
 */
    ModelButton modelButton {};

/*
 * Создание кнопок для tools
 */
    ActionNone    actionNone   {};
    ActionBrush   actionBrush  {modelPhotoshop};
    ActionEraser  actionEraser {modelPhotoshop};
    ActionLine    actionLine   {modelPhotoshop};

    Button buttonBrush  {{kWidthIcon, kHeightIcon}, {25, 100}, "img/brush.png",  actionBrush};
    Button buttonEraser {{kWidthIcon, kHeightIcon}, {25, 160}, "img/eraser.png", actionEraser};
    Button buttonLine   {{kWidthIcon, kHeightIcon}, {25, 220}, "img/line.png",   actionLine};

    modelButton.addButton (buttonBrush);
    modelButton.addButton (buttonEraser);
    modelButton.addButton (buttonLine);

    Scene scene_tools {};
    scene_tools.addObject (buttonBrush);
    scene_tools.addObject (buttonEraser);
    scene_tools.addObject (buttonLine);
    main_scene.addScene (scene_tools);

/*
 * Добавление параметров
 */
    Picture pictureColor {{150, 200}, {550, 100}, "img/colorwheel.png"};
    ActionColor actionColor (modelPhotoshop, pictureColor);
    Button buttonColor {{150, 150}, {550, 100}, "img/colorwheel.png", actionColor};
    modelButton.addButton (buttonColor);

    Scene scene_parameter_color {};
    scene_parameter_color.addObject (buttonColor);
    scene_parameter_color.addObject (pictureColor);
    scene_parameter_color.setIsDraw (false);
    main_scene.addScene (scene_parameter_color);

    Picture pictureSize {{150, 200}, {550, 100}};
    ActionSize actionSize (modelPhotoshop, pictureSize);
    Button buttonSize {{150, 200}, {550, 100}, "img/size.png", actionSize};
    modelButton.addButton (buttonSize);

    Scene scene_parameter_size {};
    scene_parameter_size.addObject (buttonSize);
    scene_parameter_size.addObject (pictureSize);
    scene_parameter_size.setIsDraw (false);
    main_scene.addScene (scene_parameter_size);

/*
 * Создание кнопок для parameters
 */
    ActionColorIcon actionColorIcon {modelPhotoshop.parameterManager, scene_parameter_color};
    ActionSizeIcon  actionSizeIcon  {modelPhotoshop.parameterManager, scene_parameter_size};

    Button buttonColorIcon {{kWidthIcon, kHeightIcon}, {725, 100}, "img/colorwheel_icon.png", actionColorIcon};
    Button buttonSizeIcon  {{kWidthIcon, kHeightIcon}, {725, 160}, "img/size_icon.png",       actionSizeIcon};
    modelButton.addButton (buttonColorIcon);
    modelButton.addButton (buttonSizeIcon);

    Scene scene_parameters {};
    scene_parameters.addObject (buttonColorIcon);
    scene_parameters.addObject (buttonSizeIcon);
    main_scene.addScene (scene_parameters);

/*
 * Создание контроллера для photoshop
 */
    ControllerPhotoshop controllerPhotoshop {modelButton};

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
            controllerPhotoshop (ctx);
            modelPhotoshop (ctx.event);
            viewPhotoshop (ctx);   
    }

    printf ("End\n");

    return 0;
}
