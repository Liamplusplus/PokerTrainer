#pragma once
#include <array>

//GUI
#include <ucurses/ucurses.hpp>
#include <blackjack/InitialDeal.hpp>

using namespace ucurses;

class Game;

namespace blackjack {

    class GameUI : public ucurses::State
    {

        friend class InitialDeal;
        public:

            GameUI(Game* game);

			// Game states
			void Hit();
			void Sit();
			void FinalDeal();
			void setup();
			void GamePhase();
			void InitialDeal();
            void displayPlayerInfo();
			void acceptDefeat();

        protected:

            void Initialize();

			// Widgets
            std::array<Label*, 6> boxes;
            std::array<Label*, 7> counts;
            TextEntry* bet;
			Label* player_info;

            Game* game;

            void placeBet(int boxn);


			void RefreshGraphics();
            void RefreshBoxes();
            void refreshBoxCount(int index);

            void Payout();

			// Everytime box changes update UI to display active box
			void RefreshActiveBox();
    };

}
