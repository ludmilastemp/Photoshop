#include "PsSPI.hpp"

#include <iostream>
#include <cmath>

PsSPI* psspi = nullptr;

struct ToolTest : PsSPI_Tool
{
    ToolTest(const char* img, const char* name) 
        : PsSPI_Tool(img, name)
    {
        color = {255, 255, 255, 255};
    }

    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    ToolTest*  tool = new ToolTest  { "img/tools/eyedropper.png", "eyedropper" };
    psspi->addTool (tool);
}

void ToolTest::apply ()
{
    PsSPI_Event event = psspi->getEvent();

    if (!event.mousePressed)
        return;

    int x = event.mouseCoordX;
    int y = event.mouseCoordY;

    color = psspi->getPixel (x, y);
    psspi->setColor (color);
}

void ToolTest::activate ()
{
    std::cout << "meow" << std::endl;
}

void ToolTest::deactivate ()
{
    std::cout << "bye" << std::endl;
}
