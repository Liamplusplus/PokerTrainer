#include <card/Canvas.hpp>

int main()
{
    card::Canvas canvas(Card(11, Card::Suit::HEART));
    std::cout << card::Canvas::size << std::endl;
    for (auto& ch : canvas.getData())
        std::cout << ch;
    std::cout << std::endl;
    return 0;
}
