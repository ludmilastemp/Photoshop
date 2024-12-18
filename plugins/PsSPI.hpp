#ifndef __PsSPI__
#define __PsSPI__

extern "C"
{
    struct PsSPI;
    void loadPlugin (PsSPI* psspi);
}

using tool_t  = int;
using param_t = int;
using layer_t = int;

struct PsSPI_Tool
{
    PsSPI_Tool(const char* init_img, const char* init_name) 
        : img(init_img), name(init_name) 
    {}

    tool_t id = -1;
    const char* img;
    const char* name;
    virtual void apply()      {};
    virtual void activate()   {};
    virtual void deactivate() {};
};

struct PsSPI_Parameter
{
    PsSPI_Parameter(const char* init_img_icon, const char* init_name) 
        : img_icon(init_img_icon), name(init_name) 
    {}

    param_t id = -1;
    layer_t layer = -1;
    const char* img_icon;
    const char* name;
    const char* img_act;
    int x; int y;
    virtual void activate() {};
};

struct PsSPI_Color
{
    unsigned char r, g, b, a;
};

struct PsSPI_Event
{
    bool mousePressed;
    int  mouseCoordX;
    int  mouseCoordY;
};

class PsSPI
{
public:
    virtual void  addTool (PsSPI_Tool* tool) = 0;
    virtual void addParameter (tool_t id, PsSPI_Parameter* param) = 0;
    virtual PsSPI_Event getEvent () = 0;
    virtual layer_t createLayer () = 0;
    virtual layer_t createParamLayer (tool_t id, param_t param_id) = 0;
    virtual void cleanLayer () = 0;
    virtual void cleanLayer (layer_t layer) = 0;
    virtual void overlayLayer (layer_t foreground) = 0;
    virtual void overlayLayer (layer_t foreground, layer_t background) = 0;
    virtual PsSPI_Color getPixel (int x, int y) = 0;
    virtual PsSPI_Color getPixel (layer_t layer, int x, int y) = 0;
    virtual void setPixel (int x, int y, PsSPI_Color color, int size = 1) = 0;
    virtual void setPixel (layer_t layer, int x, int y, PsSPI_Color color, int size = 1) = 0;
    virtual void updateLayer (layer_t layer) = 0;
};

#endif /* __PsSPI__ */