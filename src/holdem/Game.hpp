#pragma once
#include <app/Game.hpp>
#include <poker/Hand.hpp>
#include <poker/Board.hpp>

namespace holdem
{
    class Game : public cardgame::Game
    {
        public:

            Game();

            virtual void Start();
            virtual void Setup();

            void InitialDeal();
            void NextStreet();

            unsigned short getPlayerSeat() { return player_seat; }
            unsigned short getButtonPos() { return button_pos; }
            Hand* getHand(int index);
            Board board;

        protected:

            unsigned short player_seat;
            unsigned short button_pos;
            std::array<Hand, 9> hands;
    };
    
}
