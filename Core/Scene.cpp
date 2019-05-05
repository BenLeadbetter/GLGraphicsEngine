/*
*       Source file for the Scene header
*/

// ctor

#include "Scene.hpp"
#include <assert.h>

Scene::Scene()
{
    static bool SceneInsantiated = false;
    
    assert(!SceneInsantiated);      // will ensure only one
                                    // instance of Scene
    
    SceneInsantiated = true;
}