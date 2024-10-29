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

public:

    ToolBrush (ModelPhotoshop& init_modelPhotoshop, GraphicsCtx& init_ctx)
        :modelPhotoshop (init_modelPhotoshop), 
        ctx (init_ctx),
        size (200)
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

        modelPhotoshop.setPixel ({x, y}, Color (0, 1, 1, 1), size, 0);
    }
};

#endif /* STL_BRUSH */