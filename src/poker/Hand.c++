#include <poker/Hand.hpp>
#include <poker/Board.hpp>

using namespace std;

int main()
{
    Board board;
    Hand hand;

    hand.cards[0] = Card(7, Card::Suit::HEART);
    hand.cards[1] = Card(5, Card::Suit::HEART);

    board.cards[0] = Card(7, Card::Suit::HEART);
    board.cards[1] = Card(7, Card::Suit::HEART);
    board.cards[2] = Card(5, Card::Suit::HEART);

    hand.calculateStrength(board);
    std::cout << get<0>(hand.strength) << " " << get<1>(hand.strength) << " " << get<2>(hand.strength) << " ";
    std::cout << get<3>(hand.strength) << " " << get<4>(hand.strength) << " " << get<5>(hand.strength) << std::endl;
    std::cout << hand.getStrengthName() << std::endl;
    
    
}
