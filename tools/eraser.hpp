#ifndef STL_ERASER
#define STL_ERASER

#include "tool.hpp"
#include "../MVC/modelCanvas.hpp"

class ToolEraser : public Tool
{
private:
    ModelCanvas& modelCanvas;
    GraphicsCtx&    ctx;
    int size;

public:

    ToolEraser (ModelCanvas& init_modelPhotoshop, GraphicsCtx& init_ctx)
        :modelCanvas (init_modelPhotoshop), 
        ctx (init_ctx),
        size (28)
    {}

    virtual void apply (Event event) override
    {
        if (!event.getMousePressed ())
            return;

        int x = event.getCoord().x;
        int y = event.getCoord().y;

        modelCanvas.setPixel ({x, y}, Color (0, 0, 0, 0), size, kLaterActive);
    }

    virtual void setSize (int new_size) override
    {
        size = new_size;
    }

    virtual int getSize () override
    {
        return size;
    }
};

#endif /* STL_ERASER */