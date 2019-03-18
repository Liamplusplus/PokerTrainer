/*
 *
 */

#pragma once

#include <ucurses/ucurses.hpp>

class Game;

namespace cardgame {

    class SingleplayerScreen : public ucurses::State
    {
        public:

            SingleplayerScreen(Application* game);

            void New();
            void Load();

        protected:

            virtual void Initialize();

            ucurses::Menu* menu;
            ucurses::coord2d pos = ucurses::coord2d(0,0);
			Application* app;
    
    };
}
