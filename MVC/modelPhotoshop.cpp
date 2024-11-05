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
    {
        (*tools[activeTool]).stop();
    }

    if (-1 <= tool && tool < tools.size())
    {
        activeTool = tool;
    }
    else 
        std::cout << "UNKNOWN TOOL\n";
    
    parameterManager.reActivate();
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
                p.setPixelPictureTmp ({coord.x + r_x, coord.y + r_y}, color);
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

Color ModelPhotoshop::getColor ()
{
    if (0 <= activeTool && activeTool < tools.size())
        return (*tools[activeTool]).getColor();
    return {1, 1, 1, 1};
}

int ModelPhotoshop::getSize ()
{
    if (0 <= activeTool && activeTool < tools.size())
        return (*tools[activeTool]).getSize();
    return 0;
}

void ModelPhotoshop::UpdateImage ()
{
    systemState.base.overlay(systemState.tmp);
    systemState.tmp.clean();
}

/**************************************************************************/

void ModelPhotoshop::update (Event& event)
{
    if (event.getType () == -1)
        event.setType (Event::event_model);
    if (event.getType () != Event::event_model) return;

    if (0 <= activeTool && activeTool < tools.size())
    {
        (*tools[activeTool])(event);
    }

    systemState.base.update();
    systemState.tmp.update();
}

/**************************************************************************/
