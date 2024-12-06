#include "modelCanvas.hpp"
#include <iostream>

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

static Picture& getLayer (ModelCanvas& modelCanvas, int layer)
{
    if (layer == kLaterTmp) 
        return modelCanvas.systemState.tmp;
    if (layer == kLaterActive) 
        return modelCanvas.systemState.base; 
    if (layer >= 100 && layer - 100 < modelCanvas.pluginLayers.size())
        return *modelCanvas.pluginLayers[layer - 100];
    if (layer >= 300 && layer - 300 < modelCanvas.pluginParamLayers.size())
        return *modelCanvas.pluginParamLayers[layer - 300];
    return modelCanvas.systemState.tmp;
}

static VectorDec getCoordLayer (ModelCanvas& modelCanvas, int layer, VectorDec coord)
{
    // std::cout << coord.x << " " << coord.y << "\n";
    if (layer == kLaterTmp ||
        layer == kLaterActive) 
    {
        coord.x /= modelCanvas.scale;
        coord.y /= modelCanvas.scale;
        coord.x += modelCanvas.x_canvas;
        coord.y += modelCanvas.y_canvas;
    }

    // std::cout << coord.x << " " << coord.y << "\n";
    return coord; 
}

void ModelCanvas::cleanLayer (int layer)
{
    std::cout << "cleanLayer " << layer << "\n";
    Picture& p = getLayer (*this, layer);
    p.clean ();
}

void ModelCanvas::updateLayer (int layer)
{
    std::cout << "updateLayer " << layer << "\n";
    Picture& p = getLayer (*this, layer);
    p.update ();
}

void ModelCanvas::setPixel (VectorDec coord, Color color, int size, int layer)
{
    Picture& p = getLayer (*this, layer);

    for (int r_x = -size + 1; r_x < size; r_x++)
    {
        for (int r_y = -size + 1; r_y < size; r_y++)
        {
            if (r_x * r_x + r_y * r_y <= size * size               &&
                0 <= coord.x + r_x && coord.x + r_x < p.getSize().x && 
                0 <= coord.y + r_y && coord.y + r_y < p.getSize().y)
            {
                p.setPixel (coord.x + r_x, coord.y + r_y, color);
            }
        }
    }
}

Color ModelCanvas::getPixel (VectorDec coord, int layer)
{
    Picture& p = getLayer (*this, layer);

    if (0 <= coord.x && coord.x < p.getSize().x && 
        0 <= coord.y && coord.y < p.getSize().y)
    {
        return p.getPixel (coord.x, coord.y);
    }
    return {0, 0, 0, 1};
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

    event.coord.x -= kWidthCanvasCorner;
    event.coord.y -= kHeightCanvasCorner;
    toolbar(event);

    systemState.base.update();
    systemState.tmp.update();
}

/**************************************************************************/
