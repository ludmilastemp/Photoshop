#include "toolbar.hpp"

/**************************************************************************/

void Toolbar::update (Event& event)
{
    if (0 <= activeObject && activeObject < objects.size())
    {
        (*objects[activeObject])(event);
    }
}

void Toolbar::setToolColor (Color color)
{
    if (0 <= activeObject && activeObject < objects.size())
        (*objects[activeObject]).setColor(color);
}

void Toolbar::setToolSize (int size)
{
    if (0 <= activeObject && activeObject < objects.size())
        (*objects[activeObject]).setSize(size);
}

Color Toolbar::getToolColor ()
{
    if (0 <= activeObject && activeObject < objects.size())
        return (*objects[activeObject]).getColor();
    return {1, 1, 1, 1};
}

int Toolbar::getToolSize ()
{
    if (0 <= activeObject && activeObject < objects.size())
        return (*objects[activeObject]).getSize();
    return 0;
}

/**************************************************************************/