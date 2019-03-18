#include <house/GameUI.hpp>
#include <house/Game.hpp>
#include <app/Application.hpp>
#include <app/MainMenu.hpp>

#include <ctk/io/conversion.hpp>

#include <card/Texture.hpp>

using namespace ucurses;
using namespace std::chrono;

namespace house
{
    GameUI::GameUI(cardgame::Application* handle, house::Game* game_handle) : ::GameUI(handle), game(game_handle), bhelp(true)
    {
        deal_initial = -1;    
        deal_board = -1;    
    }

    void GameUI::Initialize()
    {
        target->setDefaultColor(9);

        player_info = new Label(target);
        player_info->setPosition(0.08f, 0.08f);
        player_info->setText(game->getPlayer().getName());
        player_info->appendLine("$" + ctk::to_string(game->getPlayer().getBalance()));
        
        help = new Label(target);
        help->setPosition(0.6f, 0.1);
        
        bet_display = new Label(target);
        bet_display->setPosition(0.5f, 0.85f);
        
        dealer_box = new Label(target);
        dealer_box->setPosition(0.5f, 0.05f);
        dealer_box->getPosition().x -= 6;

        // Player card display
        player_display = new Canvas(target, display_size);
        player_display->Fill('.');
        player_display->setPosition(bet_display->getPosition());
        player_display->getPosition().y -= 13;
        player_display->alignMiddle();

        // Align label after as player_display is positioned relative to label
        bet_display->setText("Ante: $" + ctk::to_string(game->ante) + " - Blind: $" + ctk::to_string(game->ante));
        bet_display->alignMiddle();
        bet_display->appendLine("\n\t  Play: $" + ctk::to_string(game->play));
        
        // Dealer card display
        dealer_display = new Canvas(target, display_size);
        dealer_display->Fill('.');
        dealer_display->setPosition(0.5f, 0.1f);
        dealer_display->alignMiddle();

        // Board display
        board = new Canvas(target, board_size);
        board->Fill('.');
        board->setPosition(0.5f, 0.37f);
        board->alignMiddle();

        InitializeDisplay(player_display);
        InitializeDisplay(dealer_display);
        InitializeDisplay(board);

        target->callback_stack.Push(KEY_F(2), [=](){ target->Bind(new cardgame::MainMenu(app)); });
        InitializeCommands();
        
    }
    
    void GameUI::Reset()
    {
        game->Reset();
        updateTotals();
        RenderCards();
        InitializeCommands();
        help->Clear();
    }        

    void GameUI::InitializeCommands()
    {
        target->Commands.Clear();
        target->ClearTips();
        target->Commands.Add('k', [=](){ changeBet(game->min_bet); });
        target->Commands.Add('j', [=](){ changeBet(-game->min_bet); });
        target->Commands.Add(10, [=](){ placeBet(); });
        target->Commands.Add('h', [=](){ bhelp = !bhelp; help->setVisibility(bhelp); });
        target->addTip("k: Increase Bet");
        target->addTip("j: Decrease Bet");
        target->addTip("  Enter: Place Bet");
    }

    void GameUI::changeBet(float amount)
    {
        if (game->changeBet(amount) == 0)
        {
            bet_display->setText("Ante: $" + ctk::to_string(game->ante) + " - Blind: $" + ctk::to_string(game->ante));
            bet_display->appendLine("\n\t  Play: $" + ctk::to_string(game->play));
        }
        else
        {
            help->loadFromFile(".resources/help/bet");
        }
            
    }

    void GameUI::placeBet()
    {
        game->PlaceBet();
        game->chip_sound.play();
        player_info->setText(game->getPlayer().getName());
        player_info->appendLine("$" + ctk::to_string(game->getPlayer().getBalance()));
        InitialDeal();
    }
            
    void GameUI::Update()
    {
        if (deal_board != -1)
        {
            steady_clock::time_point now = steady_clock::now();
            milliseconds dur = duration_cast<milliseconds>(now - timepoint);
            if (milliseconds(dur) > milliseconds(400))
            {
                Render(game->board.cards[deal_board], board, ctk::Vec2<short>(2 + (12 * deal_board), 1));
                game->card_flip.play();
                
                if (++deal_board < game->board.nCards())
                    timepoint = steady_clock::now();
                else
                    deal_board = -1;
            }
        }
    }

    void GameUI::InitialDeal()
    {
        game->InitialDeal();
        
        app->SchedualTask(200, [=]() 
        { 
            game->card_flip.play(); 
            Render(game->player_hand.cards[0], player_display, ctk::Vec2<short>(2, 1));
        });
        app->SchedualTask(400, [=]() 
        { Render(game->dealer_hand.cards[0], dealer_display, ctk::Vec2<short>(2, 1)); });
        
        app->SchedualTask(800, [=]() 
        { Render(game->player_hand.cards[1], player_display, ctk::Vec2<short>(14, 1)); });
                        
        app->SchedualTask(800, [=]() 
        { Render(game->dealer_hand.cards[1], dealer_display, ctk::Vec2<short>(14, 1)); });

        target->Commands.Clear();
        target->ClearTips();
        target->Commands.Add('h', [=](){ bhelp = !bhelp; help->setVisibility(bhelp); });
        target->addTip("Space: Check");
        target->addTip("j: 3x Raise");
        target->addTip("k: 4x Raise");
        help->setText("Preflop you have the option to raise 3x or 2x your blind bet or check");

        // If player checks, deal flop and receive input, else deal entire board.
        target->Commands.Add(' ', [=]()
        { 
            deal_board = game->board.nextStreet(); 
            NextStreet(); 
        });

        target->Commands.Add('j', [=]()
        { 
            if (game->Play(3.f) != -1)
            {
                updateTotals();
                deal_board = game->board.nextStreet(); 
                NextStreet(); 
            }
            else
                help->setText("In sufficient funds for raise");
        });
        target->Commands.Add('k', [=]()
        { 
            if (game->Play(4.f) != -1)
            {
                updateTotals();
                deal_board = game->board.nextStreet(); 
                NextStreet(); 
            }
            else
                help->setText("In sufficient funds for raise");
        });
    }
            
