#ifndef STL_BRUSH
#define STL_BRUSH

#include "tool.hpp"
#include "../MVC/modelPhotoshop.hpp"

class ToolBrush : public Tool
{
private:
    ModelPhotoshop& modelPhotoshop;
    GraphicsCtx&    ctx;
    int size;
    Color color;

public:

    ToolBrush (ModelPhotoshop& init_modelPhotoshop, GraphicsCtx& init_ctx)
        :modelPhotoshop (init_modelPhotoshop), 
        ctx (init_ctx),
        size (15), color (0, 1, 1, 1)
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

        modelPhotoshop.setPixel ({x, y}, color, size, 0);
    }

    virtual void setColor (Color& new_color) override
    {
        color = new_color;
    }

    virtual void setSize (int new_size) override
    {
        size = new_size;
    }

};

#endif /* STL_BRUSH */