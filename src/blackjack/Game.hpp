/*
 * Handle all logic and ensure the rules are carried out
 *
 */

#pragma once
#include <fstream>
#include <array>

#include <card/Deck.hpp>
#include <blackjack/BoxManager.hpp>
#include <player/Player.hpp>

#include <ctk/random/RandomGenerator.hpp>

class Game
{
    public:

		enum class State 			{ PLACE_BETS = 0, INITIAL_DEAL, PLAY, DEAL, PAY}; 
		enum class InitialState		{ FIRST_ROUND = 0, DEALER, SECOND_ROUND };
		enum class FinalState		{ DEAL, PAYOUT };

        Game();

		/* Game Flow */

        int InitialDeal();
		InitialState initial_state;
		int GamePhase();
		Card FinalDeal();
		void Payout();

		void Quit();
		void Delete();
		void Next();
        void New(const std::string& name);

		// Empties all boxes and resets statuses
		// Called on quit and at the end of each hand
        void Reset();

		int Hit();
		int Sit();
        int addBet(float value, int box);

		/* Components */

        Deck deck;

		BoxManager box_manager;
        // Pays all players for a given box
        void Pay(int box_index, float factor);

		/* Players */

		Player& getPlayer();

		void logState();

	protected:

		State state;

		ctk::RandomGenerator rand_gen;

		bool active;
};
