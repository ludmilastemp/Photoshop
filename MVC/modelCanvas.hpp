#ifndef STL_MODEL_CANVAS
#define STL_MODEL_CANVAS

#include <vector>
#include <iostream>
#include "systemState.hpp"
#include "Managers/toolbar.hpp"
#include "Managers/parameterManager.hpp"
#include "GrLib/color.hpp"

const int kLaterActive = -1;

class ModelCanvas
{
public:
    SystemState      systemState;
    Toolbar          toolbar;
    ParameterManager parameterManager;
    std::vector <Picture*> pluginLayers;
    std::vector <Picture*> pluginParamLayers;
    
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
    void   setPixel  (VectorDec coord, Color color, int size = 1, int layer = kLaterActive);
    Color  getPixel  (VectorDec coord, int layer = kLaterActive);
    void   overlayLayer (int foreground, int background = kLaterActive);
    void   cleanLayer  (int layer = kLaterActive);
    void   updateLayer (int layer = kLaterActive);
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

    int createPluginPicture (const char* png = nullptr)
    {
        Picture* p = nullptr;
        if (png)
            p = new Picture ({kWidthCanvas, kHeightCanvas}, {kWidthCanvasCorner, kHeightCanvasCorner}, png);
        else
            p = new Picture ({kWidthCanvas, kHeightCanvas}, {kWidthCanvasCorner, kHeightCanvasCorner});

        pluginLayers.push_back (p);
        systemState.pictures.push_back(p);
        return 100 + pluginLayers.size() - 1;
    }

    int createPluginParamPicture (VectorDec size, VectorDec corner, const char* png = nullptr)
    {
        Picture* p = nullptr;
        if (png)
            p = new Picture (size, corner, png);
        else
            p = new Picture (size, corner);
        
        p->setIsDraw (false);
        // std::cout << p << "\n";
        pluginParamLayers.push_back (p);
        return 300 + pluginParamLayers.size() - 1;
    }
};

#endif /* STL_MODEL_CANVAS */
