#include "controllerPhotoshop.hpp"

/**************************************************************************/

ControllerPhotoshop::ControllerPhotoshop (ModelButton& init_modelButton)
    : modelButton(init_modelButton)
{}

/**************************************************************************/

bool ControllerPhotoshop::update (GraphicsCtx& ctx)
{
    if (ctx.checkEvent == true &&
        ctx.event.type == sf::Event::MouseButtonPressed &&
        ctx.event.mouseButton.button == sf::Mouse::Left)
    {
        // printf ("Mouse button pressed\n");
        VectorDec pos = {
            ctx.event.mouseButton.x,
            ctx.event.mouseButton.y };

        ctx.checkEvent = false;
        return modelButton (pos, ctx.event);
    }

    ctx.checkEvent = false;
    return false;
}

/**************************************************************************/
