#include <blackjack/BoxManager.hpp>


BoxManager::BoxManager() : current_box(0)
{
    for (auto& box : boxes)
        box = Box();
    dealer.setActive(true);
}
		

void BoxManager::setActive(int index)
{
	current_box = index;
}
		
int BoxManager::addBet(float value, int pos)
{
	if (boxes[pos].addBet(value))
        return 0;
    else
        return -1;
}

int BoxManager::addCard(Card card)
{
    int active = current_box;
    if (active < boxes.size())
    {
        Box& box = getActive();
        box.addCard(card);

		if ( box.getStatus() == Box::Status::BLACKJACK 	||
			 box.getStatus() == Box::Status::TWENTY_ONE ||
			 box.Busted() || box.Full())
		{
			++current_box;	
			nextActive();
		}

		return active;
	}
	else
		return -1; 
}

BoxManager::Result BoxManager::Compare()
{
	Box& box = getActive();
	Box& dealer = Get(DEALER_BOX);

	std::pair<short, short> box_count = box.getCount();
	std::pair<short, short> dealer_count = dealer.getCount();
}

size_t BoxManager::size() const
{
	return boxes.size();
}

// Increments box
int BoxManager::Next()
{
	if (current_box <= boxes.size() - 1)
		return ++current_box;
	else
	{
		current_box = 0;
		return -1;
	}
}

int BoxManager::nextActive()
{
	for (;current_box < boxes.size(); ++current_box)
		if (boxes[current_box].Active())
			return current_box;
	return -1;
}

Box& BoxManager::getActive()
{
	return boxes[current_box];
}

int BoxManager::getActiveIndex()
{
	return current_box;
}

Box& BoxManager::Get(int index)
{
	if (index == DEALER_BOX)
		return dealer;
	else
		return boxes[index];
}

void BoxManager::write_form(std::ostream& stream)
{
	stream << "\n<CurrentBox> " << current_box;
	stream << "\n\n<Boxes>\n\n"; 

	for (auto& box : boxes)
	{
		box.write_form(stream);
		stream << '\n';
	}
	stream << "<Dealer>\n";
	dealer.write_form(stream);
	stream << '\n'; 
}

void BoxManager::Reset()
{
	current_box = 0;
	for (auto& box : boxes)
		box = Box();

	dealer = Box();
	dealer.setActive(true);

}

bool BoxManager::anyActive()
{
	for (auto& box : boxes)
		if (box.Active())
			return true;
	return false;

}
