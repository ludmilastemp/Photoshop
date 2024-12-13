#include "PsSPI.hpp"

#include <iostream>
#include <cmath>

PsSPI* psspi = nullptr;

struct ToolTest : PsSPI_Tool
{
    ToolTest(const char* img, const char* name) 
        : PsSPI_Tool(img, name)
    {}

    PsSPI_Color color = {0, 0, 0, 0};
    int size = 28;

    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;
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

    ToolTest*  tool = new ToolTest  { "img/eraser.png",    "eraser" };
    ParamSize* size = new ParamSize { "img/size_icon.png", "size", *tool };
    size->x = 150; 
    size->y = 200;
    size->img_act = "img/size.png";

    psspi->addTool (tool);
    psspi->addParameter (tool->id, size);
    size->layerCur = psspi->createParamLayer (tool->id, size->id);
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