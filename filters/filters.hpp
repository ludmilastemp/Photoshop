#ifndef STL_FILTER_BLUR
#define STL_FILTER_BLUR

#include "../MVC/modelCanvas.hpp"
#include <iostream>
#include <memory>

const int BlurRadius = 5;
const double BrightnessCoeff = 25 / 255.0;
const double ContrastCoeff = 1.5;

const int GaussianBlurRadius = 1;
const float GaussianBlurMatrix[2 * GaussianBlurRadius + 1][2 * GaussianBlurRadius + 1] = {
    {1.0/16, 1.0/8, 1.0/16},
    {1.0/8,  1.0/4, 1.0/8}, 
    {1.0/16, 1.0/8, 1.0/16}
};

void Blur (ModelCanvas& modelCanvas)
{
    Color (*pixels)[400] = new Color[600][400];
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
            pixels[x][y] = modelCanvas.getPixel ({x, y});

    int rad = BlurRadius;
    for (int x = rad; x < 600 - rad; x++)
        for (int y = rad; y < 400 - rad; y++)
        {
            Color color {0, 0, 0, 0};
            for (int i = -rad; i < rad; i++)
                for (int j = -rad; j < rad; j++)
                    color = color + pixels[x + i][y + j];

            color = color / rad / rad / 4;
            color.a = 1;
            modelCanvas.setPixel ({x, y}, color);
        }
    delete[] pixels;
}

void GaussianBlur (ModelCanvas& modelCanvas)
{
    Color (*pixels)[400] = new Color[600][400];
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
            pixels[x][y] = modelCanvas.getPixel ({x, y});

    for (int x = GaussianBlurRadius; x < 600 - GaussianBlurRadius; x++)
        for (int y = GaussianBlurRadius; y < 400 - GaussianBlurRadius; y++)
        {
            Color color {0, 0, 0, 0};
            for (int i = -GaussianBlurRadius; i <= GaussianBlurRadius; i++)
                for (int j = -GaussianBlurRadius; j <= GaussianBlurRadius; j++)
                    color = color + pixels[x + i][y + j] * 
                        GaussianBlurMatrix[GaussianBlurRadius + i][GaussianBlurRadius + j];

            color.a = 1;
            modelCanvas.setPixel ({x, y}, color);
        }
    delete[] pixels;
}

void UnsharpMask (ModelCanvas& modelCanvas)
{
    Color (*pixels)[400] = new Color[600][400];
    Color (*pixelsGauss)[400] = new Color[600][400];
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
            pixels[x][y] = modelCanvas.getPixel ({x, y});

    for (int x = GaussianBlurRadius; x < 600 - GaussianBlurRadius; x++)
        for (int y = GaussianBlurRadius; y < 400 - GaussianBlurRadius; y++)
        {
            Color color {0, 0, 0, 0};
            for (int i = -GaussianBlurRadius; i <= GaussianBlurRadius; i++)
                for (int j = -GaussianBlurRadius; j <= GaussianBlurRadius; j++)
                    color = color + pixels[x + i][y + j] * 
                        GaussianBlurMatrix[GaussianBlurRadius + i][GaussianBlurRadius + j];

            color.a = 1;
            pixelsGauss[x][y] = color;
        }

    for (int x = GaussianBlurRadius; x < 600 - GaussianBlurRadius; x++)
        for (int y = GaussianBlurRadius; y < 400 - GaussianBlurRadius; y++)
        {
            Color color = (pixels[x][y] - pixelsGauss[x][y]) * 2 + (pixels[x][y]);
            color.clamp();
            color.a = 1;
            modelCanvas.setPixel ({x, y}, color);
        }

    delete[] pixels;
    delete[] pixelsGauss;
}

void Invert (ModelCanvas& modelCanvas)
{
    Color (*pixels)[400] = new Color[600][400];
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
            pixels[x][y] = modelCanvas.getPixel ({x, y});

    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
        {
            Color c = pixels[x][y];
            Color color;
            color = color - c;
            color.a = 1;
            modelCanvas.setPixel ({x, y}, color);
        }
    delete[] pixels;
}

void Brightness (ModelCanvas& modelCanvas)
{
    Color (*pixels)[400] = new Color[600][400];
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
            pixels[x][y] = modelCanvas.getPixel ({x, y});

    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
        {
            Color color = pixels[x][y];
            color = color + Color{BrightnessCoeff, BrightnessCoeff, BrightnessCoeff};
            color.clamp();
            modelCanvas.setPixel ({x, y}, color);
        }
    delete[] pixels;
}

void Contrast (ModelCanvas& modelCanvas)
{
    Color (*pixels)[400] = new Color[600][400];
    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
            pixels[x][y] = modelCanvas.getPixel ({x, y});

    for (int x = 0; x < 600; x++)
        for (int y = 0; y < 400; y++)
        {
            Color color = pixels[x][y];
            if (color.a > 0.5)
            {
                color = (color - Color {0.5, 0.5, 0.5}) * ContrastCoeff + Color {0.5, 0.5, 0.5};
            }
            color.a = 1;
            color.clamp();
            modelCanvas.setPixel ({x, y}, color);
        }
    delete[] pixels;
}

#endif /* STL_FILTER_BLUR */