#ifndef STL_MENU_FILE
#define STL_MENU_FILE

#include <cstdlib>
#include <cmath>
#include "../../objects/actionClass.hpp"
#include "../../objects/button.hpp"

#include "../modelPhotoshop.hpp"
#include "../modelCanvas.hpp"

// #include "../../filters/filters.hpp"

/**************************************************************************/

class ActionFile : public Action
{
private:
    ModelCanvas& modelCanvas;

public:
    ActionFile (ModelCanvas& init_modelCanvas)
        : modelCanvas(init_modelCanvas)
    { }

    virtual Scene* create (std::vector<void*>* buttons) override
    {
        VectorDec size = {130, 37 * 2};
        const char* png = "img/menu/file-list.png";

        Button* button = new Button {size, {0, 40}, *this, png};
        buttons->push_back (button);

        Scene* sceneParameter = new Scene {};
        sceneParameter->addObject (*button);
        sceneParameter->setIsDraw (false);
        return sceneParameter;
    }

    virtual bool call (Event event) override
    {
        int x = event.getCoord().x;
        int y = event.getCoord().y;

        if (0 * 37 < y && y < 1 * 37)
        {
            printf ("Please enter the path to the image:\n");
            char path[216];
            std::cin >> path;
            modelCanvas.systemState.background.setPicture (path);
            modelCanvas.systemState.base.clean();
            return true;
        }
        if (1 * 37 < y && y < 2 * 37)
        {
            printf ("not implemented\n");
            return true;
        }
        return false;
    }
};

class ActionFilter : public Action
{
private:
    ModelPhotoshop& modelPhotoshop;

public:
    ActionFilter (ModelPhotoshop& init_modelPhotoshop)
        : modelPhotoshop (init_modelPhotoshop)
    { }

    virtual Scene* create (std::vector<void*>* buttons) override
    {
        VectorDec size = {150, 37 * 10};

        Button* button = new Button {size, {361, 40}, *this};
        buttons->push_back (button);

        Scene* sceneParameter = new Scene {};
        sceneParameter->addObject (*button);
        sceneParameter->setIsDraw (false);
        return sceneParameter;
    }

    virtual bool call (Event event) override
    {
        int y = event.getCoord().y;

        int index = y / (kHeightFilterIcon + kFilterOffset);
        // printf ("AAAAAAAAAAAAAAAAAAAA index %d AAAAAAAAAAAAAAAAa\n", index);
        if (index < modelPhotoshop.nFilters)
        {
            modelPhotoshop.filtres[index]->activate();
        }
        return true;

/*
        // int x = event.getCoord().x;
        // int y = event.getCoord().y;

        if (0 * 36 < y && y < 1 * 36)
        {
            Blur (modelCanvas);
            return true;
        }
        if (1 * 36 < y && y < 2 * 36)
        {
            GaussianBlur (modelCanvas);
            return true;
        }
        if (2 * 36 < y && y < 3 * 36)
        {
            UnsharpMask (modelCanvas);
            return true;
        }
        if (3 * 36 < y && y < 4 * 36)
        {
            Invert (modelCanvas);
            return true;
        }
        if (4 * 36 < y && y < 5 * 36)
        {
            Brightness (modelCanvas);
            return true;
        }
        if (5 * 36 < y && y < 6 * 36)
        {
            Contrast (modelCanvas);
            return true;
        }
        return false;
*/
    }
};

class ActionWindow : public Action
{
private:
    ModelPhotoshop& modelPhotoshop;

public:
    ActionWindow (ModelPhotoshop& init_modelPhotoshop)
        : modelPhotoshop (init_modelPhotoshop)
    { }

    virtual Scene* create (std::vector<void*>* buttons) override
    {
        VectorDec size = {130, 37};
        const char* png = "img/menu/window-list.png";

        Button* button = new Button {size, {502, 40}, *this, png};
        buttons->push_back (button);

        Scene* sceneParameter = new Scene {};
        sceneParameter->addObject (*button);
        sceneParameter->setIsDraw (false);
        return sceneParameter;
    }

    virtual bool call (Event event) override
    {
        int x = event.getCoord().x;
        int y = event.getCoord().y;

        if (0 * 37 < y && y < 1 * 37)
        {
            printf ("Please enter the name of the plugin:\n");
            char path[216];
            std::cin >> path;
            modelPhotoshop.addPlugin(path);
            return true;
        }
        return false;
    }
};

/**************************************************************************/

#endif /* STL_MENU_FILE */