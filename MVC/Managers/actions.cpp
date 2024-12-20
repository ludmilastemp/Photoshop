#include "actions.hpp"
#include "MVC/modelPhotoshop.hpp"

bool ActionToolbar::call (Event event)
{
    int y = event.getCoord().y;

    if (y / (kHeightIcon + kOffsetIcon) < modelCanvas.toolbar.getSize() && 
        y % (kHeightIcon + kOffsetIcon) <= kHeightIcon)
    {
        int object = y / (kHeightIcon + kOffsetIcon);
        printf ("setActiveTool %d\n", object);
        if (modelCanvas.toolbar.activeObject == object)
        {
            modelCanvas.setActiveTool (-1);
        }
        else
        {
            modelPhotoshop->activateTool ();
            modelCanvas.setActiveTool (object);
        }
        return true;
    }
    return false;
}

bool ActionIcon::call (Event event)
{
    if (menuManager.activeObject == index)
        menuManager.deactivate ();
    else
    {
        menuManager.activate (index);
        modelPhotoshop->activateMenu ();
    }
    return true;
}
