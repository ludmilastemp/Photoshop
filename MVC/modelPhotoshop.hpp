#ifndef STL_MODEL_PHOTOSHOP
#define STL_MODEL_PHOTOSHOP

#include <vector>
#include "modelCanvas.hpp"
#include "controllerPhotoshop.hpp"
#include "Managers/actions.hpp"

class ModelPhotoshop
{
public:
    ModelCanvas modelCanvas;
    ModelButton modelButton;
    Scene& main_scene;
    size_t nTool = 0;
    size_t nParameters = 0;

    ModelPhotoshop (Scene& init_main_scene)
        : modelCanvas (init_main_scene), main_scene(init_main_scene)
    {
        /*
        * Создание кнопки для tools
        */
        ActionToolbar* actionToolbar = new ActionToolbar {modelCanvas, {kWidthToolbarCorner, kHeightToolbarCorner}};
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
        nTool++;
    }

    void addParameter (Action& action, const char* pngIcon)
    {
        std::vector<void*> buttons;
        Scene* sceneParameter = action.create (&buttons);

        for (int i = 0; i < buttons.size(); i++)
            modelButton.addButton (*(Button*)buttons[i]);

        main_scene.addScene (*sceneParameter);
        modelCanvas.parameterManager.add (*sceneParameter);

        Button* buttonIcon = new Button {{kWidthIcon, kHeightIcon}, {kWidthParameterManagerCorner, kHeightParameterManagerCorner + (int)nParameters * (kHeightIcon + kOffsetIcon)}, pngIcon};
        main_scene.addObject (*buttonIcon);

        nParameters++;
    }
};

#endif /* STL_MODEL_PHOTOSHOP */
