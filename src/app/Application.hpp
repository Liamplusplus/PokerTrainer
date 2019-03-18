/*
 * Texas Holdem Application
 */
#pragma once
#include <ucurses/ucurses.hpp>

// Game data created dynamically due to option of selecting from various  games
// Forward declarations necessary for this

namespace cardgame {

    class Game;

    class Application : public ucurses::Application
    {
        public:

            Application();
            ~Application();

            void SetupGame(unsigned int type);
            void StartGame();
            
            virtual void onClose();
            virtual void onStart();

        protected:

            void Update();

        public:

            Game* game_data;
            // Level of indirection between the application and game's data model
            // Let Game class decide what to protect from outside classes
    };
}
