#ifndef STL_vectorDec
#define STL_vectorDec

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

#endif /* STL_vectorDec */