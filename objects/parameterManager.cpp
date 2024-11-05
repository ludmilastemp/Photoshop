#include "parameterManager.hpp"

/**************************************************************************/

void ParameterManager::addScene (Scene& scene)
{
    scenes.push_back(&scene);
}

void ParameterManager::activate (Scene& scene)
{
    deActivate ();
    activeScene = &scene;
    scene.setIsDraw (true);
}

void ParameterManager::deActivate ()
{
    if (activeScene != nullptr)
        activeScene->setIsDraw (false);
    activeScene = nullptr;
}

void ParameterManager::reActivate ()
{
    if (activeScene == nullptr)
        return;

    Scene* scene = activeScene;
    scene->setIsDraw (false);
    deActivate ();
    activeScene = scene;
    scene->setIsDraw (true);
}

/**************************************************************************/

/**************************************************************************/