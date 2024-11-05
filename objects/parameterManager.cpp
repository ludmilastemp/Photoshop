#include "parameterManager.hpp"

/**************************************************************************/

void ParameterManager::addScene (Scene& scene)
{
    scenes.push_back(&scene);
}

void ParameterManager::activate (int scene)
{
    deActivate ();

    if (-1 <= scene && scene < scenes.size())
    {
        activeScene = scene;
        scenes[scene]->setIsDraw (true);
    }
}

void ParameterManager::deActivate ()
{
    if (0 <= activeScene && activeScene < scenes.size())
    {
        scenes[activeScene]->setIsDraw (false);
    }
    activeScene = -1;
}

void ParameterManager::reActivate ()
{
    if (0 <= activeScene && activeScene < scenes.size())
    {
        int scene = activeScene;
        deActivate ();
        activate (scene);
    }
}

/**************************************************************************/

/**************************************************************************/