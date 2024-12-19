#include "create.hpp"
#include "color.hpp"

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
    Button* buttonFile   = new Button {{57, 50},  {0, 0},   "img/menu/file.png"};
    Button* buttonEdit   = new Button {{63, 50},  {57, 0},  "img/menu/edit.png"};
    Button* buttonImage  = new Button {{83, 50},  {120, 0}, "img/menu/image.png"};
    Button* buttonLayer  = new Button {{76, 50},  {203, 0}, "img/menu/layer.png"};
    Button* buttonSelect = new Button {{82, 50},  {279, 0}, "img/menu/select.png"};
    Button* buttonFilter = new Button {{72, 50},  {361, 0}, "img/menu/filter.png"};
    Button* buttonView   = new Button {{69, 50},  {433, 0}, "img/menu/view.png"};
    Button* buttonWindow = new Button {{102, 50}, {502, 0}, "img/menu/window.png"};
    Button* buttonMore   = new Button {{75, 50},  {604, 0}, "img/menu/more.png"};
    main_scene.addObject (*buttonFile);
    main_scene.addObject (*buttonEdit);
    main_scene.addObject (*buttonImage);
    main_scene.addObject (*buttonLayer);
    main_scene.addObject (*buttonSelect);
    main_scene.addObject (*buttonFilter);
    main_scene.addObject (*buttonView);
    main_scene.addObject (*buttonWindow);
    main_scene.addObject (*buttonMore);
}
