#include <poker/Utility.hpp>

int main(int argc, char* argv[])
{
    Hand hand1;
    Hand hand2;
    
    hand1.cards[0] = Card(12, Card::Suit::SPADE);
    hand1.cards[1] = Card(1, Card::Suit::DIAMOND);
    
    hand2.cards[0] = Card(1, Card::Suit::SPADE);
    hand2.cards[1] = Card(5, Card::Suit::HEART);
    
    hand1.calculateStrength();
    hand2.calculateStrength();

    std::cout << "Equity test between hands:\n\n\t" << hand1.getName() << " (" << hand1.getClassification() << ")" << "\n\t";
    std::cout << hand2.getName() << " (" << hand2.getClassification() << ")" << "\n\n";

    std::vector<int> counts;
    ctk::RandomGenerator rand_gen;
    std::vector<Hand> hands;
    hands.reserve(2);
    hands.push_back(hand1);
    hands.push_back(hand2);

    int sample_size = 1000;

    CalculateEquity(hands, counts, rand_gen, sample_size);

    std::cout << "After " << sample_size << " simulations, " << hand1.getName() << " won ";
    std::cout << std::to_string(counts[0]) << " times and " << hand2.getName() << " won ";
    std::cout << std::to_string(counts[1]) << " times" << std::endl;

}
