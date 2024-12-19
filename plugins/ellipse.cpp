#include "PsSPI.hpp"

#include <cstdlib>
#include <iostream>
#include <cmath>

PsSPI* psspi = nullptr;

struct ToolTest : PsSPI_Tool
{
    ToolTest(const char* img, const char* name) 
        : PsSPI_Tool(img, name)
    {}
    
    layer_t layerTmp;
    PsSPI_Color color = {200, 25, 255, 255};
    int x_start;
    int y_start;

    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;
};

struct ParamColor : PsSPI_Parameter
{
    ParamColor(const char* img, const char* name, ToolTest& _tool) 
        : PsSPI_Parameter(img, name), tool(_tool)
    {}

    ToolTest& tool;

    virtual void activate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    ToolTest*   tool  = new ToolTest   { "img/tools/ellipse.png",   "ellipse" };
    ParamColor* color = new ParamColor { "img/colorwheel_icon.png", "color", *tool };
    color->x = 150; 
    color->y = 150;
    color->img_act = "img/colorwheel.png";

    tool->layerTmp = psspi->createLayer();

    psspi->addTool (tool);
    psspi->addParameter (tool->id, color);
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

void ParamColor::activate ()
{
    std::cout << "color" << std::endl;

    PsSPI_Event event = psspi->getEvent();
    if (!event.mousePressed)
        return;

    int x = event.mouseCoordX;
    int y = event.mouseCoordY;

    tool.color = psspi->getPixel (layer, x, y);

    for (int r_x = -30; r_x < 30; r_x++)
    {
        for (int r_y = -30; r_y < 30; r_y++)
        {
            if (r_x * r_x + r_y * r_y <= 30 * 30)
            {
                psspi->setPixel (layer, 75 + r_x, 75 + r_y, tool.color);
            }
        }
    }
    std::cout << layer << std::endl;
    psspi->updateLayer (layer);
}
