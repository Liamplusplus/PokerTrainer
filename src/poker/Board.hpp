/*
 * Board analysis is very important to AI making good decisions. Good players bet
 * on relative hand strength and determine how strong their opponents hand range is
 * and how that range hits the board.
 */

#pragma once
#include <array>
#include <card/Card.hpp>

enum Street { FLOP = 0, TURN = 3, RIVER = 4, RESET = -1};

struct Board
{
    void Reset() { for (auto & card : cards) card.value = -1; }
    void Refresh();
    Street nextStreet();
    Street currentStreet();
    bool flushPossible() { return nsame_suit >= 3; }
    void setVisible(bool b);

    int nCards();

    std::array<Card, 5> cards;
    int nsame_suit;
    int nsame_val;
    bool straight_possible;
    int highest_card;
};
