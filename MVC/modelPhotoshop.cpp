#include "modelCanvas.hpp"

/**************************************************************************/

ModelPhotoshop::ModelPhotoshop (Scene& main_scene)
    : systemState(main_scene)
{}

/**************************************************************************/

void ModelPhotoshop::setActiveTool (int tool)
{
    toolbar.activate (tool);

    parameterManager.reActivate();
}

void ModelPhotoshop::addTool (Tool& tool)
{
    toolbar.add (tool);
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
    toolbar.setToolColor (color);
}

void ModelPhotoshop::setSize (int size)
{
    toolbar.setToolSize (size);
}

Color ModelPhotoshop::getColor ()
{
    return toolbar.getToolColor ();
}

int ModelPhotoshop::getSize ()
{
    return toolbar.getToolSize ();
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

    toolbar(event);

    systemState.base.update();
    systemState.tmp.update();
}

/**************************************************************************/
