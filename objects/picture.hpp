#ifndef STL_PICTURE
#define STL_PICTURE

#include "object.hpp"
#include "../GrLib/color.hpp"

class Picture : public Object
{
public:
    VectorDec size;

    Picture (const VectorDec& init_size, const VectorDec& init_corner);
    Picture (const VectorDec& init_size, const VectorDec& init_corner, const char* png);
    
    void setPixel (const VectorDec& coord, Color color);
    void overlay (const Picture& from); 
    void update (); 
    void clean (); 
}; 

#endif /* STL_PICTURE */