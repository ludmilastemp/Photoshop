#ifndef STL_TOOLBAR
#define STL_TOOLBAR

#include "../tools/tool.hpp"
#include "object.hpp"

class Toolbar : public Scene
{
private:
    std::vector <Tool*> tools; 
    int activeTool;

public:
    Toolbar () 
        :activeTool (-1)
    {}

    void operator() (Event& event)
    {
        update (event);
    }

    void update (Event& event);

    void add        (Tool& tool);
    void activate   (int tool);
    void deActivate ();
    size_t getSize () { return tools.size(); }

    void setToolColor  (Color color);
    void setToolSize   (int size);
    int  getToolSize   ();
    Color getToolColor ();
};

#endif /* STL_TOOLBAR */