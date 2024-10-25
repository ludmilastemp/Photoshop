#include <iostream>

#include <SFML/Graphics.hpp>

#include "GrLib/GrLib.hpp"
#include "MVC/controllerPhotoshop.hpp"
#include "MVC/modelPhotoshop.hpp"
#include "MVC/viewPhotoshop.hpp"
#include "tools/brush.hpp"
#include "tools/eraser.hpp"

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
    modelPhotoshop.addTool (brush);
    modelPhotoshop.addTool (eraser);

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

    Button buttonBrush  {{kWidthIcon, kHeightIcon}, {25, 100}, "img/brush.png", actionBrush};
    Button buttonEraser {{kWidthIcon, kHeightIcon}, {25, 160}, "img/eraser.png", actionEraser};

    modelButton.addButton (buttonBrush);
    modelButton.addButton (buttonEraser);

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
        
        if (/**/ctx.checkEvent == false &&/**/ ctx.window.pollEvent(ctx.event))
        {
            // std::cout << "pollEvent\n";
            ctx.checkEvent = true;
        }

        CheckEventCloseWindow (ctx);

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
