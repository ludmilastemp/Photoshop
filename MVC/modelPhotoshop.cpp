#include "modelPhotoshop.hpp"

/**************************************************************************/

ModelPhotoshop::ModelPhotoshop (Scene& main_scene)
    : systemState(main_scene), 
    activeTool (-1)
{}

/**************************************************************************/

void ModelPhotoshop::setActiveTool (int tool)
{
    if (0 <= activeTool && activeTool < tools.size())
        (*tools[activeTool]).stop();

    if (-1 <= tool && tool < tools.size())
        activeTool = tool;
    else 
        std::cout << "UNKNOWN TOOL\n";
}

void ModelPhotoshop::addTool (Tool& tool)
{
    tools.push_back (&tool);
}

static Picture& getLayer (SystemState& systemState, int layer)
{
    if (layer == -1) 
        return systemState.tmp;
    if (layer == 0) 
        return systemState.base; 
    return systemState.tmp;
}

void ModelPhotoshop::setPixel (VectorDec coord, Color color, int size, int layer)
{
    Picture& p = getLayer (systemState, layer);

    for (int r_x = -size; r_x < size; r_x++)
    {
        for (int r_y = -size; r_y < size; r_y++)
        {
            if (r_x * r_x + r_y * r_y <= size * size      &&
                0 <= coord.x + r_x && coord.x + r_x < kWidthCanvas && 
                0 <= coord.y + r_y && coord.y + r_y < kHeightCanvas)
            {
                p.setPixel ({coord.x + r_x, coord.y + r_y}, color);
            }
        }
    }
}

void ModelPhotoshop::setColor (Color color)
{
    if (0 <= activeTool && activeTool < tools.size())
        (*tools[activeTool]).setColor(color);
}

void ModelPhotoshop::setSize (int size)
{
    if (0 <= activeTool && activeTool < tools.size())
        (*tools[activeTool]).setSize(size);
}

void ModelPhotoshop::UpdateImage ()
{
    systemState.base.overlay(systemState.tmp);
    systemState.tmp.clean();
}

/**************************************************************************/

void ModelPhotoshop::update (sf::Event event)
{
    if (0 <= activeTool && activeTool < tools.size())
    {
        (*tools[activeTool])(event);
    }

    systemState.base.update();
    systemState.tmp.update();
}

/**************************************************************************/
