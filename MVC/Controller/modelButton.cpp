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
    for (int i = 0; i < buttons.size(); i++)
    {
        Button& button = *(buttons[i]);
        if (button.getIsDraw () && 
            IsButton (pos, button))
        {
            // printf ("i = %d\n", i);
            for (size_t act = 0; act < button.actions.size(); act++)
            {
                (*button.actions[act])(event); // отдельный метод
            }
            return true;
        }
    }
    return false;
}

/**************************************************************************/
