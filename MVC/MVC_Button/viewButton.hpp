#ifndef STL_VIEW_BUTTON
#define STL_VIEW_BUTTON

#include "../../objects/button.hpp"

class ViewButton
{
public:
    std::vector <Button>* buttons;

    ViewButton (std::vector <Button>* buttons);

    void operator() (GraphicsCtx& ctx)
    {
        update(ctx);
    }

    void update (GraphicsCtx& ctx);
};

#endif /* STL_VIEW_BUTTON */