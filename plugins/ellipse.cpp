#include "PsSPI.hpp"

#include <cstdlib>
#include <iostream>
#include <cmath>

PsSPI* psspi = nullptr;

struct ToolTest : PsSPI_Tool
{
    ToolTest(const char* img, const char* name) 
        : PsSPI_Tool(img, name)
    {
        color = {200, 25, 255, 255};
    }

    layer_t layerTmp;
    int x_start;
    int y_start;

    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    ToolTest*   tool  = new ToolTest   { "img/tools/ellipse.png",   "ellipse" };
    
    tool->layerTmp = psspi->createLayer();

    psspi->addTool (tool);
}

void ToolTest::apply ()
{
    PsSPI_Event event = psspi->getEvent();

    if (!event.mousePressed)
    {
        x_start = -1;
        y_start = -1;
        psspi->overlayLayer (layerTmp);
        psspi->cleanLayer (layerTmp);
        return;
    }

    int x = event.mouseCoordX;
    int y = event.mouseCoordY;

    if (x_start == -1 && y_start == -1)
    {
        x_start = x;
        y_start = y;
        return;
    }

    psspi->cleanLayer(layerTmp);

    int a = abs(x_start - x) / 2;
    int b = abs(y_start - y) / 2;
    int c = sqrt(abs(a*a - b*b));

    int x0 = (x_start + x) / 2;
    int y0 = (y_start + y) / 2;
    int R = 2 * std::max(a, b);

    int xc = (a > b) * c;
    int yc = (b > a) * c;

    for (int x_draw = -a; x_draw < a; x_draw++)
        for (int y_draw = -b; y_draw < b; y_draw++)
        {
            int r1 = (x_draw - xc) * (x_draw - xc) + (y_draw - yc) * (y_draw - yc);
            int r2 = (x_draw + xc) * (x_draw + xc) + (y_draw + yc) * (y_draw + yc);
            int r = sqrt(r1) + sqrt(r2);
            if (r < R)
            {
                psspi->setPixel (layerTmp, x0 + x_draw, y0 + y_draw, color, 1);
            }
        }

    psspi->updateLayer(layerTmp);
    return;
}

void ToolTest::activate ()
{
    std::cout << "meow" << std::endl;
}

void ToolTest::deactivate ()
{
    std::cout << "bye" << std::endl; 
}
