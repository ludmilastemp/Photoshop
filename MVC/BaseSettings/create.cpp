#include "create.hpp"
#include "MVC/Managers/actions.hpp"
#include "color.hpp"
#include "menu.hpp"

void CreateBaseSettings (ModelPhotoshop& modelPhotoshop) 
{
    ModelCanvas& modelCanvas = modelPhotoshop.modelCanvas;
    ModelButton& modelButton = modelPhotoshop.modelButton;
    Scene& main_scene = modelPhotoshop.main_scene;

    /*
    * Создание кнопки для color
    */
    ActionColor* actionColor = new ActionColor {modelCanvas};
    std::vector<void*> buttons;
    Scene* sceneParameter = actionColor->create (&buttons);

    for (int i = 0; i < buttons.size(); i++)
        modelButton.addButton (*(Button*)buttons[i]);
    buttons.clear();
    main_scene.addScene (*sceneParameter);

    ActionColorIcon* actionColorIcon = new ActionColorIcon {modelCanvas.parameterManager};
    Button* buttonIcon = new Button {{kWidthColor, kHeightColor},  {kWidthColorCorner, kHeightColorCorner}, *actionColorIcon, "img/color_icon.png"};
    modelButton.addButton (*buttonIcon);
    main_scene.addObject (*buttonIcon);

    modelCanvas.parameterManager.color = actionColor;
    printf ("parameterManager %lu color\n", modelCanvas.parameterManager.objects.size());
    modelCanvas.parameterManager.add (*sceneParameter);

    /*
    * Создание верхнего меню 
    */
    ActionFile* actionFile = new ActionFile {modelCanvas};  
    sceneParameter = actionFile->create (&buttons);
    for (int i = 0; i < buttons.size(); i++)
        modelButton.addButton (*(Button*)buttons[i]);
    buttons.clear();
    main_scene.addScene (*sceneParameter);
    modelPhotoshop.menuManager.add(*sceneParameter);

    ActionIcon* actionFileIcon = new ActionIcon {&modelPhotoshop, modelPhotoshop.menuManager};
    Button* buttonFile   = new Button {{57, 50},  {0, 0},  *actionFileIcon, "img/menu/file.png"};
    modelButton.addButton (*buttonFile);
    main_scene.addObject (*buttonFile);

    Button* buttonEdit   = new Button {{63, 50},  {57, 0},  "img/menu/edit.png"};
    Button* buttonImage  = new Button {{83, 50},  {120, 0}, "img/menu/image.png"};
    Button* buttonLayer  = new Button {{76, 50},  {203, 0}, "img/menu/layer.png"};
    Button* buttonSelect = new Button {{82, 50},  {279, 0}, "img/menu/select.png"};

    ActionFilter* actionFilter = new ActionFilter {modelPhotoshop};  
    sceneParameter = actionFilter->create (&buttons);
    for (int i = 0; i < buttons.size(); i++)
        modelButton.addButton (*(Button*)buttons[i]);
    buttons.clear();
    main_scene.addScene (*sceneParameter);
    modelPhotoshop.menuManager.add(*sceneParameter);
    modelPhotoshop.filtersScene = sceneParameter;

    ActionIcon* actionFilterIcon = new ActionIcon {&modelPhotoshop, modelPhotoshop.menuManager};
    Button* buttonFilter   = new Button {{72, 50},  {361, 0},  *actionFilterIcon, "img/menu/filter.png"};
    modelButton.addButton (*buttonFilter);
    main_scene.addObject (*buttonFilter);

    Button* buttonView   = new Button {{69, 50},  {433, 0}, "img/menu/view.png"};

    ActionWindow* actionWindow = new ActionWindow {modelPhotoshop};  
    sceneParameter = actionWindow->create (&buttons);
    for (int i = 0; i < buttons.size(); i++)
        modelButton.addButton (*(Button*)buttons[i]);
    buttons.clear();
    main_scene.addScene (*sceneParameter);
    modelPhotoshop.menuManager.add(*sceneParameter);

    ActionIcon* actionWindowIcon = new ActionIcon {&modelPhotoshop, modelPhotoshop.menuManager};
    Button* buttonWindow   = new Button {{102, 50}, {502, 0},  *actionWindowIcon, "img/menu/window.png"};
    modelButton.addButton (*buttonWindow);
    main_scene.addObject (*buttonWindow);

    Button* buttonMore   = new Button {{75, 50},  {604, 0}, "img/menu/more.png"};
    main_scene.addObject (*buttonEdit);
    main_scene.addObject (*buttonImage);
    main_scene.addObject (*buttonLayer);
    main_scene.addObject (*buttonSelect);
    main_scene.addObject (*buttonView);
    main_scene.addObject (*buttonMore);
}
