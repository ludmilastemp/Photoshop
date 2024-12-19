#ifndef STL_SYSTEM_STATE
#define STL_SYSTEM_STATE

#include "../objects/picture.hpp"

class SystemState
{
public:
    Picture background;
    Picture base;
    Picture tmp;
    std::vector <Picture*> pictures;

    SystemState (Scene& main_scene)
        : 
        background ({kWidthCanvas,       kHeightCanvas}, 
                    {kWidthCanvasCorner, kHeightCanvasCorner}, "img/paper.jpg"),
                    // {kWidthCanvasCorner, kHeightCanvasCorner}, "img/cat.png"),
        base       ({kWidthCanvas,       kHeightCanvas}, 
                    {kWidthCanvasCorner, kHeightCanvasCorner}, "img/paper.jpg"),
        tmp        ({kWidthCanvas,       kHeightCanvas}, 
                    {kWidthCanvasCorner, kHeightCanvasCorner})
    {
        main_scene.addObject (background);
        main_scene.addObject (base);
        main_scene.addObject (tmp);
    }

};

#endif /* STL_SYSTEM_STATE */