/*
 *
 *
 */

#pragma once
#include <blackjack/Box.hpp>
#include <iostream>

#define DEALER_BOX 6

class BoxManager
{
	public:

        enum class State    { SUCCESS, FAILURE };
        enum class Result   { WIN = 0, LOSS, STANDOFF };

        friend class Game;

		BoxManager();

		int 	           addBet(float value, int pos);
        int                addCard(Card card);             /* Adds to current active box */
        Result             Compare();

		// Increment

		int				Next();
		int				nextActive();

		void setActive(int index);

		// Access
		
		Box&			Get(int index);
		Box&			getActive();
		int 			getActiveIndex();	

        size_t size() const;

        void write_form(std::ostream& stream);

        bool anyActive();

	protected:

		void Reset(); 
		std::array<Box, 6> 	boxes;
		Box 				dealer;
		// Receives card at end of dealing phase
		// Always hits if below 17

        // 0 - 5. 6 For Dealer box
		int current_box;

};
