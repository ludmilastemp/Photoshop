#ifndef STL_GrLibCtx
#define STL_GrLibCtx

#include <SFML/Graphics.hpp>
#include "../vectors/vectorDec.hpp"

const int kWidthWindow  = 800 / 2;
const int kHeightWindow = 550 / 2;

const int kWidthCanvas  = 600;
const int kHeightCanvas = 400;

const int kWidthCanvasCorner  = 100;
const int kHeightCanvasCorner = 100;

const int kWidthIcon  = 50;
const int kHeightIcon = 50;

class Event
{
private:
    sf::Event event;
    sf::RenderWindow& window;

    int type;
    bool windowClose;
    bool mousePressed;
    VectorDec coord;
public:

    enum
    {
        event_controller = 1,
        event_model      = 2,
    };


    Event (sf::RenderWindow& init_window)
        :window(init_window), windowClose(false), mousePressed(false), type(-1)
    {}

    bool update ()
    {
        bool ret = false;
        while (window.pollEvent(event)) 
        {
            int type_old = type;
            type = -1;
            if (event.type == sf::Event::Closed) 
                windowClose = true;
            else if (event.type == sf::Event::MouseButtonPressed) 
                mousePressed = true;
            else if (event.type == sf::Event::MouseButtonReleased) 
                mousePressed = false;
            else 
                type = type_old;

            ret = true;
        }

        sf::Vector2i position = sf::Mouse::getPosition(window);
        coord.x = position.x;
        coord.y = position.y;

        return ret;
    }

    bool operator () ()
    {
        return update ();
    }

    bool getWindowClose () { return windowClose; }
    bool getMousePressed () { return mousePressed; }
    VectorDec getCoord () { return coord; }
    int getType () { return type; }
    void setType (int new_type) { type = new_type; }
};

class GraphicsCtx
{
public:
    sf::RenderWindow window;
    Event event;

    GraphicsCtx ();
};

#endif /* STL_GrLibCtx */