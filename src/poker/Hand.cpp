#include <poker/Hand.hpp>
#include <algorithm>
#include <cstdlib>
#include <poker/Utility.hpp>

// Information required to classify hand strength
// tuple<1> is used to represent strength type
// tuple<2> is used to represent second pair or second highest card
   
Hand::Hand()
{
    strength = strength_struct(0, 0, 0, 0, 0 ,0);
}

void Hand::Reset() 
{ 
    for (auto & card : cards) card.value = -1; 
    strength = strength_struct(0, 0, 0, 0, 0 ,0);
}

void Hand::setVisible(bool b)
{
    cards[0].showing = b;
    cards[1].showing = b;
}

std::string Hand::getName()
{
    std::string name; 
    if (std::get<1>(strength) == 0)
        name = "Pocket " + card_names[std::get<0>(strength) - 2] + "s"; 
    else
    {
        name = card_names[std::get<0>(strength) - 2] + " " + card_names[(std::get<0>(strength) - std::get<1>(strength)) - 2];
        if (std::get<2>(strength))
            name += " suited";
        else
            name += " offsuit";
    }
    return name;
}

std::string Hand::getClassification()
{
    std::string name;
    if (std::get<0>(strength) <= 6)
        name = "Small";
    else if (std::get<0>(strength) <= 9)
        name = "Medium";
    else
        name = "High";
    
    if (std::get<1>(strength) == 0)
    {
        name += " pocket pair";
        return name;
    }

    if (std::get<2>(strength))
        name += " suited";

    if (std::get<1>(strength) == 1)
        name += " connector";
    else if (std::get<1>(strength) == 2)
        name += " two-gapper";
    else
        name += " card";
    return name;
}
    
void Hand::calculateStrength()
{
    int highcard = std::max(cards[0].getValue(), cards[1].getValue());
    int diff = std::abs(cards[0].getValue() - cards[1].getValue());
    int suited = (cards[0].suit == cards[1].suit);
    strength = strength_struct(highcard, diff, suited, 0, 0, 0);
}

void Hand::calculateStrength(Board& board)
{
    int count = 0;
    std::vector<Card> all_cards;
    all_cards.reserve(7);

    for (auto& card : cards)
        all_cards.push_back(card);
    
    for (auto& card : board.cards)
        if (!card.Null())
            all_cards.push_back(card);

    // Sorting from highest to lowest will make the test functions return
    // the highest cards that satisfy the condition first, making further
    // tests redundant
    std::sort(all_cards.begin(), all_cards.end(), 
            [](Card& a, Card& b) { return a.getValue() > b.getValue(); });
    
    std::vector<int> highs;
    std::pair<int, int> flush = Flush(all_cards);
    int straightflush = -1;
    if (flush.first != -1)
        straightflush = StraightFlush(all_cards, flush.first);
   
    if (straightflush != -1)
    {
        if (straightflush == 14) // Ace high straightflush
        {
            strength = std::make_tuple(Strength::ROYALFLUSH, 0, 0, 0, 0, 0); 
            return;
        }
        else
        {
            strength = std::make_tuple(Strength::STRAIGHTFLUSH, straightflush, 0, 0, 0, 0);
            return;
        }
    }

    // Sort cards after testing for lower end straights
    std::sort(all_cards.begin(), all_cards.end(), 
            [](Card& a, Card& b) { return a.getValue() > b.getValue(); });

    std::pair<int, int> same = NSame(all_cards);
    std::pair<int, int> second_pair;
    if (same.first == 4)
    {
        getHighestCards(highs, all_cards, 1, {same.second});
        strength = std::make_tuple(Strength::QUADS, same.second, highs[0], 0, 0, 0);
        return;
    }

    int straight = Straight(all_cards); 

    std::sort(all_cards.begin(), all_cards.end(), 
            [](Card& a, Card& b) { return a.getValue() > b.getValue(); });

    if (same.first == 3)
    {
        // Search for pair ignoring the value of trips
        second_pair = NSame(all_cards, same.second);
        if (second_pair.first >= 2)
        {
            strength = std::make_tuple(Strength::BOAT, same.second, second_pair.second, 0, 0, 0); 
            return;
        }
        if (straight == -1 && flush.first == -1)
        {
            getHighestCards(highs, all_cards, 2, {same.second});
            strength = std::make_tuple(Strength::TRIPS, same.second, highs[0], highs[1], 0, 0); 
            return;
        }
    }

    if (flush.first != -1)
    {
        strength = std::make_tuple(Strength::FLUSH, flush.second, 0, 0, 0, 0); 
        return;
    }
    if (straight != -1)
    {
        strength = std::make_tuple(Strength::STRAIGHT, straight, 0, 0, 0, 0); 
        return;
    }

    if (same.first == 2)
    {
        second_pair = NSame(all_cards, same.second);
        if (second_pair.first == 2)
        {
            getHighestCards(highs, all_cards, 1, {same.second, second_pair.second});
            strength = std::make_tuple(Strength::TWO_PAIR, same.second, second_pair.second, highs[0], 0, 0); return;
        }
        else
        {
            getHighestCards(highs, all_cards, 3, {same.second});
            strength = std::make_tuple(Strength::PAIR, same.second, highs[0], highs[1], highs[2], 0); return;
        }
    }
    else
    {
        getHighestCards(highs, all_cards, 5, {});
        strength = std::make_tuple(Strength::HIGH, highs[0], highs[1], highs[2], highs[3], highs[4]); return;
    }
    strength = std::make_tuple(-1, -1, -1, -1, -1, -1); return;
}


std::string Hand::getStrengthName()
{
    int stren = std::get<0>(strength);
    switch (stren)
    {
        case 0: // High
            {
                int value = std::get<1>(strength);
                return (Card(value, 0).getName() + " High");
                break;
            }
        case 1: // Pair
            {
                int value = std::get<1>(strength);
                return "One Pair: " + Card(value, 0).getName() + "s";
                break;
            }
        case 2: // Two Pair
            {
                int pair = std::get<1>(strength);
                int second = std::get<2>(strength);
                return "Two Pair: " + card_names[pair - 2] + "s and " + card_names[second - 2] + "s";
                break;
            }
        case 3: // Trips
            {
                int value = std::get<1>(strength);
                return "Three of a kind: " + Card(value, 0).getName() + "s";
                break;
            }
        case 4: // Straight
            {
                int value = std::get<1>(strength);
                return "Straight to the " + Card(value, 0).getName();
                break;
            }
        case 5: // Flush
            {
                int value = std::get<1>(strength);
                return Card(value, 0).getName() + " High Flush";
                break;
            }
        case 6: // Full House
            {
                int trips = std::get<1>(strength);
                int pair = std::get<2>(strength);
                return "Full House: " + Card(trips, 0).getName() + "s over " + Card(pair, 0).getName() + 's';
                break;
            }
        case 7: // Quads
            {
                int value = std::get<1>(strength);
                return "Four of a kind: " + Card(value, 0).getName() + "s";
                break;
            }
        case 8: // Straight Flush
            {
                int value = std::get<1>(strength);
                return "Straight Flush to the " + Card(value, 0).getName();
                break;
            }
        case 9: // Royal Flush
            {
                return "Royal Flush";
                break;
            }
    }
    return "Error: Unclassified";
}

