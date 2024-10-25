#ifndef STL_GrLibCtx
#define STL_GrLibCtx

#include <SFML/Graphics.hpp>

const int kWidthWindow  = 800 / 2;
const int kHeightWindow = 550 / 2;

const int kWidthCanvas  = 600;
const int kHeightCanvas = 400;

const int kWidthCanvasCorner  = 100;
const int kHeightCanvasCorner = 100;

const int kWidthIcon  = 50;
const int kHeightIcon = 50;

class GraphicsCtx
{
public:
    sf::RenderWindow window;
    sf::Event event;
    bool checkEvent;

    GraphicsCtx ();
};

#endif /* STL_GrLibCtx */