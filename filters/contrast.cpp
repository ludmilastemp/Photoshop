#include "PsSPI.hpp"

#include <cstddef>
#include <iostream>
#include <cmath>
#include <cstdint>

PsSPI* psspi = nullptr;

struct FilterTest : PsSPI_Filter
{
    PsSPI_Color (*pixels)[400];
    double contrastCoeff = 1.5;
    int size = 15;

    FilterTest (const char* img, const char* name) 
        : PsSPI_Filter(img, name)
    {
        pixels = new PsSPI_Color[600][400];
    }

    ~FilterTest ()
    {
        delete[] pixels;
    }

    virtual void apply()      override;
    virtual void activate()   override;
    virtual void deactivate() override;
};

struct Setting : PsSPI_FilterSetting
{
    Setting(const char* img, const char* name, FilterTest& _filter) 
        : PsSPI_FilterSetting(img, name), filter(_filter)
    {}

    FilterTest& filter;
    layer_t layerCur;

    virtual void activate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    FilterTest* filter  = new FilterTest { "img/filters/contrast.png", "contrast" };
    Setting*    setting = new Setting    { "img/size_icon.png", "setting", *filter };
    setting->x = 150; 
    setting->y = 70;
    setting->img_act = "img/filters/blur-setting.png";

    psspi->addFilter (filter);
    psspi->addFilterSetting (filter->id, setting);
}

void FilterTest::apply ()
{
    std::cout << "apply" << std::endl;
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
        {
            int r = 0, g = 0, b = 0;
            r = (pixels[x][y].r - 128) * contrastCoeff + 128,
            g = (pixels[x][y].g - 128) * contrastCoeff + 128,
            b = (pixels[x][y].b - 128) * contrastCoeff + 128;
            if (r < 0) r = 0; if (r > 255) r = 255; 
            if (g < 0) g = 0; if (g > 255) g = 255; 
            if (b < 0) b = 0; if (b > 255) b = 255; 
            psspi->setPixel (x, y, {(uint8_t)r, (uint8_t)g, (uint8_t)b, 255});          
        }
}

void FilterTest::activate ()
{
    std::cout << "meow" << std::endl;
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
            pixels[x][y] = psspi->getPixel (x, y);
    apply();
}

void FilterTest::deactivate ()
{
    std::cout << "bye" << std::endl;
}

void Setting::activate()
{
    PsSPI_Event event = psspi->getEvent();
    if (!event.mousePressed)
        return;

    int x = event.mouseCoordX;
    int y = event.mouseCoordY;

    if (0 <= y && y <= 37 &&
        0 <= x && x <= 75)
    {
        psspi->closeFilter (filter.id);
    }

    if (0  <= y && y <= 37 &&
        75 <= x && x <= 150)
    {
        for (int x = 0; x < 600; x++)
            for (int y = 0; y < 400; y++)
                psspi->setPixel (x, y, filter.pixels[x][y]);
        psspi->closeFilter (filter.id);
    }

    int size = 0;
    if (10 <= x && x <= 140 && 
        38 <= y && y <= 70)
    {
        size = (int)(1.0 * (x - 10) / 130 * (2 - 1) + 1);
        filter.contrastCoeff = size;
        filter.apply();
    }
    else return;

    // psspi->cleanLayer (layerCur);
    // for (int r_x = 0; r_x < size; r_x++)
    // {
    //     int r_y = sqrt (size * size - r_x * r_x);
    //     psspi->setPixel (layerCur, 75 + r_x, 75 + r_y, {0, 0, 0, 255});
    //     psspi->setPixel (layerCur, 75 + r_x, 75 - r_y, {0, 0, 0, 255});
    //     psspi->setPixel (layerCur, 75 - r_x, 75 + r_y, {0, 0, 0, 255});
    //     psspi->setPixel (layerCur, 75 - r_x, 75 - r_y, {0, 0, 0, 255});
    //     psspi->setPixel (layerCur, 75 + r_y, 75 + r_x, {0, 0, 0, 255});
    //     psspi->setPixel (layerCur, 75 + r_y, 75 - r_x, {0, 0, 0, 255});
    //     psspi->setPixel (layerCur, 75 - r_y, 75 + r_x, {0, 0, 0, 255});
    //     psspi->setPixel (layerCur, 75 - r_y, 75 - r_x, {0, 0, 0, 255});
    // }
    // psspi->updateLayer (layerCur);
}