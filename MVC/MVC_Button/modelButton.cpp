#include "modelButton.hpp"

/**************************************************************************/

ModelButton::ModelButton ()
{}

/**************************************************************************/

void ModelButton::addButton (Button& button)
{
    buttons.push_back (&button);
}

bool ModelButton::update (VectorDec pos, sf::Event event)
{
    for (int i = 0; i < buttons.size(); i++)
    {
        Button& button = *(buttons[i]);
        if (button.isDraw && 
            IsButton (pos, button))
        {
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
