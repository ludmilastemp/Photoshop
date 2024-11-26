#ifndef STL_MODEL_CANVAS
#define STL_MODEL_CANVAS

#include <vector>
#include "systemState.hpp"
#include "Managers/toolbar.hpp"
#include "Managers/parameterManager.hpp"
#include "../GrLib/color.hpp"

class ModelCanvas
{
public:
    SystemState      systemState;
    Toolbar          toolbar;
    ParameterManager parameterManager;
    
    double scale;
    int x_canvas;
    int y_canvas;

    ModelCanvas (Scene& main_scene);

    void operator() (Event& event)
    {
        update (event);
    }

    void   update        (Event& event);
    void   addTool       (Tool& tool);
    void   setActiveTool (int tool);
    void   setPixel  (VectorDec coord, Color color, int size = 1, int layer = -1);
    Color  getColor  ();   
    void   setColor  (Color color);
    int    getSize   (); 
    void   setSize   (int size);
    int    getShiftX ();
    void   setShiftX (int shiftX);
    int    getShiftY ();
    void   setShiftY (int shiftY);
    double getScale  ();
    void   setScale  (double scale);

    void UpdateImage ();
};


#endif /* STL_MODEL_CANVAS */
