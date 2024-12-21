#include "PsSPI.hpp"

#include <cstddef>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <cassert>

PsSPI* psspi = nullptr;

struct FilterTest : PsSPI_Filter
{
    FilterTest (const char* img, const char* name) 
        : PsSPI_Filter(img, name)
    {}

    static const int GaussianBlurRadius = 1;
    const double GaussianBlurMatrix[2 * GaussianBlurRadius + 1][2 * GaussianBlurRadius + 1] = {
        {1.0/16, 1.0/8, 1.0/16},
        {1.0/8,  1.0/4, 1.0/8}, 
        {1.0/16, 1.0/8, 1.0/16}
    };

    int size = 15;
    layer_t layerTmp;

    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    FilterTest* filter = new FilterTest { "img/filters/gaussianBlur.png", "gaussianBlur" };

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

    int rad = GaussianBlurRadius;
    for (int x = rad; x < 600 - rad; x++)
        for (int y = rad; y < 400 - rad; y++)
        {
            double r = 0, g = 0, b = 0;
            for (int i = -rad; i <= rad; i++)
                for (int j = -rad; j <= rad; j++)
                    r += GaussianBlurMatrix[rad + i][rad + j] * pixels[x + i][y + j].r,
                    g += GaussianBlurMatrix[rad + i][rad + j] * pixels[x + i][y + j].g,
                    b += GaussianBlurMatrix[rad + i][rad + j] * pixels[x + i][y + j].b;
            psspi->setPixel (x, y, {(uint8_t)r, (uint8_t)g, (uint8_t)b, 255});            
        }

    delete[] pixels;
}

void FilterTest::deactivate ()
{
    std::cout << "bye" << std::endl;
}
