#include <blackjack/Box.hpp>
#include <fstream>
#include <algorithm>

Box::Box() : status(Box::Status::UNDER), active(false), busted(false), full(false)
{
	bet = 0.0f;

	for (auto& card : cards)
		card = Card();
}

// Two possible values
// Every ace is a one || One ace is an 11
// getCount().first being the safest and
// getCount().second being the highest
std::pair<short, short> Box::getCount()
{
	std::pair<short, short> count = {0, 0};
	bool counted_eleven = false;
	for (auto& card : cards)
	{
		if (card.value >= 10)
		{
			count.first += 10;
			count.second += 10;
		}
		else if (card.value == 1) // Ace
		{
			count.first += 1;
			if (!counted_eleven)
			{
				count.second += 11;
				counted_eleven = true;
			}
			else
				count.second += 1;
		}
		else
		{
			count.first += card.value;
			count.second += card.value;
		}
	}

	if (count.second > 21 || count.first == count.second)
		count.second = -1;

	return count;

}

short Box::Highest()
{
	std::pair<short, short> count = getCount();
	if (count.second == -1)
		return count.first;
	else
		return count.second;
}

// No cards
bool Box::Empty() 				
{ 
	return cards[0].Null(); 
}

// No bets
bool Box::inActive()
{
	return bet == 0.f; 
}

// Busted
bool Box::Busted()
{
	return busted;
}

bool Box::Full()
{
	return full;
}

Card Box::Bottom()
{ 
	for (auto& card : cards)
		if (!card.Null())
			return card; 
	return Card();
}

Card Box::Top()
{
	for (std::array<Card, 5>::reverse_iterator rit = cards.rbegin(); rit != cards.rend(); ++rit)
		if (!rit->Null())
			return *rit;
	return Card();
}

int Box::nCards()
{
	return std::count_if(cards.begin(), cards.end(), [](Card& c) { return !c.Null(); });
}

bool Box::addBet(float value)
{
	active = true;

	if (bet == 0.0f)
	{
		bet = value;
		return true;
	}

	return false;
}

void Box::addCard(Card& card)
{
	for (auto& it : cards)
		if (it.Null())
		{
			it = card;
			break;
		}
	setStatus();
}

void Box::setStatus()
{
	std::pair<short, short> count = getCount();

	if (count.first > 21)
	{
		busted = true;
		active = false;
	}
	else if (count.second == 21 || count.first == 21)
	{
		if (nCards() == 2)
		{
			status = Status::BLACKJACK;
			active = false;
		}
		else
			status = Status::TWENTY_ONE;
	}
	else
		status = Status::UNDER;	

	if (nCards() == 5)
	{
		full = true;
		active = false;
	}
}

bool Box::Active()
{
	return active;
}

void Box::setActive(bool b)
{
	active = b;
}

Box::Status Box::getStatus()
{
	return status;
}

void Box::write_form(std::ostream& stream)
{
	bool active = !inActive();
	stream << "<Active> " << std::boolalpha << active;
	stream << "<Busted> " << std::boolalpha << Busted();
	if (active)
	{
		stream << "\n<Bet> " << bet << '\n' ;
		stream << "\n<Cards> " << nCards() << std::endl;
		for (auto& card : cards)
		{
			card.write_form(stream);
			stream << '\n';
		}
		std::pair<short, short> count = getCount();
		stream << "<Count> " << count.first << ", " << count.second << std::endl;
	}
}
