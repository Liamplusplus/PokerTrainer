#include <app/GameUI.hpp>
#include <app/Config.hpp>
#include <card/Texture.hpp>
#include <app/MainMenu.hpp>

const ctk::Vec2<short> GameUI::display_size = ctk::Vec2<short>(27, 11);
const ctk::Vec2<short> GameUI::board_size = ctk::Vec2<short>(63, 11);

using namespace ucurses;

GameUI::GameUI(cardgame::Application* handle) : app(handle)
{
    std::ifstream file(game::graphics, std::ios_base::in);
    for (int i = 0; i < 14; i++)
    {
        textures[i] = card::Texture(i);
    }

    // Definition of suit colors
    //

    // Table yellow on green
    init_pair(9, 1 * 2.55f, 9 * 2.55f);
    init_pair(8, 89 * 2.55f, 9 * 2.55f);

    // Card default: black on white
    init_pair(10, COLOR_BLACK, 1 * 2.55f);
    init_pair(card::RED, COLOR_RED, 1 * 2.55f);

    // For multi colored suits
    //init_pair(Card::Suit::CLUB, 9 * 2.55f, 1 * 2.55f);
    //init_pair(Card::Suit::SPADE, 57 * 2.55f, 1 * 2.55f);
    //init_pair(Card::Suit::DIAMOND, 69 * 2.55f, 1 * 2.55f);
}

void GameUI::Quit()
{
    target->Bind(new cardgame::MainMenu(app));
}

void GameUI::Test()
{
    std::ofstream file("testfile"); 
    for (auto& texture : textures)
        for (auto& ch : texture.getData())
            std::cout << ch;
}

card::Texture* GameUI::getCardTexture(int id)
{
    return &textures[id];
}

void GameUI::Render(const Card& card, ucurses::Canvas* canvas, ctk::Vec2<short> pos)
{
    if (card.value == -1)
    {
        for (int y = pos.y; y < card::Texture::size.y + pos.y; y++)
            for (int x = pos.x; x < card::Texture::size.x + pos.x; x++)
                *(canvas->cells.Get(x, y)) = ucurses::Cell(' ', 9);
        return;
    }
    card::Texture* texture;

    if (!card.showing)
        texture = &textures[0];
    else
        texture = &textures[card.value];

    texture->Render(canvas, card.suit, pos);
}
   
    
void GameUI::InitializeDisplay(Canvas* display)
{
    ctk::Vec2<short> display_size = display->getSize();

    for (int x = 0; x < display_size.x; x++)
    {
        for (int y = 0; y < display_size.y; y++)
        {
            if (y == 0 || y == display_size.y - 1)
                *(display->cells.Get(x, y)) = Cell(ACS_HLINE, 9);
            else if (x == 0 || x == display_size.x - 1)
                *(display->cells.Get(x, y)) = Cell(ACS_VLINE, 9);
            else
                *(display->cells.Get(x, y)) = Cell(' ', 9);
        }
    }
    *(display->cells.Get(0, 0)) = Cell(ACS_ULCORNER, 9);
    *(display->cells.Get(display_size.x - 1, 0)) = Cell(ACS_URCORNER, 9);
    *(display->cells.Get(0, display_size.y - 1)) = Cell(ACS_LLCORNER, 9);
    *(display->cells.Get(display_size.x - 1, display_size.y - 1)) = Cell(ACS_LRCORNER, 9); 
}
