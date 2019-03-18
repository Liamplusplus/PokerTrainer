#include <poker/Hand.hpp>

using namespace std;

int main()
{
    Hand hand;

    hand.cards[0] = Card(11, Card::Suit::SPADE);
    hand.cards[1] = Card(8, Card::Suit::SPADE);
    hand.calculateStrength();

    std::cout << hand.getName() << std::endl;
    std::cout << hand.getClassification() << std::endl;
}