    void GameUI::updateTotals()
    {
        bet_display->setText("Ante: $" + ctk::to_string(game->ante) + " - Blind: $" + ctk::to_string(game->ante));
        bet_display->appendLine("\n\t  Play: $" + ctk::to_string(game->play));
        
        player_info->setText(game->getPlayer().getName());
        player_info->appendLine("$" + ctk::to_string(game->getPlayer().getBalance()));
    }

    void GameUI::NextStreet()
    {
        game->NextStreet();
        int current_street = game->board.currentStreet();
        switch (current_street)
        {
            case Street::FLOP:
                target->Commands.Clear();
                target->ClearTips();
                target->addTip("Space: Check");
                target->addTip("j: 2x Raise");
                help->loadFromFile(".resources/help/flop");
                target->Commands.Add(' ', [=]()
                { 
                    deal_board = game->board.nextStreet(); 
                    NextStreet(); 
                });
                break;
            case Street::RIVER:
                target->Commands.Clear();
                target->ClearTips();
                if (game->play == 0.f)
                {
                    target->addTip("Space: Play!");
                    target->addTip("f: Fold");
                    help->loadFromFile(".resources/help/riv");
                    target->Commands.Add(' ', [=]() { game->Play(1.f); FinishHand(); });
                    target->Commands.Add('f', [=]() { Fold(); });
                }
                else
                {
                    help->Clear();
                    FinishHand(2900);
                }
                break;
        }
    }

    void GameUI::Fold()
    {
        app->SchedualTask(400, [=]() mutable
        {
            Render(game->dealer_hand.cards[0], dealer_display, ctk::Vec2<short>(2, 1));
        });
        app->SchedualTask(800, [=]() mutable
        {
            Render(game->dealer_hand.cards[1], dealer_display, ctk::Vec2<short>(14, 1));
        });
        app->SchedualTask(1200, [=]() mutable
        {
            Reset();
        });
    }

    void GameUI::FinishHand(int delay)
    {
        updateTotals();
        target->Commands.Clear();
        target->ClearTips();
        game->dealer_hand.setVisible(true);
        app->SchedualTask(delay, [=]() mutable
        {
            Render(game->dealer_hand.cards[0], dealer_display, ctk::Vec2<short>(2, 1));
        });
        app->SchedualTask(delay + 400, [=]() mutable
        {
            Render(game->dealer_hand.cards[1], dealer_display, ctk::Vec2<short>(14, 1));
        });
        app->SchedualTask(delay + 1800, [=]() 
        {
            calculatePayout();
        });
        app->SchedualTask(delay + 3400, [=]() mutable
        {
            Reset();
        });
    }

    void GameUI::calculatePayout()
    {
        float winnings = game->calculatePayout();
        help->setText("Players " + game->player_hand.getStrengthName());
        help->appendLine("Dealers " + game->dealer_hand.getStrengthName());
        if (winnings > 0.f)
            help->appendLine("\nPlayer wins!  $" + ctk::to_string(winnings));
        else if (winnings < 0.f)
            help->appendLine("\nPlayer loses  $" + ctk::to_string(winnings));
        else
            help->appendLine("\nTie");
    }

    void GameUI::RenderTest()
    {
        Render(Card(1, Card::Suit::HEART), board, ctk::Vec2<short>(2, 1));
        Render(Card(8, Card::Suit::DIAMOND), board, ctk::Vec2<short>(14, 1));
        Render(Card(8, Card::Suit::SPADE), board, ctk::Vec2<short>(26, 1));
        Render(Card(13, Card::Suit::SPADE), board, ctk::Vec2<short>(38, 1));
        Render(Card(1, Card::Suit::SPADE), board, ctk::Vec2<short>(50, 1));
        
        Render(Card(0, Card::Suit::CLUB), dealer_display, ctk::Vec2<short>(2, 1));
        Render(Card(0, Card::Suit::HEART), dealer_display, ctk::Vec2<short>(14, 1));
        
        Render(Card(1, Card::Suit::SPADE), player_display, ctk::Vec2<short>(2, 1));
        Render(Card(11, Card::Suit::SPADE), player_display, ctk::Vec2<short>(14, 1));
 
    }

    void GameUI::RenderCards()
    {
        Render(game->player_hand.cards[0], player_display, ctk::Vec2<short>(2, 1));
        Render(game->player_hand.cards[1], player_display, ctk::Vec2<short>(14, 1));
        
        Render(game->dealer_hand.cards[0], dealer_display, ctk::Vec2<short>(2, 1));
        Render(game->dealer_hand.cards[1], dealer_display, ctk::Vec2<short>(14, 1));
        
        Render(game->board.cards[0], board, ctk::Vec2<short>(2, 1));
        Render(game->board.cards[1], board, ctk::Vec2<short>(14, 1));
        Render(game->board.cards[2], board, ctk::Vec2<short>(26, 1));
        Render(game->board.cards[3], board, ctk::Vec2<short>(38, 1));
        Render(game->board.cards[4], board, ctk::Vec2<short>(50, 1));
    }
    
}
