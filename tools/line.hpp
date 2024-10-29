#ifndef STL_LINE
#define STL_LINE

#include "tool.hpp"
#include "../MVC/modelPhotoshop.hpp"

class ToolLine : public Tool
{
private:
    ModelPhotoshop& modelPhotoshop;
    GraphicsCtx&    ctx;
    int size;
    int x_start;
    int y_start;

public:

    ToolLine (ModelPhotoshop& init_modelPhotoshop, GraphicsCtx& init_ctx)
        :modelPhotoshop (init_modelPhotoshop), 
        ctx (init_ctx),
        size (2), 
        x_start(-1), 
        y_start(-1)
    {}

    virtual void active (sf::Event event) override
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            modelPhotoshop.UpdateImage ();
            x_start = -1;
            y_start = -1;
            return;
        }

        // int x = event.mouseMove.x - kWidthCanvasCorner;
        // int y = event.mouseMove.y - kHeightCanvasCorner;
        sf::Vector2i position = sf::Mouse::getPosition(ctx.window);
        int x = position.x - kWidthCanvasCorner;
        int y = position.y - kHeightCanvasCorner;

        if (0 <= x && x < kWidthCanvas && 
            0 <= y && y < kHeightCanvas)
        {
            if (x_start == -1 && y_start == -1)
            {
                x_start = x;
                y_start = y;
                std::cout << x << " " << y << "\n";
                return;
            }

            modelPhotoshop.systemState.tmp.clean();
            Color color {0, 0, 0, 1};

            int x_draw = x_start;
            int y_draw = y_start;

            if (abs(x - x_start) < abs(y - y_start))
            {
                int A = 2 * abs(x - x_start);
                int B = A - 2 * abs(y - y_start);
                int P = A - abs(y - y_start);

                for (y_draw = y_start; y_draw <= y; y_draw++)
                {
                    if (P < 0)
                    {
                        P += A;
                    }
                    else if (P >= 0)
                    {
                        if (x - x_start > 0)
                            x_draw++;
                        else 
                            x_draw--;
                        P += B;
                    }
                    
                    modelPhotoshop.setPixel ({x_draw, y_draw}, color, size);
                }
                x_draw = x;
                for (y_draw = y; y_draw <= y_start; y_draw++)
                {
                    if (P < 0)
                    {
                        P += A;
                    }
                    else if (P >= 0)
                    {
                        if (x - x_start > 0)
                            x_draw--;
                        else 
                            x_draw++;
                        P += B;
                    }
                    
                    modelPhotoshop.setPixel ({x_draw, y_draw}, color, size);
                }
                return;
            }


            int A = 2 * abs(y - y_start);
            int B = A - 2 * abs(x - x_start);
            int P = A - abs(x - x_start);
            for (x_draw = x_start; x_draw <= x; x_draw++)
            {
                if (P < 0)
                {
                    P += A;
                }
                else if (P >= 0)
                {
                    if (y - y_start > 0)
                        y_draw++;
                    else 
                        y_draw--;
                    P += B;
                }

                modelPhotoshop.setPixel ({x_draw, y_draw}, color, size);
            }
            y_draw = y;
            for (x_draw = x; x_draw <= x_start; x_draw++)
            {
                if (P < 0)
                {
                    P += A;
                }
                else if (P >= 0)
                {
                    if (y - y_start > 0)
                        y_draw--;
                    else 
                        y_draw++;
                    P += B;
                }

                modelPhotoshop.setPixel ({x_draw, y_draw}, color, size);
            }
            return;
        }
    }

    virtual void stop () override
    {
        modelPhotoshop.UpdateImage ();
        x_start = -1;
        y_start = -1;
    }
};

#endif /* STL_LINE */