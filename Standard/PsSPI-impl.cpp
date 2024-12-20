#include "PsSPI-impl.hpp"
#include "PsSPI.hpp"

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

    const char* pngIcon = param->img_icon;
    Button* buttonIcon = new Button {{kWidthParam, kHeightParam}, {kWidthParameterManagerCorner + (int)tool.nParameters * (kHeightParam + kOffsetParam), kHeightParameterManagerCorner}, pngIcon};
    tool.parameterButtons.addObject (*buttonIcon);

    VectorDec size = {param->x, param->y};
    const char* png = param->img_act;

    ToolParameter* action = new ToolParameter {modelCanvas, ctx};
    action->param = param;

    int id_layer = modelCanvas.createPluginParamPicture (size, {kWidthParameterManagerCorner + (int)tool.nParameters * (kHeightParam + kOffsetParam), kCanvasYBegin}, png);
    Button* button = new Button {size, {kWidthParameterManagerCorner + (int)tool.nParameters * (kHeightParam + kOffsetParam), kCanvasYBegin}, *action, png};
    modelPhotoshop.modelButton.addButton (*button);

    Scene* sceneParameter = new Scene {};
    sceneParameter->addObject (*button);
    sceneParameter->addObject (*modelCanvas.pluginParamLayers[id_layer - 300]);
    sceneParameter->setIsDraw (false);

    modelPhotoshop.main_scene.addScene (*sceneParameter);        
    
    printf ("parameterManager %lu fill\n", modelCanvas.parameterManager.objects.size());

    modelCanvas.parameterManager.add   (*sceneParameter);
    tool.parametersIndex.push_back(modelCanvas.parameterManager.objects.size() - 1);

    param->id = tool.nParameters; 
    param->layer = id_layer;
    
    tool.nParameters++;
}

void StlPsSPI::addFilter (PsSPI_Filter* filter)
{
    FilterPlugin* new_filter = new FilterPlugin {modelCanvas, ctx};
    new_filter->filter = filter;
    pl_filters.push_back (new_filter);

    modelPhotoshop.addFilter (*new_filter, filter->img);
    filter->id = pl_filters.size() - 1;

    modelPhotoshop.main_scene.addScene (new_filter->setting);
}

void StlPsSPI::addFilterSetting (filter_t id, PsSPI_FilterSetting* setting)
{
    // Tool& tool = *modelCanvas.toolbar.objects[id];

    // const char* pngIcon = param->img_icon;
    // Button* buttonIcon = new Button {{kWidthParam, kHeightParam}, {kCanvasXEnd - size.x, kHeightParameterManagerCorner}, pngIcon};
    // tool.parameterButtons.addObject (*buttonIcon);

    Filter& filter = *modelPhotoshop.filtres[id];

    VectorDec size = {setting->x, setting->y};
    const char* png = setting->img_act;

    ActionFilterSetting* action = new ActionFilterSetting {modelPhotoshop, modelCanvas, ctx};
    action->setting = setting;

    int id_layer = modelCanvas.createPluginParamPicture (size, {kCanvasXEnd - size.x, kCanvasYBegin}, png);
    Button* button = new Button {size, {kCanvasXEnd - size.x, kCanvasYBegin}, *action, png};
    modelPhotoshop.modelButton.addButton (*button);

    filter.setting.addObject (*button);
    filter.setting.addObject (*modelCanvas.pluginParamLayers[id_layer - 300]);
    filter.setting.setIsDraw (false);
    
    // printf ("parameterManager %lu fill\n", modelCanvas.parameterManager.objects.size());

    // modelCanvas.parameterManager.add   (*sceneParameter);
    // tool.parametersIndex.push_back(modelCanvas.parameterManager.objects.size() - 1);

    setting->id = filter.nParameters; 
    setting->layer = id_layer;
    
    filter.nParameters++;
}

void StlPsSPI::closeFilter (filter_t id)
{    
    Filter& filter = *modelPhotoshop.filtres[id];
    filter.deactivate();
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
    modelCanvas.overlayLayer (foreground);
}

void StlPsSPI::overlayLayer (layer_t foreground, layer_t background) 
{
    modelCanvas.overlayLayer (foreground, background);
}

void StlPsSPI::setColor (PsSPI_Color color)
{
    Color my_color = {(double)color.r, (double)color.g, (double)color.b, (double)color.a};
    modelCanvas.setColor (my_color / 255);
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
