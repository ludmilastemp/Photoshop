#ifndef STL_MODEL_BUTTON
#define STL_MODEL_BUTTON

#include "../../objects/button.hpp"

class ModelButton
{
public:
    std::vector <Button*> buttons;

    ModelButton ();

    bool operator() (VectorDec pos, Event event)
    {
        return update(pos, event);
    }

    void addButton (Button& button); 
    bool update (VectorDec pos, Event event);
};

#endif /* STL_MODEL_BUTTON */