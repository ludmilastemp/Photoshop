#include "modelPhotoshop.hpp"

/**************************************************************************/

ModelPhotoshop::ModelPhotoshop ()
    : systemState(), 
    activeTool (-1)
{}

/**************************************************************************/

void ModelPhotoshop::setActiveTool (int tool)
{
    if (0 <= activeTool && activeTool <= tools.size())
        (*tools[activeTool]).stop();
    UpdateImage ();
    if (tool >= -1 && tool <= tools.size())
        activeTool = tool;
}

void ModelPhotoshop::addTool (Tool& tool)
{
    tools.push_back (&tool);
}

void ModelPhotoshop::setPixel (VectorDec coord, Color color)
{
    systemState.tmp.setPixel ({coord.x, coord.y}, color);
}

void ModelPhotoshop::UpdateImage ()
{
    systemState.base.overlay(systemState.tmp);
    systemState.tmp.clean();
}

/**************************************************************************/

void ModelPhotoshop::update (sf::Event event)
{
    static int x = 0;
    static int y = 0;

    if (y == x) { x++; y = 0; }
    
    // setPixel ({x + 330, y + 220}, Color(0, 1, 1, 0.3));
    y++;

    if (0 <= activeTool && activeTool < tools.size())
    {
        (*tools[activeTool])(event);
    }

    systemState.tmp.update();
}

/**************************************************************************/
