#include <card/Deck.hpp>
#include <app/Config.hpp>

#include <algorithm>
#include <fstream>

#include <ctk/random/RandomGenerator.hpp>

Deck::Deck()
{
	// Fill the deck with 52 unique cards
    for (int value = 1; value <= 13; value++)
        for (int suit = 0; suit < Card::Suit::NUMSUIT; suit++)
            deck.emplace_back(value, static_cast<Card::Suit>(suit));

    if (deck.size() != 52)
    {
        std::fstream logfile(game::log, std::ios_base::out);
        logfile << "Error: Deck size is not equal to 52" << std::endl;
    }
}
		
Card Deck::Top()
{ 
    Card card = deck.back();
    deck.pop_back();
    return card;
}

void Deck::Shuffle(ctk::RandomGenerator& rand_gen)
{
    std::shuffle ( deck.begin(), deck.end(), rand_gen.Generate() );
}

void Deck::Reset(ctk::RandomGenerator& rand_gen)
{
    deck.clear();
    for (int value = 1; value <= 13; ++value)
        for (int suit = 0; suit < Card::Suit::NUMSUIT; ++suit)
            deck.emplace_back(value, static_cast<Card::Suit>(suit));

    Shuffle(rand_gen);
}


void Deck::write_form(std::ostream& stream)
{
    stream << deck.size() << std::endl;
    for (int i = 0; i < deck.size(); ++i)
        deck[i].write_form(stream);
}
void Deck::read_form(std::istream& stream)
{
    size_t size;
    stream >> size;
    deck.resize(size);
    for (int i = 0; i < deck.size(); ++i)
        deck[i].read_form(stream);
}

void Deck::write_dump(std::ostream& stream)
{
    
}
void Deck::read_dump(std::istream& stream)
{
    
}
