/*
 * The game class should encompass the organisation of data and game flow
 * whilst the UI should only handle visuals and updating of widgets.
 */

#pragma once
#include <app/Game.hpp>
#include <poker/Hand.hpp>

namespace house 
{
    class Game : public cardgame::Game
    {
        public:
            
            Game();

            virtual void Start();
            virtual void Setup();

            void InitialDeal();
            void NextStreet();
            void Reset();

            void PlaceBet();
            int Play(float multiplier);
            float calculatePayout();

            int changeBet(float amount);

            Hand player_hand;
            Hand dealer_hand;
            Board board;

            float ante;
            float play;

        protected:

    };
}
