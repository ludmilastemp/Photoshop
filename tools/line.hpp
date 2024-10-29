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

            int A = 2 * (y - y_start);
            int B = A - 2 * (x - x_start);
            int P = A - (x - x_start);
            int x_draw = x_start;
            int y_draw = y_start;

            if (abs(x - x_start) < abs(y - y_start))
            {
                A = 2 * (x - x_start);
                B = A - 2 * (y - y_start);
                P = A - (y - y_start);

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

                    for (int i = -size / 2; i <= size / 2; i++)
                    {
                        for (int j = -size / 2; j <= size / 2; j++)
                        {
                            if (0 <= x_draw + i && x_draw + i < kWidthCanvas && 
                                0 <= y_draw + j && y_draw + j < kHeightCanvas)
                                modelPhotoshop.setPixel ({x_draw + i, y_draw + j}, color);
                        }
                    }
                }
                return;
            }

// • Если линия наклонена вниз, а не вверх, то, когда значение P равно 0
// или больше, нарисуйте пиксель следующего столбца на одну строку ниже предыдущего пикселя,
// а не над ним.
// • Если изменение значения Y больше, чем изменение значения X, то
// необходимо будет изменить вычисления для A, B и начальное значение для P.

// При вычислении A, B и начального значения P используйте X там, где ранее
// вы использовали бы Y, и наоборот. При рисовании пикселей, вместо того чтобы проходить
// по каждому столбцу на оси X, пройдитесь по каждой строке на оси Y,
// рисуя по одному пикселю на строку.

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

                for (int i = -size / 2; i <= size / 2; i++)
                {
                    for (int j = -size / 2; j <= size / 2; j++)
                    {
                        if (0 <= x_draw + i && x_draw + i < kWidthCanvas && 
                            0 <= y_draw + j && y_draw + j < kHeightCanvas)
                            modelPhotoshop.setPixel ({x_draw + i, y_draw + j}, color);
                    }
                }
            }
            return;

            int x_min = std::min (x_start, x);
            int x_max = std::max (x_start, x);

            for (int x_draw = x_min; x_draw <= x_max; x_draw++)
            {
                double scale = 1.0 * (x - x_draw) / (x - x_start);

                int y_draw;
                y_draw = (int)(y - scale * (y - y_start)) - 1; 
                if (0 <= y_draw && y_draw < kWidthCanvas)
                    modelPhotoshop.setPixel ({x_draw, y_draw}, color);

                y_draw += 1; 
                if (0 <= y_draw && y_draw < kWidthCanvas)
                    modelPhotoshop.setPixel ({x_draw, y_draw}, color);

                y_draw += 1; 
                if (0 <= y_draw && y_draw < kWidthCanvas)
                    modelPhotoshop.setPixel ({x_draw, y_draw}, color);
            }
                        

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