#pragma once
#include <card/Card.hpp>
#include <poker/Board.hpp>
#include <array>
#include <tuple>
#include <vector>
#include <utility>

/* Hand Classification */

/* 
 * The hand to win the pot at showdown is the strongest five card hand made
 * from seven cards, the players hole cards and the board
 *
 * Hands strength can be classified from the following table:
 *
 *  Royal Flush - 10-J-Q-K-A same suit
 *  Straight Flush - Five consecutive cards of same suit
 *  Four of a kind - Four cards of the same value eg. 8-8-8-8-J
 *  Full House - Three of a kind and a pair e.g 8-8-8-J-J
 *  Flush - Five of the same suit  
 *  Straight - Five cards of consecutive value  
 *  Three of a kind - Three cards of same value e.g K-K-K-Q-10  
 *  Two Pair - Two pairs  
 *  Pair - Two cards of same value  
 *  High card - Highest cards relative to board  
 *
 *  When two hands are classified to have the same strength, it is the highest to win.
 */
using strength_struct = std::tuple<short, short, short, short, short, short>;
/*
bool operator==(const strength_struct& lhs, const strength_struct& rhs)
{ 
    return (std::get<0>(lhs) == std::get<0>(rhs) && std::get<1>(lhs) == std::get<1>(rhs) &&
            std::get<2>(lhs) == std::get<2>(rhs) && std::get<3>(lhs) == std::get<3>(rhs) &&
            std::get<4>(lhs) == std::get<4>(rhs) && std::get<5>(lhs) == std::get<5>(rhs)); 
}
bool operator>(const strength_struct& lhs, const strength_struct& rhs)
{
    return (std::get<0>(lhs) > std::get<0>(rhs) || std::get<1>(lhs) > std::get<1>(rhs) ||
            std::get<2>(lhs) > std::get<2>(rhs) || std::get<3>(lhs) > std::get<3>(rhs) ||
            std::get<4>(lhs) > std::get<4>(rhs) || std::get<5>(lhs) > std::get<5>(rhs));
}
*/
/* 
 * Strength struct used to hold maximum amount of information about the strength of a hand
 * Without a flop, [0] holds the highest card of the hole cards, [1] holds the difference in value
 * and [2] holds whether it is suited or not.
 *
 * Post flop the strength can hold information of the strongest made hand the hole cards can make given
 * the flop
 */
struct Hand
{
    Hand();
    enum Strength { HIGH = 0, PAIR, TWO_PAIR, TRIPS, STRAIGHT, FLUSH, BOAT, QUADS, STRAIGHTFLUSH, ROYALFLUSH, STRENGTHNUM };
    std::array<Card, 2> cards;
    void Reset();

    void setVisible(bool b);

    bool Empty() { return (cards[0].Null() || cards[1].Null()); }

    std::string getStrengthName();
    std::string getName();
    std::string getClassification();
    void calculateStrength();

    // Strength is calculated on each street to avoid unecessary processing
    void calculateStrength(Board& board);
    strength_struct strength;
   
};

 
