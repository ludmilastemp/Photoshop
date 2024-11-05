#include "toolbar.hpp"

/**************************************************************************/

void Toolbar::add (Tool& tool)
{
    tools.push_back(&tool);
}

void Toolbar::activate (int tool)
{
    deActivate ();

    if (-1 <= tool && tool < tools.size())
    {
        activeTool = tool;
    }
}

void Toolbar::deActivate ()
{
    if (0 <= activeTool && activeTool < tools.size())
    {
        (*tools[activeTool]).stop();
    }
    activeTool = -1;
}

void Toolbar::update (Event& event)
{
    if (0 <= activeTool && activeTool < tools.size())
    {
        (*tools[activeTool])(event);
    }
}

/**************************************************************************/

void Toolbar::setToolColor (Color color)
{
    if (0 <= activeTool && activeTool < tools.size())
        (*tools[activeTool]).setColor(color);
}

void Toolbar::setToolSize (int size)
{
    if (0 <= activeTool && activeTool < tools.size())
        (*tools[activeTool]).setSize(size);
}

Color Toolbar::getToolColor ()
{
    if (0 <= activeTool && activeTool < tools.size())
        return (*tools[activeTool]).getColor();
    return {1, 1, 1, 1};
}

int Toolbar::getToolSize ()
{
    if (0 <= activeTool && activeTool < tools.size())
        return (*tools[activeTool]).getSize();
    return 0;
}

/**************************************************************************/