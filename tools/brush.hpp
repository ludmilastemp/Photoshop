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
        size (14)
    {}

    virtual void active (sf::Event event) override
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return;

        int x = event.mouseMove.x - kWidthCanvasCorner;
        int y = event.mouseMove.y - kHeightCanvasCorner;

        if (0 <= x && x < kWidthCanvas && 
            0 <= y && y < kHeightCanvas)
        {
            for (int r_x = -size / 2; r_x < size / 2; r_x++)
            {
                for (int r_y = -size / 2; r_y < size / 2; r_y++)
                {
                    if (r_x * r_x + r_y * r_y <= size)
                        modelPhotoshop.setPixel ({x + r_x, y + r_y}, Color (0, 1, 1, 1));
                }
            }
        }
    }
};

#endif /* STL_BRUSH */