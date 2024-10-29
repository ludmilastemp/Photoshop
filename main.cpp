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
    int i = 0;

    GraphicsCtx ctx {};

/*
 * MVC photoshop
 */
    ModelPhotoshop modelPhotoshop {};
    ViewPhotoshop  viewPhotoshop  {modelPhotoshop.systemState};

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
    ViewButton  viewButton  {&modelButton.buttons}; 

/*
 * Создание кнопок
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

/*
 * Создание контроллера для photoshop
 */
    ControllerPhotoshop controllerPhotoshop {modelButton, viewButton};

/*
 * Начало программы
 */

    while (IsWindowOpen(ctx))
    {
        i++;
        // if (i == 300) { printf ("End\n"); return 0; }
        
        assert (ctx.checkEvent == false);

        if (ctx.window.pollEvent(ctx.event)) 
            ctx.checkEvent = true;
        if (CheckEventCloseWindow (ctx)) break;

        if (ctx.window.pollEvent(ctx.event)) 
            ctx.checkEvent = true;
        if (CheckEventCloseWindow (ctx)) break;

        CleanWindow (ctx);

        /*
         * MVC
         */ 
            controllerPhotoshop (ctx); 
            modelPhotoshop (ctx.event);
            viewPhotoshop (ctx);   

        DisplayWindow(ctx);                                                                                                sf::sleep (sf::seconds(0.01));
    }

    printf ("End\n");

    return 0;

}
