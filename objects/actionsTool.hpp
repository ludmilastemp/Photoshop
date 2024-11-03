#ifndef STL_ACTIONSTOOL
#define STL_ACTIONSTOOL

#include <cstdlib>
#include "actionClass.hpp"

#include "../MVC/modelPhotoshop.hpp"

/**************************************************************************/

class ActionNone : public Action
{
public:
    ActionNone ()
    {}

    virtual void call () override
    {

    }
};

class ActionBrush : public Action
{
private:
    ModelPhotoshop& modelPhotoshop;

public:
    ActionBrush (ModelPhotoshop& init_modelPhotoshop)
        : modelPhotoshop(init_modelPhotoshop)
    {}

    virtual void call () override
    {
        std::cout << "setActiveTool 0\n";
        modelPhotoshop.setActiveTool (0);
    }
};

class ActionEraser : public Action
{
private:
    ModelPhotoshop& modelPhotoshop;

public:
    ActionEraser (ModelPhotoshop& init_modelPhotoshop)
        : modelPhotoshop(init_modelPhotoshop)
    {}

    virtual void call () override
    {
        std::cout << "setActiveTool 1\n";
        modelPhotoshop.setActiveTool (1);
    }
};

class ActionLine : public Action
{
private:
    ModelPhotoshop& modelPhotoshop;

public:
    ActionLine (ModelPhotoshop& init_modelPhotoshop)
        : modelPhotoshop(init_modelPhotoshop)
    {}

    virtual void call () override
    {
        std::cout << "setActiveTool 2\n";
        modelPhotoshop.setActiveTool (2);
    }
};

/**************************************************************************/

#endif /* STL_ACTIONSTOOL */