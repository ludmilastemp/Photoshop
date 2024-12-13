#ifndef STL_TOOL_PLUGIN
#define STL_TOOL_PLUGIN

#include "../tools/tool.hpp"
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
        modelCanvas.parameterManager.deactivate();
        tool->deactivate();
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

    void call (Event event)
    {
        Button& b = *(Button*)modelCanvas.parameterManager.objects[param->id]->objects[0];
        ctx.event.coord.x = event.coord.x;
        ctx.event.coord.y = event.coord.y;
        param->activate();
    }
};


#endif /* STL_TOOL_PLUGIN */