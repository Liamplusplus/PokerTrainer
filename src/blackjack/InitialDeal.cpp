#include <blackjack/InitialDeal.hpp>
#include <blackjack/GameUI.hpp>
#include <app/MainMenu.hpp>

#include <ucurses/ucurses.hpp>

using namespace ucurses;

namespace blackjack {
           
    void InitialDeal::Setup(GameUI* game_ui)
    {

        for (size_t i = 0; i < game_ui->boxes.size(); ++i)
            game_ui->boxes[i]->addCommand(i + 49, std::bind(&GameUI::placeBet, game_ui, i + 1));
        
        game_ui->counts.back()->setText("Dealer");
        game_ui->RefreshBoxes();
        game_ui->displayPlayerInfo();
		
        game_ui->target->Commands.Add(10, std::bind(&GameUI::InitialDeal, game_ui));
		//game_ui->target->addCommand('l', std::bind(&Game::logState, game_ui->game));
		game_ui->target->callback_stack.Push('l', std::bind(&InitialDeal::Callback, game_ui->game, game_ui->target));
        game_ui->target->addTip("1-6: Bet on box");
        game_ui->target->addTip("Enter: Deal");
        game_ui->target->addTip("l: Leave table");
        
    }
            
    void InitialDeal::Advance(GameUI* game_ui)
    {
    
    }

    void InitialDeal::Callback(Game* game_data, Window* target)
    {
        game_data->Save();
        target->Bind(new MainMenu(game_data));
    }



}

