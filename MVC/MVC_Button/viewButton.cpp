#include "viewButton.hpp"

/**************************************************************************/

ViewButton::ViewButton (std::vector <Button>* init_buttons)
    :buttons (init_buttons)
{}

/**************************************************************************/

void ViewButton::update (GraphicsCtx& ctx)
{
    assert (buttons);
    for (int i = 0; i < buttons->size(); i++)
    {
        ctx.window.draw ((*buttons)[i].sprite);
    }
}

/**************************************************************************/
