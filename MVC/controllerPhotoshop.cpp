#include "controllerPhotoshop.hpp"

/**************************************************************************/

ControllerPhotoshop::ControllerPhotoshop (ModelButton& init_modelButton)
    : modelButton(init_modelButton)
{}

/**************************************************************************/

void ControllerPhotoshop::update (GraphicsCtx& ctx)
{
    sf::Vector2i pos = sf::Mouse::getPosition(ctx.window);
    
    if (ctx.checkEvent == true &&
        ctx.event.type == sf::Event::MouseButtonPressed &&
        ctx.event.mouseButton.button == sf::Mouse::Left)
    {
        // printf ("Mouse button pressed\n");
        modelButton (pos);
    }

    ctx.checkEvent = false;
}

/**************************************************************************/
