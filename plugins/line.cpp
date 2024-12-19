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
    int size = 10;
    int x_start;
    int y_start;

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

    ToolTest*   tool  = new ToolTest   { "img/tools/line.png",      "line" };
    
    ParamSize* size = new ParamSize { "img/size_icon.png", "size", *tool };
    size->x = 150; 
    size->y = 200;
    size->img_act = "img/size.png";

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
            psspi->setPixel (layerTmp, x_draw, y_draw, color, size);
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
            psspi->setPixel (layerTmp, x_draw, y_draw, color, size);
        }
    }
    else 
    {
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
            psspi->setPixel (layerTmp, x_draw, y_draw, color, size);
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
            psspi->setPixel (layerTmp, x_draw, y_draw, color, size);
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