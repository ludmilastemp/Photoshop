#ifndef STL_MODEL_PHOTOSHOP
#define STL_MODEL_PHOTOSHOP

#include <vector>
#include "Managers/manager.hpp"
#include "modelCanvas.hpp"
#include "controllerPhotoshop.hpp"
#include "Managers/actions.hpp"
#include "objects/filter.hpp"

#include <dlfcn.h>
#include "PsSPI.hpp"

class ModelPhotoshop
{
public:
    ModelCanvas modelCanvas;
    ModelButton modelButton;
    Scene& main_scene;
    size_t nTool = 0;
    size_t nFilters = 0;
    size_t nParameters = 0;
    MenuManager menuManager;
    std::vector<Filter*> filtres;
    Scene* filtersScene;
    std::vector <void*> dll;
    PsSPI* psspi;

    ModelPhotoshop (Scene& init_main_scene)
        : modelCanvas (init_main_scene), main_scene(init_main_scene)
    {
        /*
        * Создание кнопки для tools
        */
        ActionToolbar* actionToolbar = new ActionToolbar {this, modelCanvas, {kWidthToolbarCorner, kHeightToolbarCorner}};
        Button* buttonToolbar = new Button {{kWidthToolbar, kHeightToolbar}, {kWidthToolbarCorner, kHeightToolbarCorner}, *actionToolbar};
        modelButton.addButton (*buttonToolbar);

        /*
        * Создание кнопки для parameters
        */
        ActionParameterManager* actionParameterManager = new ActionParameterManager {modelCanvas, {kWidthParameterManagerCorner, kHeightParameterManagerCorner}};
        Button* buttonParameterManager = new Button {{kWidthParameterManager, kHeightParameterManager}, {kWidthParameterManagerCorner, kHeightParameterManagerCorner}, *actionParameterManager};
        modelButton.addButton (*buttonParameterManager);
    }

    void addTool (Tool& tool, const char* png)
    {
        modelCanvas.addTool (tool);
        Button* button = new Button {{kWidthIcon, kHeightIcon}, {kWidthToolbarCorner, kHeightToolbarCorner + (int)nTool * (kHeightIcon + kOffsetIcon)}, png};
        main_scene.addObject (*button);
        Button* buttonPng = new Button {{kWidthIcon, kHeightIcon}, {kWidthToolbarCorner, kHeightToolbarCorner - kHeightIcon}, png};
        tool.parameterButtons.addObject (*buttonPng);
        nTool++;
    }

    void addFilter (Filter& filter, const char* png)
    {
        Button* button = new Button {{kWidthFilterIcon, kHeightFilterIcon}, {kWidthFilterbarCorner, kHeightFilterbarCorner + (int)nFilters * (kHeightFilterIcon + kFilterOffset)}, png};
        filtersScene->addObject(*button);
        filtres.push_back(&filter);
        nFilters++;
    }

    void addPlugin (const char* path)
    {
        void* ptr = dlopen(path, RTLD_NOW | RTLD_LOCAL);
        if (!ptr) {
            fprintf(stderr, "%s\n", dlerror());
            return;
        }
        dll.push_back(ptr);

        void (*func)(PsSPI*) = (void (*)(PsSPI*)) dlsym (ptr, "loadPlugin");
        (*func)( psspi );
    }

    void activateTool () { printf ("activateTool\n"); menuManager.deactivate(); }
    void activateMenu () { printf ("activateMenu\n"); modelCanvas.setActiveTool(-1); }

    void setPsspi (PsSPI* new_psspi)
    {
        psspi = new_psspi;
    }

    void closePlugins ()
    {
        for (void* ptr : dll)
            dlclose(ptr);
    }

    void addParameter (Action& action, const char* pngIcon)
    {
        // std::vector<void*> buttons;
        // Scene* sceneParameter = action.create (&buttons);

        // for (int i = 0; i < buttons.size(); i++)
        //     modelButton.addButton (*(Button*)buttons[i]);

        // main_scene.addScene (*sceneParameter);
        // modelCanvas.parameterManager.add (*sceneParameter);

        // Button* buttonIcon = new Button {{kWidthIcon, kHeightIcon}, {kWidthParameterManagerCorner, kHeightParameterManagerCorner + (int)nParameters * (kHeightIcon + kOffsetIcon)}, pngIcon};
        // main_scene.addObject (*buttonIcon);

        // nParameters++;
    }
};

#endif /* STL_MODEL_PHOTOSHOP */
