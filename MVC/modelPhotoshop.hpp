#ifndef STL_MODEL_PHOTOSHOP
#define STL_MODEL_PHOTOSHOP

#include <vector>
#include "modelCanvas.hpp"
#include "controllerCanvas.hpp"

class ModelPhotoshop
{
public:
    ModelCanvas modelCanvas;
    ModelButton modelButton;
    Scene& main_scene;
    size_t nTool;
    size_t nParameters;

    ModelPhotoshop (Scene& init_main_scene)
        : modelCanvas (init_main_scene), main_scene(init_main_scene), nTool (0)
    {
        /*
        * Создание кнопки для tools
        */
        ActionToolbar* actionToolbar = new ActionToolbar {modelCanvas, {25, 100}};
        Button* buttonToolbar = new Button {{50, 400}, {25, 100}, *actionToolbar};
        modelButton.addButton (*buttonToolbar);

        /*
        * Создание кнопки для parameters
        */
        ActionParameterManager* actionParameterManager = new ActionParameterManager {modelCanvas, {725, 100}};
        Button* buttonParameterManager = new Button {{50, 400}, {725, 100}, *actionParameterManager};
        modelButton.addButton (*buttonParameterManager);
    }

    void addTool (Tool& tool, const char* png)
    {
        modelCanvas.addTool (tool);
        Button* button = new Button {{kWidthIcon, kHeightIcon}, {25, 100 + (int)nTool * 60}, png};
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
        modelCanvas.parameterManager.addScene (*sceneParameter);

        Button* buttonIcon = new Button {{kWidthIcon, kHeightIcon}, {725, 100 + (int)nParameters * 60}, pngIcon};
        main_scene.addObject (*buttonIcon);

        nParameters++;
    }
};


#endif /* STL_MODEL_PHOTOSHOP */
