#include "modelButton.hpp"

/**************************************************************************/

ModelButton::ModelButton ()
{}

/**************************************************************************/

void ModelButton::addButton (Button button)
{
    buttons.push_back (button);
}

void ModelButton::update (sf::Vector2i pos)
{
    for (int i = 0; i < buttons.size(); i++)
    {
        Button& button = buttons[i];
        if (IsButton (pos, button))
        {
            for (size_t act = 0; act < button.actions.size(); act++)
            {
                (*button.actions[act])(); // отдельный метод
            }
        }
    }
}

/**************************************************************************/
