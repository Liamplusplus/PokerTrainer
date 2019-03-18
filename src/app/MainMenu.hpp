/*
 * Main menu
 */
#pragma once

#include <ucurses/ucurses.hpp>

namespace cardgame 
{
    class Application;

    class MainMenu : public ucurses::State
    {
        enum Selection { POKER = 0, BLACKJACK, SETTINGS};

        public:

        MainMenu(Application* handle);
        void Update();

        protected:

        void Select();
        virtual void Initialize();

        ucurses::Menu* mode_select;
        Application* app;
    };
}
