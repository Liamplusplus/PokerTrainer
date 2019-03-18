#include <class/Card.hpp>
#include <iostream>

int main()
{
   
    Card test(5, Card::Suit::HEART);
    test.write_form(std::cout);

}
