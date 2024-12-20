#ifndef STL_TOOLBAR
#define STL_TOOLBAR

#include "manager.hpp"
#include "objects/tool.hpp"

class Toolbar : public Manager<Tool>
{
public:
    Toolbar () 
        :Manager ()
    {}

    void operator() (Event& event)
    {
        update (event);
    }

    void update (Event& event);

    void  setToolColor  (Color color);
    void  setToolSize   (int size);
    int   getToolSize   ();
    Color getToolColor ();
};

#endif /* STL_TOOLBAR */