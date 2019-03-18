/*
 * UI for house poker setup
 */

#pragma once

#include <ucurses/ucurses.hpp>

namespace cardgame
{
    class Application;
}

namespace house {

    class SetupUI : public ucurses::State
    {
        public: 
            
            SetupUI(cardgame::Application* handle);

        protected:

            void Initialize();

            ucurses::Menu* menu;
            cardgame::Application* app;
    };

}
