#include "button.hpp"

void DrawButton (const Button& button, GraphicsCtx& ctx);

/**************************************************************************/

Button::Button (const VectorDec& init_size, const VectorDec& init_corner, const char* png, Action& action)
    : Object(init_size, init_corner, png), 
    size(init_size), corner(init_corner)
{
    actions.push_back (&action);
}

/**************************************************************************/

void Button::setIsDraw (bool newDraw) 
{
    setIsDrawSimple (newDraw);

    if (newDraw)
    {
        for (size_t act = 0; act < actions.size(); act++)
        {
            actions[act]->active();
        }
    }
}

/**************************************************************************/

bool IsButton (const VectorDec& pos, const Button& button)
{
    return 
        button.corner.x <= pos.x && 
                           pos.x <= button.corner.x + button.size.x &&
        button.corner.y <= pos.y && 
                           pos.y <= button.corner.y + button.size.y;

}

/**************************************************************************/
