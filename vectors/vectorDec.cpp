#include "vectorDec.hpp"

#include <cmath>
#include <cassert>

/**************************************************************************/

VectorDec::VectorDec (coord_t x_init, coord_t y_init) 
    : x(x_init), y(y_init)
{}

VectorDec::VectorDec (const VectorDec& vDec) 
    : x(vDec.x), y(vDec.y)
{}

/**************************************************************************/

VectorDec VectorDec::operator+ (const VectorDec& v2) const
{
    return VectorDec {x + v2.x, y + v2.y};
}

VectorDec VectorDec::operator- (const VectorDec& v2) const
{
    return VectorDec {x - v2.x, y - v2.y};
}

VectorDec VectorDec::operator* (const int mul) const
{
    return VectorDec {x * mul, y * mul};
}

VectorDec VectorDec::operator/ (const int mul) const
{
    return VectorDec {x / mul, y / mul};
}

VectorDec VectorDec::operator- () const
{
    return VectorDec {-x, -y};
}

/**************************************************************************/

void VectorDec::normalize ()
{
    x /= abs(x);
    y /= abs(y);
}

void VectorDec::perpendicular ()
{
    coord_t tmp = x;
    x = y;
    y = -tmp;
}

/**************************************************************************/

VectorDec NormalizeVector (const VectorDec& v) 
{
    return VectorDec {v.x / abs(v.x), v.y / abs(v.y)};
}

VectorDec PerpendicularVector (const VectorDec& v) 
{
    return VectorDec {v.y, -v.x};
}

/**************************************************************************/

/**************************************************************************/

VectorDecUint32::VectorDecUint32 (uint32_t x_init, uint32_t y_init) 
    : x(x_init), y(y_init)
{}

VectorDecUint32::VectorDecUint32 (const VectorDecUint32& vDec) 
    : x(vDec.x), y(vDec.y)
{}

/**************************************************************************/

VectorDecUint32 VectorDecUint32::operator+ (const VectorDecUint32& v2) const
{
    return VectorDecUint32 {x + v2.x, y + v2.y};
}

VectorDecUint32 VectorDecUint32::operator- (const VectorDecUint32& v2) const
{
    assert (x >= v2.x);
    assert (y >= v2.y);
    return VectorDecUint32 {x - v2.x, y - v2.y};
}

VectorDecUint32 VectorDecUint32::operator* (const int mul) const
{
    return VectorDecUint32 {x * mul, y * mul};
}

VectorDecUint32 VectorDecUint32::operator/ (const int mul) const
{
    return VectorDecUint32 {x / mul, y / mul};
}

/**************************************************************************/
