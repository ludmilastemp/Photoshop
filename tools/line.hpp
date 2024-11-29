#ifndef STL_LINE
#define STL_LINE

#include "tool.hpp"
#include "../MVC/modelCanvas.hpp"

class ToolLine : public Tool
{
private:
    ModelCanvas& modelCanvas;
    GraphicsCtx&    ctx;
    int size;
    Color color;
    int x_start;
    int y_start;

public:

    ToolLine (ModelCanvas& init_modelPhotoshop, GraphicsCtx& init_ctx)
        :modelCanvas (init_modelPhotoshop), 
        ctx (init_ctx),
        size (5), 
        color (1, 0, 1, 1),
        x_start(-1), 
        y_start(-1)
    {}

    virtual void apply (Event event) override
    {
        if (!event.getMousePressed ())
        {
            modelCanvas.UpdateImage ();
            x_start = -1;
            y_start = -1;
            return;
        }

        int x = event.getCoord().x - kWidthCanvasCorner;
        int y = event.getCoord().y - kHeightCanvasCorner;

        if (x_start == -1 && y_start == -1)
        {
            x_start = x;
            y_start = y;
            return;
        }

        modelCanvas.systemState.tmp.clean();

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
                
                modelCanvas.setPixel ({x_draw, y_draw}, color, size);
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
                
                modelCanvas.setPixel ({x_draw, y_draw}, color, size);
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

            modelCanvas.setPixel ({x_draw, y_draw}, color, size);
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

            modelCanvas.setPixel ({x_draw, y_draw}, color, size);
        }
        return;
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

    virtual void deActivate () override
    {
        modelCanvas.UpdateImage ();
        x_start = -1;
        y_start = -1;
    }
};

#endif /* STL_LINE */