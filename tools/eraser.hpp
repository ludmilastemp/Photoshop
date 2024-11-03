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
        size (18)
    {}

    virtual void active (sf::Event event) override
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return;

        // int x = event.mouseMove.x - kWidthCanvasCorner;
        // int y = event.mouseMove.y - kHeightCanvasCorner;
        sf::Vector2i position = sf::Mouse::getPosition(ctx.window);
        int x = position.x - kWidthCanvasCorner;
        int y = position.y - kHeightCanvasCorner;

        modelPhotoshop.setPixel ({x, y}, Color (0, 0, 0, 0), size, 0);
    }

    virtual void setSize (int new_size) override
    {
        size = new_size;
    }

};

#endif /* STL_ERASER */