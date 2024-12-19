#ifndef STL_PsSPIIMPL
#define STL_PsSPIIMPL

#include <vector>
#include "../plugins/PsSPI.hpp"
#include "../Standard/tool_plugin.hpp"
#include "../objects/tool.hpp"
#include "../MVC/modelPhotoshop.hpp"
#include "../MVC/modelCanvas.hpp"

class StlPsSPI : public PsSPI
{
private:
    ModelPhotoshop& modelPhotoshop;
    ModelCanvas& modelCanvas;
    GraphicsCtx& ctx;
    std::vector <Tool*> pl_tools;

public:

    StlPsSPI (ModelPhotoshop& init_modelPhotoshop, ModelCanvas& init_modelCanvas, GraphicsCtx& init_ctx)
        :
        modelPhotoshop (init_modelPhotoshop),
        modelCanvas (init_modelCanvas), 
        ctx (init_ctx)
    {}

public:

    virtual void addTool (PsSPI_Tool* tool) override;
    virtual void addParameter (tool_t id, PsSPI_Parameter* param) override;
    virtual PsSPI_Event getEvent () override;
    virtual layer_t createLayer () override;
    virtual layer_t createParamLayer (tool_t id, param_t param_id) override;
    virtual void cleanLayer () override;
    virtual void cleanLayer (layer_t layer) override;
    virtual void overlayLayer (layer_t foreground) override;
    virtual void overlayLayer (layer_t foreground, layer_t background) override;
    virtual void setColor (PsSPI_Color color) override;
    virtual PsSPI_Color getPixel (int x, int y) override;
    virtual PsSPI_Color getPixel (layer_t layer, int x, int y) override;
    virtual void setPixel (int x, int y, PsSPI_Color color, int size = 1) override;
    virtual void setPixel (layer_t layer, int x, int y, PsSPI_Color color, int size = 1) override;
    virtual void updateLayer (layer_t layer) override;
};

#endif /* STL_PsSPIIMPL */