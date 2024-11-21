#include "GrLib.hpp"

#include <stdio.h>
#include <unistd.h>


GraphicsCtx::GraphicsCtx ()
    :window(sf::VideoMode(kHalfWidthWindow * 2, kHalfHeightWindow * 2), "SFML works!"), 
    event (window)
{}

/**************************************************************************/

/*
// void DrawLine (Vector& v, Vector n, GraphicsCtx& ctx);

// void DrawLine (Vector& v, Vector n, GraphicsCtx& ctx)
// {
//     sf::Vertex line[] =
//     {
//         sf::Vertex(sf::Vector2f(kHalfWidthWindow + n.getX(), kHalfHeightWindow - n.getY())),
//         sf::Vertex(sf::Vector2f(kHalfWidthWindow + n.getX() + v.getX(), kHalfHeightWindow - n.getY() - v.getY()))
//     };

//     ctx.window.draw(line, 100, sf::Lines);
// }
*/

bool IsWindowOpen (GraphicsCtx& ctx)
{
    return ctx.window.isOpen();
}

bool CheckEventCloseWindow (GraphicsCtx& ctx)
{
    if (ctx.event.getWindowClose ())
    {
        std::cout << "close window\n";
        ctx.window.close();
        return 1;
    }
    return 0;
}

void DisplayWindow (GraphicsCtx& ctx)
{          
    ctx.window.display();
}

void CleanWindow (GraphicsCtx& ctx)
{
    ctx.window.clear();
}

