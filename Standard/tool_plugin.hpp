#ifndef STL_TOOL_PLUGIN
#define STL_TOOL_PLUGIN

#include "../objects/tool.hpp"
#include "../objects/filter.hpp"
#include "../MVC/modelCanvas.hpp"
#include "../plugins/PsSPI.hpp"
#include "../objects/actionClass.hpp"
#include "../objects/button.hpp"
#include <iostream>

class ToolPlugin : public Tool
{
private:
    ModelCanvas& modelCanvas;
    GraphicsCtx&    ctx;

public:
    PsSPI_Tool* tool;

    ToolPlugin (ModelCanvas& init_modelCanvas, GraphicsCtx& init_ctx)
        :modelCanvas (init_modelCanvas), 
        ctx (init_ctx)
    {}

    virtual void apply (Event event) override
    {
        if (!tool) return;
        tool->apply();
    }

    virtual void activate () override
    {
        if (!tool) return;
        parameterButtons.setIsDraw (true);
        tool->activate();
    }

    virtual void deactivate () override
    {
        if (!tool) return;
        parameterButtons.setIsDraw (false);
        tool->deactivate();
    }

    virtual void setColor (Color& color) override
    {
        if (!tool) return;
        tool->setColor({(uint8_t)(color.r * 255), 
                        (uint8_t)(color.g * 255), 
                        (uint8_t)(color.b * 255), 
                        (uint8_t)(color.a * 255)});
    }

    virtual Color getColor () override
    {
        if (!tool) return {0, 0, 0, 0};
        PsSPI_Color c = tool->getColor();
        return {(double)c.r / 255, 
                (double)c.g / 255, 
                (double)c.b / 255, 
                (double)c.a / 255};
    }
};

class ToolParameter : public Action
{
private:
    ModelCanvas& modelCanvas;
    GraphicsCtx&    ctx;

public:
    PsSPI_Parameter* param;

    ToolParameter (ModelCanvas& init_modelCanvas, GraphicsCtx& init_ctx)
        :modelCanvas (init_modelCanvas), 
        ctx (init_ctx)
    {}

    bool call (Event event)
    {
        Button& b = *(Button*)modelCanvas.parameterManager.objects[param->id]->objects[0];
        ctx.event.coord.x = event.coord.x;
        ctx.event.coord.y = event.coord.y;
        param->activate();
        return true;
    }
};

class FilterPlugin : public Filter
{
private:
    ModelCanvas& modelCanvas;
    GraphicsCtx&    ctx;

public:
    PsSPI_Filter* filter;

    FilterPlugin (ModelCanvas& init_modelCanvas, GraphicsCtx& init_ctx)
        :modelCanvas (init_modelCanvas), 
        ctx (init_ctx)
    {}

    virtual void apply (Event event) override
    {
        if (!filter) return;
        filter->apply();
    }

    virtual void activate () override
    {
        if (!filter) return;
        parameterButtons.setIsDraw (true);
        filter->activate();
    }

    virtual void deactivate () override
    {
        if (!filter) return;
        parameterButtons.setIsDraw (false);
        filter->deactivate();
    }
};

#endif /* STL_TOOL_PLUGIN */