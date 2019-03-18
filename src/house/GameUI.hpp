/*
 * UI for house poker
 */

#pragma once
#include <array>
#include <app/GameUI.hpp>
#include <house/Game.hpp>
#include <chrono>

namespace cardgame
{
    class Application;
    class Game;
}

namespace house {

    class Game;
    class GameUI : public ::GameUI
    {
        public: 
            
            GameUI(cardgame::Application* handle, house::Game* game_handle);
            
        protected:

            void Initialize();
            void InitializeCommands();

            void RenderTest();
            void RenderCards();

            void InitialDeal();
            void NextStreet();
            void Deal(int ncards);
            void Reset();

            void updateTotals();
            void FinishHand(int delay = 0);
            void calculatePayout();

            virtual void Update();
            void Fold();

            void changeBet(float amount);
            void placeBet();
            ucurses::Label* player_info;
            ucurses::Label* bet_display;
            ucurses::Label* dealer_box;

            ucurses::Label* help;
            
            ucurses::Canvas* player_display;
            ucurses::Canvas* dealer_display;
            ucurses::Canvas* board;
            // 27 * 11

            // UI tracks game state to update UI elements
            Game* game;

            std::chrono::steady_clock::time_point timepoint;
            
            int deal_initial;
            int deal_board;
            bool bhelp;
    };

}
