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

    for (int r_x = -size / 2; r_x < size / 2; r_x++)
    {
        for (int r_y = -size / 2; r_y < size / 2; r_y++)
        {
            if (r_x * r_x + r_y * r_y <= size          &&
                0 <= coord.x + r_x && coord.x + r_x < kWidthCanvas && 
                0 <= coord.y + r_y && coord.y + r_y < kHeightCanvas)
            {
                p.setPixel ({coord.x + r_x, coord.y + r_y}, color);
            }
        }
    }
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

    systemState.base.update();
    systemState.tmp.update();
}

/**************************************************************************/
