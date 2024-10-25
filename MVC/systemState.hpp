#ifndef STL_SYSTEM_STATE
#define STL_SYSTEM_STATE

#include "../GrLib/GrLibCtx.hpp"
#include "../objects/picture.hpp"

class SystemState
{
public:
    Picture background;
    Picture base;
    Picture tmp;

    SystemState ()
        : 
        background ({kWidthCanvas,       kHeightCanvas}, 
                    {kWidthCanvasCorner, kHeightCanvasCorner}, "img/cat.png"),
        base       ({kWidthCanvas,       kHeightCanvas}, 
                    {kWidthCanvasCorner, kHeightCanvasCorner}, "img/cat.png"),
        tmp        ({kWidthCanvas,       kHeightCanvas}, 
                    {kWidthCanvasCorner, kHeightCanvasCorner})
    {}

};

#endif /* STL_SYSTEM_STATE */