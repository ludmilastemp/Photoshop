#ifndef STL_PICTURE
#define STL_PICTURE

#include "object.hpp"

class Picture : public Object
{
public:
    VectorDec size;

    Picture (const VectorDec& init_size, const VectorDec& init_corner);
    Picture (const VectorDec& init_size, const VectorDec& init_corner, const char* png);
    
    void overlay (const Picture& from); 
    void clean (); 
}; 

#endif /* STL_PICTURE */