#ifndef GUARD_SCENE_HPP
#define GUARD_SCENE_HPP

/*
*   Header file for the Scene class
*
*   The scene will hold pointers to all the active objects
*   and will be responsible for updating and drawing 
*   each of them.
*
*/

#include <vector>
#include <memory>
#include "Drawable.hpp"

class Scene
{
    public:

        // ctor: there should only be one instance of the Scene
        Scene();

        //
        void update(float dtime);
        void draw();

        //
        void addActiveDrawable(const Drawable& drawable);

        //

    private:
        
        //
        void removeInactiveDrawables();

        // data
        std::vector<std::shared_ptr<Drawable>>      ActiveDrawables;
};

#endif