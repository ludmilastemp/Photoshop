#ifndef STL_BRUSH
#define STL_BRUSH

#include "tool.hpp"
#include "../MVC/modelCanvas.hpp"

class ToolBrush : public Tool
{
private:
    ModelCanvas& modelCanvas;
    GraphicsCtx&    ctx;
    int size;
    Color color;

public:

    ToolBrush (ModelCanvas& init_modelCanvas, GraphicsCtx& init_ctx)
        :modelCanvas (init_modelCanvas), 
        ctx (init_ctx),
        size (15), color (0, 1, 1, 1)
    {}

    virtual void apply (Event event) override
    {
        if (!event.getMousePressed ())
            return;

        int x = event.getCoord().x;
        int y = event.getCoord().y;

        modelCanvas.setPixel ({x, y}, color, size, kLaterActive);
    }

    virtual void setColor (Color& new_color) override
    {
        color = new_color;
    }

    virtual void setSize (int new_size) override
    {
        size = new_size;
    }

    virtual Color getColor () override
    {
        return color;
    }

    virtual int getSize () override
    {
        return size;
    }

};

#endif /* STL_BRUSH */