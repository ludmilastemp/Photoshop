#include "PsSPI.hpp"

#include <iostream>
#include <cmath>

PsSPI* psspi = nullptr;

struct ToolTest : PsSPI_Tool
{
    ToolTest(const char* img, const char* name) 
        : PsSPI_Tool(img, name)
    {
         color = {0, 255, 255, 255};
    }

    int size = 15;
    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;

    virtual void        setColor (PsSPI_Color new_color) override { color = new_color; }
    virtual PsSPI_Color getColor ()                      override { return color; }
};

struct ParamColor : PsSPI_Parameter
{
    ParamColor(const char* img, const char* name, ToolTest& _tool) 
        : PsSPI_Parameter(img, name), tool(_tool)
    {}

    ToolTest& tool;

    virtual void activate() override;
};

struct ParamSize : PsSPI_Parameter
{
    ParamSize(const char* img, const char* name, ToolTest& _tool) 
        : PsSPI_Parameter(img, name), tool(_tool)
    {}

    ToolTest& tool;
    layer_t layerCur;

    virtual void activate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    ToolTest*   tool  = new ToolTest   { "img/tools/brush.png",           "brush" };
    ParamColor* color = new ParamColor { "img/colorwheel_icon.png", "color", *tool };
    color->x = 150; 
    color->y = 150;
    color->img_act = "img/colorwheel.png";

    ParamSize* size = new ParamSize { "img/size_icon.png", "size", *tool };
    size->x = 150; 
    size->y = 200;
    size->img_act = "img/size.png";

    psspi->addTool (tool);
    // psspi->addParameter (tool->id, color);
    // psspi->addParameter (tool->id, size);
    // size->layerCur = psspi->createParamLayer (tool->id, size->id);
}

void ToolTest::apply ()
{
    PsSPI_Event event = psspi->getEvent();

    if (!event.mousePressed)
        return;

    int x = event.mouseCoordX;
    int y = event.mouseCoordY;

    psspi->setPixel (x, y, color, size);
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

void ParamSize::activate ()
{
    std::cout << "size" << std::endl;

    PsSPI_Event event = psspi->getEvent();
    if (!event.mousePressed)
        return;

    int x = event.mouseCoordX;
    int y = event.mouseCoordY;

    int size = 0;
    if (15 <= x && x <= 140 && 
        0  <= y && y <= 200)
    {
        size = (int)(1.0 * (x - 15) / 125 * (60 - 1) + 3);
        tool.size = size;
    }
    else return;

    psspi->cleanLayer (layerCur);
    for (int r_x = 0; r_x < size; r_x++)
    {
        int r_y = sqrt (size * size - r_x * r_x);
        psspi->setPixel (layerCur, 75 + r_x, 75 + r_y, {0, 0, 0, 255});
        psspi->setPixel (layerCur, 75 + r_x, 75 - r_y, {0, 0, 0, 255});
        psspi->setPixel (layerCur, 75 - r_x, 75 + r_y, {0, 0, 0, 255});
        psspi->setPixel (layerCur, 75 - r_x, 75 - r_y, {0, 0, 0, 255});
        psspi->setPixel (layerCur, 75 + r_y, 75 + r_x, {0, 0, 0, 255});
        psspi->setPixel (layerCur, 75 + r_y, 75 - r_x, {0, 0, 0, 255});
        psspi->setPixel (layerCur, 75 - r_y, 75 + r_x, {0, 0, 0, 255});
        psspi->setPixel (layerCur, 75 - r_y, 75 - r_x, {0, 0, 0, 255});
    }
    psspi->updateLayer (layerCur);
}
