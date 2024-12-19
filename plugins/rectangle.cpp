#include "PsSPI.hpp"

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
    bool fill = false;

    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;
};

struct ParamFill : PsSPI_Parameter
{
    ParamFill(const char* img, const char* name, ToolTest& _tool) 
        : PsSPI_Parameter(img, name), tool(_tool)
    {}

    ToolTest& tool;
    PsSPI_Color color_true  = {0, 0, 0, 255};
    PsSPI_Color color_false = {71, 71, 71, 255};

    virtual void activate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    ToolTest*   tool  = new ToolTest   { "img/tools/rectangle.png", "rectangle" };
    ParamFill* fill = new ParamFill { "img/parameters/fill_icon.png", "fill", *tool };
    fill->x = 84; 
    fill->y = 45;
    fill->img_act = "img/parameters/fill.png";

    tool->layerTmp = psspi->createLayer();

    psspi->addTool (tool);
    psspi->addParameter (tool->id, fill);
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

    int x_max = std::max (x_start, x);
    int y_max = std::max (y_start, y);

    if (fill)
        for (int x_draw = std::min (x_start, x); x_draw < x_max; x_draw++)
            for (int y_draw = std::min (y_start, y); y_draw < y_max; y_draw++)
                psspi->setPixel (layerTmp, x_draw, y_draw, color, 1);
    else
    {
        for (int x_draw = std::min (x_start, x); x_draw < x_max; x_draw++)
        {
            psspi->setPixel (layerTmp, x_draw, y_start, color, 1);
            psspi->setPixel (layerTmp, x_draw, y,       color, 1);
        }

        for (int y_draw = std::min (y_start, y); y_draw < y_max; y_draw++)
        {
            psspi->setPixel (layerTmp, x_start, y_draw, color, 1);
            psspi->setPixel (layerTmp, x,       y_draw, color, 1);
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

void ParamFill::activate ()
{
    std::cout << "fill" << std::endl;

    PsSPI_Event event = psspi->getEvent();
    if (!event.mousePressed)
        return;

    int x = event.mouseCoordX;
    int y = event.mouseCoordY;
    
    PsSPI_Color color;
    if (tool.fill)
    {
        tool.fill = false;
        color = color_false;
    }
    else
    {
        tool.fill = true;
        color = color_true;
    }

    for (int x_draw = 0; x_draw < 15; x_draw++)
        for (int y_draw = 0; y_draw < 15; y_draw++)
            psspi->setPixel (layer, 52 + x_draw, 14 + y_draw, color, 1);

    psspi->updateLayer (layer);
}
