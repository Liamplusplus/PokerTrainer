#include <holdem/GameUI.hpp>

using namespace ucurses;

namespace holdem {

    
    GameUI::GameUI(cardgame::Application* handle, holdem::Game* game_handle) : ::GameUI(handle), game(game_handle)
    {
        dealing = -1;
    }

    void GameUI::Initialize()
    {
        target->setDefaultColor(9);
        for (auto& display : displays)
        {
            display = new Canvas(target, display_size);
            display->Fill('.');
            InitializeDisplay(display);
        }
        displays[0]->setPosition(0.65f, 0.05f);
        displays[1]->setPosition(0.97f, 0.25f);
        displays[2]->setPosition(0.97f, 0.58f);
        displays[1]->getPosition().x -= 27;
        displays[2]->getPosition().x -= 27;

        displays[4]->setPosition(0.5f, 0.77f);
        displays[4]->alignMiddle();

        displays[3]->setPosition(0.0f, 0.73f);
        displays[5]->setPosition(0.0f, 0.73f);
        displays[5]->getPosition().x = displays[4]->getPosition().x - (27 + 16);
        displays[3]->getPosition().x = displays[4]->getPosition().x + (27 + 16);

        displays[6]->setPosition(0.03f, 0.58f);
        displays[7]->setPosition(0.03f, 0.25f);
        displays[8]->setPosition(0.2f, 0.05f);

        button = new Label(target);
        button->setText("B");

        for (int i = 0; i < 9; i++)
        {
            display_info[i] = new Label(target); 
            display_info[i]->setPosition(displays[i]->getPosition());
            display_info[i]->getPosition() += ctk::Vec2<short>(14, 13);
            if (i == game->getPlayerSeat())
            {
                display_info[i]->setText("Hero");
            }
            display_info[i]->alignMiddle();
        }
        
        board = new Canvas(target, board_size);
        board->Fill('.');
        board->setPosition(0.5f, 0.37f);
        board->alignMiddle();
        InitializeDisplay(board);

        target->Commands.Add(KEY_F(5), [=]() { Quit(); });
        target->Commands.Add('d', [=]() { InitialDeal(); });
        target->Commands.Add('n', [=]() { NextStreet(); });
        
    }

    void GameUI::InitialDeal()
    {
        game->InitialDeal();
        RenderButton();
        RenderCards();
    }

    void GameUI::RenderButton()
    {
        short button_pos = game->getButtonPos();
        button->setPosition(displays[button_pos]->getPosition());
        if (button_pos == 3 || button_pos == 4 || button_pos == 5)
        {
            button->getPosition().x += 12;
            button->getPosition().y -= 2;
        }
        if (button_pos == 6 || button_pos == 7)
        {
            button->getPosition().x += 26;
            button->getPosition().y += 5;
        }
        if (button_pos == 1 || button_pos == 2)
        {
            button->getPosition().x -= 2;
            button->getPosition().y += 5;
        }
        if (button_pos == 0 || button_pos == 8)
        {
            button->getPosition().x += 12;
            button->getPosition().y += 12;
        }
    
    }
    
    void GameUI::NextStreet()
    {
        game->NextStreet();
        RenderCards();
    }
        
    void GameUI::RenderCards()
    {
        for (int i = 0; i < 9; i++)
        {
            Render(game->getHand(i)->cards[0], displays[i], ctk::Vec2<short>(2, 1));       
            Render(game->getHand(i)->cards[1], displays[i], ctk::Vec2<short>(14, 1));
        }
        
        Render(game->board.cards[0], board, ctk::Vec2<short>(2, 1));
        Render(game->board.cards[1], board, ctk::Vec2<short>(14, 1));
        Render(game->board.cards[2], board, ctk::Vec2<short>(26, 1));
        Render(game->board.cards[3], board, ctk::Vec2<short>(38, 1));
        Render(game->board.cards[4], board, ctk::Vec2<short>(50, 1));
    }
}
