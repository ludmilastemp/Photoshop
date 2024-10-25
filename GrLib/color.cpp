#include "color.hpp"

#include <stdio.h>
#include <math.h>
#include <assert.h>

/**************************************************************************/

Color::Color (color_t init_r, color_t init_g, color_t init_b, color_t init_a) 
    : r(init_r), g(init_g), b(init_b), a(init_a)
{}

/**************************************************************************/

Color Color::operator+ (const Color& color2) const
{
    return Color {r + color2.r, g + color2.g, b + color2.b, a + color2.a};
}

Color Color::operator- (const Color& color2) const
{
    return Color {r - color2.r, g - color2.g, b - color2.b, a - color2.a};
}

Color Color::operator* (const Color& color2) const
{
    return Color {r * color2.r, g * color2.g, b * color2.b, a * color2.a};
}

Color Color::operator* (const double mul) const
{
    return Color {r * mul, g * mul, b * mul, a * mul};
}

Color Color::operator/ (const double mul) const
{
    return Color {r / mul, g / mul, b / mul, a / mul};
}

Color Color::operator- () const
{
    return Color {-r, -g, -b, a};
}

/**************************************************************************/

void Color::clamp ()
{
    if (r > 1) r = 1;
    if (g > 1) g = 1;
    if (b > 1) b = 1;
    if (a > 1) a = 1;
}
/**************************************************************************/
