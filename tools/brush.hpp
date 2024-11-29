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

    ToolBrush (ModelCanvas& init_modelPhotoshop, GraphicsCtx& init_ctx)
        :modelCanvas (init_modelPhotoshop), 
        ctx (init_ctx),
        size (15), color (0, 1, 1, 1)
    {}

    virtual void apply (Event event) override
    {
        if (!event.getMousePressed ())
            return;

        int x = event.getCoord().x - kWidthCanvasCorner;
        int y = event.getCoord().y - kHeightCanvasCorner;

        modelCanvas.setPixel ({x, y}, color, size, 0);
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