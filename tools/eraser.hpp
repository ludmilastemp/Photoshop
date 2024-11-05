#ifndef STL_ERASER
#define STL_ERASER

#include "tool.hpp"
#include "../MVC/modelPhotoshop.hpp"

class ToolEraser : public Tool
{
private:
    ModelPhotoshop& modelPhotoshop;
    GraphicsCtx&    ctx;
    int size;

public:

    ToolEraser (ModelPhotoshop& init_modelPhotoshop, GraphicsCtx& init_ctx)
        :modelPhotoshop (init_modelPhotoshop), 
        ctx (init_ctx),
        size (28)
    {}

    virtual void active (Event event) override
    {
        if (!event.getMousePressed ())
            return;

        int x = event.getCoord().x - kWidthCanvasCorner;
        int y = event.getCoord().y - kHeightCanvasCorner;

        modelPhotoshop.setPixel ({x, y}, Color (0, 0, 0, 0), size, 0);
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