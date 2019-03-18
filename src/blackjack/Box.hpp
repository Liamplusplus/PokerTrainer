/*
 * Stores bets and cards
 */

#pragma once

#include <utility>
#include <array>

#include <card/Card.hpp>

class Box
{
    public:

		// Seperated non mutually-exclusive enums into booleans FULL and BUST
		enum Status 		{ BLACKJACK, TWENTY_ONE, UNDER};
        Box();

        // Returns sum of all bets
        float getSum();

		Status getStatus();
		// Determine status of box
		void setStatus();
        bool Active();
        void setActive(bool b);

        std::pair<short, short> getCount();
		// Two possible values
		// Every ace is a one || One ace is an 11
		// getCount().first being the safest and
		// getCount().second being the highest
		// getCount().second == -1 if over 22 or no aces exist
        // Returns highest score under 21
		//
        short Highest();

		void addCard(Card& card);
		Card Bottom();				// Returns the first non-null card
		Card Top();
	
		// Hands
		bool Busted();				/* Too many */
		bool Full();

		bool Empty();				/* No cards */
		bool inActive();			/* No bets */
		int nCards();
        
		bool addBet(float f);		// Returns false if box is full

		float bet;

		void write_form(std::ostream& stream);


    protected:

        std::array<Card, 5> cards;
		Status status;

        bool active;
		bool busted;
		bool full;
        // Set to true on InitialDeal phase if sum is greater than zero
        // Set to inactive if already payed out due to blackjack
};

