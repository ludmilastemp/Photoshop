#include "parameterManager.hpp"

/**************************************************************************/

void ParameterManager::addScene (Scene& scene)
{
    scenes.push_back(&scene);
}

void ParameterManager::activate (Scene& scene)
{
    deActivate ();
    scene.setIsDraw (true);
    activeScene = &scene;
}

void ParameterManager::deActivate ()
{
    if (activeScene != nullptr)
        activeScene->setIsDraw (false);
    activeScene = nullptr;
}

/**************************************************************************/

/**************************************************************************/