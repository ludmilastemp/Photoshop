#ifndef STL_MODEL_BUTTON
#define STL_MODEL_BUTTON

#include "../../objects/button.hpp"

class ModelButton
{
public:
    std::vector <Button> buttons;

    ModelButton ();

    void operator() (sf::Vector2i pos)
    {
        update(pos);
    }

    void addButton (Button button); 
    void update (sf::Vector2i pos);
};

#endif /* STL_MODEL_BUTTON */