#include "PsSPI-impl.hpp"

void StlPsSPI::addTool (PsSPI_Tool* tool)
{
    ToolPlugin* new_tool = new ToolPlugin {modelCanvas, ctx};
    new_tool->tool = tool;
    pl_tools.push_back (new_tool);

    modelPhotoshop.addTool (*new_tool, tool->img);
    tool->id = pl_tools.size() - 1;

    modelPhotoshop.main_scene.addScene (new_tool->parameterButtons);
}

void StlPsSPI::addParameter (tool_t id, PsSPI_Parameter* param)
{
    Tool& tool = *modelCanvas.toolbar.objects[id];

    VectorDec size = {param->x, param->y};
    const char* png = param->img_act;
    const char* pngIcon = param->img_icon;

    ToolParameter* action = new ToolParameter {modelCanvas, ctx};
    action->param = param;

    int id_layer = modelCanvas.createPluginParamPicture (size, {kCanvasXEnd - size.x, kCanvasYBegin}, png);
    Button* button = new Button {size, {kCanvasXEnd - size.x, kCanvasYBegin}, *action, png};
    modelPhotoshop.modelButton.addButton (*button);

    Scene* sceneParameter = new Scene {};
    sceneParameter->addObject (*button);
    sceneParameter->addObject (*modelCanvas.pluginParamLayers[id_layer - 300]);
    sceneParameter->setIsDraw (false);

    modelPhotoshop.main_scene.addScene (*sceneParameter);
    modelCanvas.parameterManager.add   (*sceneParameter);
    tool.parametersIndex.push_back(modelCanvas.parameterManager.objects.size() - 1);

    Button* buttonIcon = new Button {{kWidthIcon, kHeightIcon}, {kWidthParameterManagerCorner, kHeightParameterManagerCorner + (int)tool.nParameters * (kHeightIcon + kOffsetIcon)}, pngIcon};
    tool.parameterButtons.addObject (*buttonIcon);

    param->id = tool.nParameters; 
    param->layer = id_layer;
    
    tool.nParameters++;
}

PsSPI_Event StlPsSPI::getEvent ()
{
    return {.mousePressed = ctx.event.getMousePressed(),
            .mouseCoordX  = ctx.event.getCoord().x,
            .mouseCoordY  = ctx.event.getCoord().y};
}

layer_t StlPsSPI::createLayer ()
{
    return modelCanvas.createPluginPicture();
}

layer_t StlPsSPI::createParamLayer (tool_t id, param_t param_id)
{
    param_t param_id_abs = modelCanvas.toolbar.objects[id]->parametersIndex[param_id];
    Button& b = *(Button*)modelCanvas.parameterManager.objects[param_id_abs]->objects[0];
    layer_t l = modelCanvas.createPluginParamPicture(b.size, b.corner);
    modelCanvas.parameterManager.objects[param_id_abs]->addObject (*modelCanvas.pluginParamLayers[l - 300]);
    return l;
}

void StlPsSPI::cleanLayer ()
{
    modelCanvas.systemState.base.clean();
}

void StlPsSPI::cleanLayer (layer_t layer)
{
    modelCanvas.cleanLayer (layer);
}

void StlPsSPI::overlayLayer (layer_t foreground) 
{
    if (foreground == kLaterTmp)
        modelCanvas.UpdateImage ();
}

void StlPsSPI::overlayLayer (layer_t foreground, layer_t background) 
{
    if (foreground == kLaterTmp && background == kLaterActive)
        modelCanvas.UpdateImage ();
}

PsSPI_Color StlPsSPI::getPixel (int x, int y)
{
    Color my_color = modelCanvas.getPixel ({x, y});
    return {(unsigned char) (my_color.r * 255), 
            (unsigned char) (my_color.g * 255), 
            (unsigned char) (my_color.b * 255), 
            (unsigned char) (my_color.a * 255) };
}

PsSPI_Color StlPsSPI::getPixel (layer_t layer, int x, int y)
{
    Color my_color = {0, 0, 0, 1};
    my_color = modelCanvas.getPixel ({x, y}, layer);
    return {(unsigned char) (my_color.r * 255), 
            (unsigned char) (my_color.g * 255), 
            (unsigned char) (my_color.b * 255), 
            (unsigned char) (my_color.a * 255) }; 
}

void StlPsSPI::setPixel (int x, int y, PsSPI_Color color, int size)
{
    Color my_color = {(double)color.r, (double)color.g, (double)color.b, (double)color.a};
    modelCanvas.setPixel ({x, y}, my_color / 255, size, kLaterActive);
}

void StlPsSPI::setPixel (layer_t layer, int x, int y, PsSPI_Color color, int size)
{
    Color my_color = {(double)color.r, (double)color.g, (double)color.b, (double)color.a};
    modelCanvas.setPixel ({x, y}, my_color / 255, size, layer);
}

void StlPsSPI::updateLayer (layer_t layer)
{
    modelCanvas.updateLayer (layer);
}
