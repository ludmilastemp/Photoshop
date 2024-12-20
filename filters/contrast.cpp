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

    const double ContrastCoeff = 1.5;
    int size = 15;
    layer_t layerTmp;

    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    FilterTest* filter = new FilterTest { "img/filters/contrast.png", "contrast" };

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
            int r = 0, g = 0, b = 0;
            r = (pixels[x][y].r - 128) * ContrastCoeff + 128,
            g = (pixels[x][y].g - 128) * ContrastCoeff + 128,
            b = (pixels[x][y].b - 128) * ContrastCoeff + 128;
            if (r < 0) r = 0; if (r > 255) r = 255; 
            if (g < 0) g = 0; if (g > 255) g = 255; 
            if (b < 0) b = 0; if (b > 255) b = 255; 
            psspi->setPixel (x, y, {(uint8_t)r, (uint8_t)g, (uint8_t)b, 255});          
        }

    delete[] pixels;
}

void FilterTest::deactivate ()
{
    std::cout << "bye" << std::endl;
}
