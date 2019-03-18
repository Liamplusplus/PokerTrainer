/*
 * Contains 52 Unique cards
 * Shuffles every hand
 */

#pragma once
#include <vector>
#include <card/Card.hpp>
	
namespace ctk { class RandomGenerator; }

class Deck
{
    public:

        Deck(); 

        void Shuffle(ctk::RandomGenerator& rand_gen);

        inline size_t getSize() { return deck.size(); }

		// I/O
		//
        void write_form(std::ostream& stream);
        void read_form(std::istream& stream);
    
        void write_dump(std::ostream& stream);
        void read_dump(std::istream& stream);
    
        void write_binary(std::ostream& stream) {}
        void read_binary(std::istream& stream)  {}

		Card Top();
		void  Pop() { deck.pop_back(); }
        void  Reset(ctk::RandomGenerator& rand_gen);
        void Erase(int index) { deck.erase(deck.begin() + index); }
        std::vector<Card> deck;

        Card& operator[](int index) { return deck[index]; }
        const Card& operator[](int index) const { return deck[index]; }

    protected:

        // Last element of the array is the top of the deck
        // std::stack does not expose iterators
};
