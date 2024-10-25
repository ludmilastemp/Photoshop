#include "GrLib.hpp"

#include <stdio.h>
#include <unistd.h>


GraphicsCtx::GraphicsCtx ()
    :window(sf::VideoMode(kWidthWindow * 2, kHeightWindow * 2), "SFML works!"), 
    event(), checkEvent(false)
{}

/**************************************************************************/

/*
// void DrawLine (Vector& v, Vector n, GraphicsCtx& ctx);

// void DrawLine (Vector& v, Vector n, GraphicsCtx& ctx)
// {
//     sf::Vertex line[] =
//     {
//         sf::Vertex(sf::Vector2f(kWidthWindow + n.getX(), kHeightWindow - n.getY())),
//         sf::Vertex(sf::Vector2f(kWidthWindow + n.getX() + v.getX(), kHeightWindow - n.getY() - v.getY()))
//     };

//     ctx.window.draw(line, 100, sf::Lines);
// }
*/

bool IsWindowOpen (GraphicsCtx& ctx)
{
    return ctx.window.isOpen();
}

void CheckEventCloseWindow (GraphicsCtx& ctx)
{
    if (ctx.checkEvent == true && ctx.event.type == sf::Event::Closed)
    {
        std::cout << "close window\n";
        ctx.window.close();
    }
}

void DisplayWindow (GraphicsCtx& ctx)
{          
    ctx.window.display();
}

void CleanWindow (GraphicsCtx& ctx)
{
    ctx.window.clear();
}

