#include "modelCanvas.hpp"

/**************************************************************************/

ModelCanvas::ModelCanvas (Scene& main_scene)
    : systemState(main_scene), scale(1), x_canvas(0), y_canvas(0)
{}

/**************************************************************************/

void ModelCanvas::setActiveTool (int tool)
{
    toolbar.activate (tool);

    parameterManager.reActivate();
}

void ModelCanvas::addTool (Tool& tool)
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

void ModelCanvas::setPixel (VectorDec coord, Color color, int size, int layer)
{
    coord.x /= scale;
    coord.y /= scale;
    coord.x += x_canvas;
    coord.y += y_canvas;

    Picture& p = getLayer (systemState, layer);

    for (int r_x = -size; r_x < size; r_x++)
    {
        for (int r_y = -size; r_y < size; r_y++)
        {
            if (r_x * r_x + r_y * r_y <= size * size               &&
                0 <= coord.x + r_x && coord.x + r_x < kWidthCanvas && 
                0 <= coord.y + r_y && coord.y + r_y < kHeightCanvas)
            {
                p.setPixel (coord.x + r_x, coord.y + r_y, color);
            }
        }
    }
}

Color ModelCanvas::getColor ()
{
    return toolbar.getToolColor ();
}

void ModelCanvas::setColor (Color color)
{
    toolbar.setToolColor (color);
}

int ModelCanvas::getSize ()
{
    return toolbar.getToolSize ();
}

void ModelCanvas::setSize (int size)
{
    toolbar.setToolSize (size);
}

int ModelCanvas::getShiftX ()
{
    return x_canvas;
}

void ModelCanvas::setShiftX (int shiftX)
{
    x_canvas = shiftX;

    systemState.background.setScale (scale, x_canvas, y_canvas);
    systemState.base      .setScale (scale, x_canvas, y_canvas);
    systemState.tmp       .setScale (scale, x_canvas, y_canvas);
}

int ModelCanvas::getShiftY ()
{
    return y_canvas;
}

void ModelCanvas::setShiftY (int shiftY)
{
    y_canvas = shiftY;

    systemState.background.setScale (scale, x_canvas, y_canvas);
    systemState.base      .setScale (scale, x_canvas, y_canvas);
    systemState.tmp       .setScale (scale, x_canvas, y_canvas);
}

double ModelCanvas::getScale ()
{
    return scale;
}

void ModelCanvas::setScale (double new_scale)
{
    scale = new_scale;
    printf ("set scale %lg\n", scale);

    systemState.background.setScale (scale, x_canvas, y_canvas);
    systemState.base      .setScale (scale, x_canvas, y_canvas);
    systemState.tmp       .setScale (scale, x_canvas, y_canvas);
}

void ModelCanvas::UpdateImage ()
{
    systemState.base.overlay(systemState.tmp);
    systemState.tmp.clean();
}

/**************************************************************************/

void ModelCanvas::update (Event& event)
{
    if (event.getType () == -1)
        event.setType (Event::event_model);
    if (event.getType () != Event::event_model) return;

    toolbar(event);

    systemState.base.update();
    systemState.tmp.update();
}

/**************************************************************************/
