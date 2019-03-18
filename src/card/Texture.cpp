#include <card/Texture.hpp>
#include <app/Config.hpp>

namespace card {

    const ctk::Vec2<short> Texture::size = ctk::Vec2<short>(11, 9);

    Texture::Texture()  {}
    Texture::Texture(int id) : id(id)
    {
        Load();
    }

    void Texture::Load()
    {
        std::ifstream file(game::graphics, std::ios_base::in);
        file.seekg(id * 108);
        file.read(data.data(), 108);
    }

    void Texture::Render(ucurses::Canvas* canvas, Card::Suit suit, ctk::Vec2<short> pos)
    {
        short count = 0;
        
        for (int y = pos.y; y < Texture::size.y + pos.y; y++)
            for (int x = pos.x; x <= Texture::size.x + pos.x; x++)
            {
                char ch =  data[count++];

                // Borders
                if (ch != '\n') // Character
                {
                    canvas->cells.Get(x, y)->symbol = ch;
                    canvas->cells.Get(x, y)->color = 10;
                    if (y == pos.y || y == pos.y + (Texture::size.y - 1))
                        *(canvas->cells.Get(x, y)) = ucurses::Cell(ACS_HLINE, 10);
                    else if (x == pos.x || x == pos.x + Texture::size.x - 1)
                        *(canvas->cells.Get(x, y)) = ucurses::Cell(ACS_VLINE, 10); 
                }
                if (ch == '*')
                {
                    canvas->cells.Get(x, y)->symbol = suit_symbols[suit];

                    if (suit == Card::Suit::CLUB || suit == Card::Suit::SPADE)
                        canvas->cells.Get(x, y)->color = BLACK;
                    if (suit == Card::Suit::DIAMOND || suit == Card::Suit::HEART)
                        canvas->cells.Get(x, y)->color = RED;

                }
                if (id != 0)
                {
                    
                    if (!(x < pos.x + 2 || x > pos.x + Texture::size.x - 3 || y < pos.y + 1 || y > pos.y + Texture::size.y - 2))
                        if (y == pos.y + 1 || y == pos.y + (Texture::size.y - 2))
                            *(canvas->cells.Get(x, y)) = ucurses::Cell(ACS_HLINE, 10);
                        else if (x == pos.x + 2 || x == pos.x + Texture::size.x - 3)
                            *(canvas->cells.Get(x, y)) = ucurses::Cell(ACS_VLINE, 10); 
                    canvas->cells.Get(pos.x + 2, pos.y + 1)->symbol = ACS_ULCORNER;
                    canvas->cells.Get((Texture::size.x - 3) + pos.x, pos.y + 1)->symbol = ACS_URCORNER;
                    canvas->cells.Get(pos.x + 2, pos.y + (Texture::size.y - 2))->symbol = ACS_LLCORNER;
                    canvas->cells.Get(pos.x + (Texture::size.x - 3), pos.y + (Texture::size.y - 2))->symbol = ACS_LRCORNER;
                }
                else
                {
                    if (y == pos.y + 3 || y == pos.y + 5)
                    {
                        if (x == pos.x)
                            *(canvas->cells.Get(x, y)) = ucurses::Cell(ACS_LTEE, 10); 
                        else if (x == pos.x + 10)
                            *(canvas->cells.Get(x, y)) = ucurses::Cell(ACS_RTEE, 10); 
                        else if (ch != '\n')
                            *(canvas->cells.Get(x, y)) = ucurses::Cell(ACS_HLINE, 10); 
                    }
                    canvas->cells.Get(pos.x + 3, pos.y + 4)->color = RED;
                    canvas->cells.Get(pos.x + 4, pos.y + 4)->color = BLACK;
                    canvas->cells.Get(pos.x + 6, pos.y + 4)->color = RED;
                    canvas->cells.Get(pos.x + 7, pos.y + 4)->color = BLACK;
                }


            }
        canvas->cells.Get(pos.x, pos.y)->symbol = ACS_ULCORNER;
        canvas->cells.Get((Texture::size.x - 1) + pos.x, pos.y)->symbol = ACS_URCORNER;
        canvas->cells.Get(pos.x, pos.y + (Texture::size.y - 1))->symbol = ACS_LLCORNER;
        canvas->cells.Get(pos.x + (Texture::size.x - 1), pos.y + (Texture::size.y - 1))->symbol = ACS_LRCORNER;
    }

    const std::array<char, 108>& Texture::getData() const
    {
        return data;
    }

}
