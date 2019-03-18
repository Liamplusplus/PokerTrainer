/*
 * Outsourced gui state code to reduce clutter in GameUI class
 */

#pragma once
#include <blackjack/State.hpp>

namespace ucurses { class Window; }

class Game;

namespace blackjack {
    
    class GameUI;

    class InitialDeal : public blackjack::State
    {
        public:

            static void Setup(GameUI* game_ui);
            static void Advance(GameUI* game_ui);
            
            static void Callback(Game* game_data, ucurses::Window* target);
    };
}
