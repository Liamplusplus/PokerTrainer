#pragma once
#include <iostream>
#include <string>

struct Card
{
    // Constants and enums
    enum Suit { HEART = 0, DIAMOND, SPADE, CLUB, NUMSUIT };
    enum Special { JACK = 11, QUEEN, KING, ACE, NUMSPECIAL };

    // Data 
    int value; 
    Suit suit;
    bool showing;

    Card(int value, int suit);
    Card() : value(-1), suit(Suit::HEART), showing(false) {}

	Card(const Card& src)
	{
		value = src.value;
		suit = src.suit;
	}

    void setVisible(bool b);

    // Ace is treated as 14
    int getValue();
    // Ace is treated as 1
    int getStraightValue();

	bool Null() { return value == -1; }
    std::string getName();

    // I/O
    void write_form(std::ostream& stream) const;
    void read_form(std::istream& stream);
    
    void write_dump(std::ostream& stream) const;
    void read_dump(std::istream& stream);
    
    void write_binary(std::ostream& stream) {}
    void read_binary(std::istream& stream) {}
};

inline bool operator==(const Card& lhs, const Card& rhs)
{ return (lhs.value == rhs.value && lhs.suit == rhs.suit); }

static const std::string suit_names[Card::Suit::NUMSUIT] = { "Hearts", "Diamonds", "Spades", "Clubs" };
static const std::string card_names[] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
