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
        size (14)
    {}

    virtual void active (sf::Event event) override
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            return;

        // int x_ = event.mouseMove.x - kWidthCanvasCorner;
        // int y_ = event.mouseMove.y - kHeightCanvasCorner;
        sf::Vector2i position = sf::Mouse::getPosition(ctx.window);
        int x = position.x - kWidthCanvasCorner;
        int y = position.y - kHeightCanvasCorner;

        if (0 <= x && x < kWidthCanvas && 
            0 <= y && y < kHeightCanvas)
        {
            for (int r_x = -size / 2; r_x < size / 2; r_x++)
            {
                for (int r_y = -size / 2; r_y < size / 2; r_y++)
                {
                    if (r_x * r_x + r_y * r_y <= size)
                    {
                        sf::Color color = 
                            modelPhotoshop.systemState.background.image.getPixel (x + r_x, y + r_y);
                        
                        modelPhotoshop.setPixel ({x + r_x, y + r_y}, 
                            // Color (0, 0, 0, 0));
                            Color (color.r / 255.0, color.g / 255.0, color.b / 255.0));
                    }
                }
            }
        }
    }

    // virtual void stop () override {}
};

#endif /* STL_ERASER */