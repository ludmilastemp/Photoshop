#include "modelButton.hpp"

/**************************************************************************/

ModelButton::ModelButton ()
{}

/**************************************************************************/

void ModelButton::addButton (Button& button)
{
    buttons.push_back (&button);
}

bool ModelButton::update (VectorDec pos, Event event)
{
    for (int i = buttons.size() - 1; i >= 0; i--)
    {
        Button& button = *(buttons[i]);
        if (button.getIsDraw () && 
            IsButton (pos, button))
        {
            // printf ("i = %d\n", i);
            bool check = false;
            event.coord.x -= button.corner.x;
            event.coord.y -= button.corner.y;
            for (size_t act = 0; act < button.actions.size(); act++)
            {
                check |= (*button.actions[act])(event); // отдельный метод
            }
            if (check)
                return true;
        }
    }
    return false;
}

/**************************************************************************/
