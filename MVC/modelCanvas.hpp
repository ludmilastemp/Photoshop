#ifndef STL_MODEL_CANVAS
#define STL_MODEL_CANVAS

#include <vector>
#include "systemState.hpp"
#include "../objects/parameterManager.hpp"
#include "../GrLib/color.hpp"
#include "../objects/toolbar.hpp"
#include "../tools/tool.hpp" //
#include "../vectors/vectorDec.hpp"
#include "../GrLib/GrLib.hpp" ///

class ModelCanvas
{
public:
    SystemState systemState;
    Toolbar toolbar;
    ParameterManager parameterManager;
    
    // std::vector<Tool*> tools; 
    // int activeTool;

    ModelCanvas (Scene& main_scene);

    void operator() (Event& event)
    {
        update (event);
    }

    void update (Event& event);
    void addTool  (Tool& tool);
    void setActiveTool (int tool);
    void setPixel (VectorDec coord, Color color, int size = 1, int layer = -1);
    void setColor (Color color);
    void setSize  (int size);
    int getSize   ();
    Color getColor ();

    void UpdateImage ();
};


#endif /* STL_MODEL_CANVAS */
