#ifndef STL_vectorDec
#define STL_vectorDec

#include <cstdint>

using coord_t = int;

class VectorDec
{
public:

    coord_t x {}; 
    coord_t y {};

    VectorDec (coord_t x = 0, coord_t y = 0);
    VectorDec (const VectorDec& vDec);

    VectorDec operator+ (const VectorDec& v2) const;
    VectorDec operator- (const VectorDec& v2) const;
    VectorDec operator- () const;
    VectorDec operator* (const int mul) const;
    VectorDec operator/ (const int mul) const;

    void normalize ();
    void perpendicular ();
};

VectorDec NormalizeVector     (const VectorDec& v);
VectorDec PerpendicularVector (const VectorDec& v);

class VectorDecUint32
{
public:

    uint32_t x; 
    uint32_t y;

    VectorDecUint32 (uint32_t x = 0, uint32_t y = 0);
    VectorDecUint32 (const VectorDecUint32& vDec);

    VectorDecUint32 operator+ (const VectorDecUint32& v2) const;
    VectorDecUint32 operator- (const VectorDecUint32& v2) const;
    VectorDecUint32 operator* (const int mul) const;
    VectorDecUint32 operator/ (const int mul) const;
};

#endif /* STL_vectorDec */