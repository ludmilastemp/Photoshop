#include "PsSPI.hpp"

#include <cstddef>
#include <iostream>
#include <cmath>
#include <cstdint>

PsSPI* psspi = nullptr;

struct FilterTest : PsSPI_Filter
{
    PsSPI_Color (*pixels)[400];
    int coeffs[256];
    int size = 15;

    FilterTest (const char* img, const char* name) 
        : PsSPI_Filter(img, name)
    {
        pixels = new PsSPI_Color[600][400];
        for (int i = 0; i < 256; i++)
            coeffs[i] = i;
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

    virtual void activate() override;
};

void loadPlugin (PsSPI* psspi_)
{
    psspi = psspi_;

    FilterTest* filter  = new FilterTest { "img/filters/splain.png", "splain" };
    Setting*    setting = new Setting    { "img/size_icon.png", "setting", *filter };
    setting->x = 300; 
    setting->y = 332;
    setting->img_act = "img/filters/splain-setting.png";

    psspi->addFilter (filter);
    psspi->addFilterSetting (filter->id, setting);
    for (int i = 0; i < 256; i++)
        psspi->setPixel (setting->layer, 22 + i, 57 + 255 - i, {128, 128, 128, 255});
    psspi->updateLayer(setting->layer);
}

void FilterTest::apply ()
{
    std::cout << "apply" << std::endl;
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
        {
            int r = 0, g = 0, b = 0;
            int i = (pixels[x][y].r + pixels[x][y].g + pixels[x][y].b) / 3;
            if (i != 0)
                r = 1.0 * pixels[x][y].r * i / coeffs[i],
                g = 1.0 * pixels[x][y].g * i / coeffs[i],
                b = 1.0 * pixels[x][y].b * i / coeffs[i];
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
    if (22 <= x && x <= 275 && 
        57 <= y && y <= 310)
    {
        x -= 22;
        y -= 57;
        psspi->setPixel (layer, 22 + x, 57 + 255 - filter.coeffs[x], {71, 71, 71, 255});
        filter.coeffs[x] = 255 - y;
        psspi->setPixel (layer, 22 + x, 57 + 255 - filter.coeffs[x], {128, 128, 128, 255});
        psspi->updateLayer(layer);
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