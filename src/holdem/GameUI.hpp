/*
 * UI for Texas Hold'em poker
 */

#pragma once
#include <array>
#include <app/GameUI.hpp>
#include <holdem/Game.hpp>
#include <chrono>

namespace cardgame
{
    class Application;
    class Game;
}

namespace holdem {

    class Game;
    class GameUI : public ::GameUI
    {
        public: 
            
            GameUI(cardgame::Application* handle, holdem::Game* game_handle);
            

        protected:

            void Initialize();

            void InitialDeal();
            void RenderCards();
            void NextStreet();
            void RenderButton();
            //void Reset();

            //virtual void Update();

            //void changeBet(float amount);
            //void placeBet();
            
            // UI tracks game state to update UI elements
            Game* game;

            std::array<ucurses::Canvas*, 9> displays;
            std::array<ucurses::Label*, 9> display_info;
            ucurses::Canvas* board;
            ucurses::Label* button;

            std::chrono::steady_clock::time_point timepoint;
            
            int dealing;
    };

}
