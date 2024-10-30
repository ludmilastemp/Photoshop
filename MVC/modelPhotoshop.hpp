#ifndef STL_MODEL_PHOTOSHOP
#define STL_MODEL_PHOTOSHOP

#include <vector>
#include "systemState.hpp"
#include "../GrLib/color.hpp"
#include "../tools/tool.hpp"
#include "../vectors/vectorDec.hpp"
#include "../GrLib/GrLib.hpp" ///

class ModelPhotoshop
{
public:
    SystemState systemState;
    
    std::vector<Tool*> tools; 
    int activeTool;

    ModelPhotoshop (Scene& main_scene);

    void operator() (sf::Event event)
    {
        update (event);
    }

    void update (sf::Event event);
    void setActiveTool (int tool);
    void addTool (Tool& tool);
    void setPixel (VectorDec coord, Color color, int size = 1, int layer = -1);

    void UpdateImage ();
};


#endif /* STL_MODEL_PHOTOSHOP */
