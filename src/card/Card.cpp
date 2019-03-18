#include <card/Card.hpp>

    
Card::Card(int value, int suit) : value(value), suit(static_cast<Suit>(suit)), showing(false) 
{

}

void Card::write_form(std::ostream& stream) const
{
    stream << "<Value> " << value << '\n' << "<Suit> " << suit_names[static_cast<int>(suit)] << std::endl;
}
    
void Card::setVisible(bool b)
{
    showing = b; 
}

void Card::read_form(std::istream& stream)
{
    stream.ignore(256, ' ');
    stream >> value;
    stream.ignore(256, ' ');
    
    int cast;
    stream >> cast;
    suit = static_cast<Suit>(cast);
}

void Card::write_dump(std::ostream& stream) const
{
    stream << value << " " << static_cast<int>(suit);
}
void Card::read_dump(std::istream& stream)
{
    int cast;
    stream >> value >> cast;
    suit = static_cast<Suit>(cast);
}

int Card::getValue()
{
    if (value == 1)
        return 14;
    else
        return value;
}

std::string Card::getName()
{
    return card_names[getValue() - 2];
}

int Card::getStraightValue()
{
    if (value == 1)
        return 1;
    else
        return value;
}
