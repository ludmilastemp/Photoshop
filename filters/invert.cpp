#include "../plugins/PsSPI.hpp"

#include <cstddef>
#include <iostream>
#include <cmath>
#include <cstdint>

PsSPI* psspi = nullptr;

struct FilterTest : PsSPI_Filter
{
    FilterTest (const char* img, const char* name) 
        : PsSPI_Filter(img, name)
    {}

    static const int BlurRadius = 5;
    int size = 15;
    layer_t layerTmp;

    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    FilterTest* filter = new FilterTest { "img/filters/invert.png", "invert" };

    psspi->addFilter (filter);
    filter->layerTmp = psspi->createLayer();
}

void FilterTest::apply ()
{
    std::cout << "apply" << std::endl;
}

void FilterTest::activate ()
{
    std::cout << "meow" << std::endl;
    PsSPI_Color (*pixels)[400] = new PsSPI_Color[600][400];
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
            pixels[x][y] = psspi->getPixel (x, y);

    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
        {
            psspi->setPixel (x, y, {(uint8_t)(255 - pixels[x][y].r), (uint8_t)(255 - pixels[x][y].g), (uint8_t)(255 - pixels[x][y].b), 255});
        }

    delete[] pixels;
}

void FilterTest::deactivate ()
{
    std::cout << "bye" << std::endl;
}
