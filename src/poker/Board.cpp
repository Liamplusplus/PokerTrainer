#include <poker/Board.hpp>

Street Board::nextStreet()
{
    if (cards[FLOP].value == -1)
        return FLOP;
    else if (cards[TURN].value == -1)
        return TURN;
    else if (cards[RIVER].value == -1)
        return RIVER;
    else
        return RESET;
}

Street Board::currentStreet()
{
    if (cards[4].value != -1)
        return RIVER;
    else if (cards[3].value != -1)
        return TURN;
    else if (cards[2].value != -1)
        return FLOP;
}

void Board::Refresh()
{
    setVisible(true);    
}

int Board::nCards()
{
    int counter = 0;
    for (auto& card : cards)
        if (card.value != -1)
            ++counter;
    return counter;
}

void Board::setVisible(bool b)
{
    for (auto& card : cards)
        card.showing = b;
}
