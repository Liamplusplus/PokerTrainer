#include <poker/Utility.hpp>
#include <poker/Board.hpp>
#include <card/Deck.hpp>
using namespace std;

void CalculateEquity(std::vector<Hand>& hands, std::vector<int>& counts, ctk::RandomGenerator& rand_gen, int sample_size)
{
    // for sample_size, runout board and calculate winner, accumulate counts and calculate equities
    std::vector<Card> dead;

    for (auto& hand : hands)
    {
        dead.push_back(hand.cards[0]);
        dead.push_back(hand.cards[1]);
    }
    
    // Remove any dead cards from simulation deck
    Deck deck;
    for (int i = 0; i < dead.size(); i++)
    {
        for (int j = 0; j < deck.getSize(); j++)
        {
            if (dead[i] == deck[j])
                deck.Erase(j);
        }
    }

    Board board;
    counts.reserve(hands.size());
    for (int i = 0; i < hands.size(); i++)
        counts.push_back(0);

    for (int j = 0; j < sample_size; j++)
    {
        deck.Shuffle(rand_gen);

        for (int i = 0; i < 5; i++)
        {
            board.cards[i] = deck.Top();
        }

        for (auto& hand : hands)
            hand.calculateStrength(board);

        int strongest = -1;
        strength_struct last_hand_str = hands[0].strength;
        for (int i = 1; i < hands.size(); i++)
        {
            if (hands[i].strength > last_hand_str)
                strongest = i;
            else if (last_hand_str > hands[i].strength)
                strongest = i - 1;
        }
        if (strongest != -1)
            counts[strongest]++;
        for (int i = 0; i < 5; i++)
            deck.deck.push_back(board.cards[i]);

        board.Reset();
    }
}
// Returns highest card of the highest straight with Ace being 14 and 1
int Straight(std::vector<Card>& cards)
{
    // First check for highest straight sorted highest to lowest
    int conseq = 1;
    int value = cards[0].getValue();
    for (int i = 1; i < cards.size(); i++)
    {
        if (cards[i].getValue() == value - 1)
            conseq++;
        else if (cards[i].getValue() != value) // If straight contains pair, dont reset count
            conseq = 1;
        value = cards[i].getValue();
        if (conseq == 5)
            return value + 4;
    }

    // Second, check for straight sorted lowest to highest
    std::sort(cards.begin(), cards.end(), 
            [](Card& a, Card& b) { return a.getStraightValue() < b.getStraightValue(); });

    conseq = 1;
    value = cards[0].getStraightValue();

    for (int i = 1; i < cards.size(); i++)
    {
        if (cards[i].getStraightValue() == value + 1)
            conseq++;
        else if (cards[i].getStraightValue() != value)
            conseq = 1;

        value = cards[i].getStraightValue();
        if (conseq == 5)
            return value;
    }
    return -1;
}

int StraightFlush(std::vector<Card>& cards, int suit)
{
    std::vector<Card> flush;
    flush.reserve(7);
    for (auto& card : cards)
        if (card.suit == suit)
            flush.push_back(card);

    return Straight(flush);
}

// Returns highest flush 
std::pair<int, int> Flush(std::vector<Card>& cards)
{
    std::array<std::pair<int, int>, 4> counts;
    for (auto& card: cards)
    {
        counts[card.suit].first++; 
        if (card.getValue() > counts[card.suit].second)
            counts[card.suit].second = card.getValue();
        if (counts[card.suit].first >= 5)
            return std::make_pair(card.suit, counts[card.suit].second);
    }

    return std::pair<int, int>(-1, -1);
}


std::pair<int, int> NSame(std::vector<Card>& cards, int ignore)
{
    int same = 1;
    std::pair<int, int> data(1, 0);
    int value = cards[0].getValue();
    for (int i = 1; i <= cards.size(); i++)
    {
        if (value != ignore)
        {
            // If card = last card.value increment same. Else save highest count and reset count
            if (cards[i].getValue() == value) same++;
            else
            {
                if (same > data.first)
                {
                    data.first = same;
                    data.second = value;
                }
                same = 1;
            }
        }
        value = cards[i].getValue();
    }
    return data; 
}

// Takes vector of cards sorted from highest to lowest and returns n highest values, ignoring list 
void getHighestCards(std::vector<int>& src, std::vector<Card>& cards, int n, std::initializer_list<int> ignore)
{
    src.reserve(n);
    bool skip;
    int count = 0;
    for (auto& card: cards)
    {
        if (count == n) 
            return;
        for (auto& val : ignore)
            card.getValue() == val ? skip = true : skip = false;
        if (!skip)
        {
            src.push_back(card.getValue());
            ++count;
        }
    }
}
