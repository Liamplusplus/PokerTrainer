#include <blackjack/GameUI.hpp>
#include <card/CardCanvas.hpp>
#include <app/MainMenu.hpp>
#include <app/Config.hpp>
#include <blackjack/Game.hpp>

#include <ctk/io/conversion.hpp>

#include <sstream>

namespace blackjack {

    GameUI::GameUI(::Game* game) : game(game)
    {

    }

    void GameUI::Initialize()
    {
		if (game->getPlayer().getBalance() < 5.f)
		{
			target->Clear();
			Label* game_over = new Label(target);
			game_over->setPosition(0.5f, 0.5f);
			game_over->setText("You are broke, go be depressed somewhere else");
			game_over->move(-10, 0);
			target->addTip("Enter: Accept Defeat");
			target->Commands.Add(10, std::bind(&GameUI::acceptDefeat, this));
		}
		else
		{

			player_info = new Label(target);
			player_info->setPosition(0.05f, 0.1f);

			bet = new TextEntry(target);
			bet->setPosition(0.5f, 0.95f);
			bet->setSubject("Place Bet");

			for (size_t i = 0; i < boxes.size(); ++i)
			{
				boxes[i] = new Label(target);
				boxes[i]->setPosition(0.1666f * (i + 0.3), 0.8f);
				boxes[i]->setText("  Box " + std::to_string(i + 1));
			}

			for (size_t i = 0; i < boxes.size(); ++i)
			{
				counts[i] = new Label(target);
				counts[i]->setPosition(0.1666f * (i + 0.3), 0.76f);
			}

			counts.back() = new Label(target);
			counts.back()->setPosition(0.5f, 0.2f);
			counts.back()->move(15, 3);

			InitialDeal::Setup(this);
		}

	}

	/********** Game States ********/

	// Currently deals cards to every box with money and then draws a cardcanvas
	void GameUI::InitialDeal()
	{
		int boxno = game->InitialDeal();	

		if (boxno > -1) // Active Box found
		{
			Box& box = game->box_manager.Get(boxno);
			float x = 0.1666f * (boxno + 0.3);
			float y = 0.55;
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(x, y);
			canvas->move(0, -(box.nCards()  * 2) + 2);
			canvas->Load(box.Top());
			game->box_manager.Next();
			displayPlayerInfo();
			RefreshActiveBox();
		}
		else if (boxno == -2) // Dealer turn
		{
			Box& box = game->box_manager.Get(DEALER_BOX);
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(0.5f, 0.2f);
			canvas->Load(box.Top());
		}
		else if (boxno == -3)
		{
			GamePhase();
		}
	}

	/*
	 * Find next active box
	 * Prompt hit or sit
	 * 		If bust or sit, increment box
	 * 		If hit and safe, prompt again
	 *
	 * 	After all boxes, deal dealers hand
	 */
	void GameUI::GamePhase()
	{
		for (int i = 0; i < counts.size(); ++i)
			refreshBoxCount(i);

		if (game->GamePhase() != -1)
		{
			target->Commands.Clear();
			target->addTip("h: Hit");
			target->addTip("s: Sit");

			// DEBUG
			//
			target->Commands.Add('l', std::bind(&Game::logState, game));

			target->Commands.Add('h', std::bind(&GameUI::Hit, this));
			target->Commands.Add('s', std::bind(&GameUI::Sit, this));
		}
		else
		{
			target->Bind(new GameUI(this->game));
		}
	}

	void GameUI::setup()
	{
		target->Commands.Clear();

		target->addTip("Enter: Final Deal");
		target->Commands.Add('l', std::bind(&Game::logState, game));
		target->Commands.Add(10, std::bind(&GameUI::FinalDeal, this));
	}

	void GameUI::FinalDeal()
	{
		Card card = game->FinalDeal();
		refreshBoxCount(DEALER_BOX);

		if (!card.Null())
		{
			Box& box = game->box_manager.Get(DEALER_BOX);
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(0.5f, 0.2f);
			canvas->move(0, -(box.nCards()  * 2) + 2);
			canvas->Load(box.Top());
		}
		else
		{
			target->Clear();
			Initialize();
		}
	}

	void GameUI::acceptDefeat()
	{
		game->Delete();	
		game->Reset();
		target->Bind(new MainMenu(game));
	}

	void GameUI::displayPlayerInfo()
	{
		player_info->setText(game->getPlayer().getName() + ": $" + ctk::to_string(game->getPlayer().getBalance())); 
	}


	// 
	void GameUI::Hit()
	{
		int active = game->Hit();
		if (active != -1)
		{
			float y = 0.55;
			float x = 0.1666f * (active + 0.3);
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(x, y);
			canvas->move(0, -(game->box_manager.Get(active).nCards()  * 2) + 2);
			canvas->Load(game->box_manager.Get(active).Top());
			refreshBoxCount(active);
			if (game->box_manager.getActiveIndex() == boxes.size())
				setup();
		}
		RefreshActiveBox();
	}

	void GameUI::Sit()
	{
		if (game->Sit() == -1)
			setup();
		RefreshActiveBox();
	}
	// Initial Deal:
	// Deal one card to every box with money in it. Then one card to dealer
	//
	// Game Round
	// Ask each non-empty box to hit or sit, and add a card accordingly
	// Then deal the dealers box, hitting whilst under 17

	void GameUI::placeBet(int boxn)
	{
		game::debug << "placeBet() " << boxn << std::endl;
		bet->getInput();
		std::stringstream bet_amount;
		bet_amount.str(bet->getText());
		if (!bet_amount.str().empty())
		{
			double temp = 0.0f;
			if (bet_amount >> temp)
			{
				if (temp > 0.0f)
				{
					if (game->addBet(temp, boxn) == -1)
						bet->setText("Not enough funds");
				}
				else bet->setText("Bet must be greater than zero");
			}
			else
				bet->setText("Invalid bet");
		}
		std::stringstream stream("$");
		stream << game->getPlayer().getName();
		stream << ": $" << std::fixed << std::setprecision(2) <<  game->getPlayer().getBalance();
		player_info->setText(stream.str());
		RefreshBoxes();
	}

	void GameUI::RefreshBoxes()
	{
		for (int i = 0; i < boxes.size(); ++i)
		{
			boxes[i]->setText("  Box " + std::to_string(i + 1) + "  "); // 0, 1, 8, 9
			boxes[i]->appendLine("");
			float bet =game-> box_manager.Get(i).bet;
			if (bet > 0.0f)
				boxes[i]->appendLine(game->getPlayer().getName() + ": $" + ctk::to_string(bet));
		}
		RefreshActiveBox();
	}

	// Pass in index to allow updating one box at a time
	void GameUI::refreshBoxCount(int index)
	{
		Box& box = game->box_manager.Get(index);

		std::pair<short, short> count = box.getCount();
		Box::Status status = box.getStatus();

		if (box.Busted())
			counts[index]->setText("--- Bust ---");
		else if (box.Full())
			counts[index]->setText("- Five Cards -");
		else if (status == Box::Status::UNDER || status == Box::Status::TWENTY_ONE)
		{
			counts[index]->setText(std::to_string(count.first));
			if (count.second != -1)
				counts[index]->appendText(", " + std::to_string(count.second));
		}
		else if (status == Box::Status::BLACKJACK)
			counts[index]->setText("+++ Blackjack +++");
	}

	void GameUI::RefreshGraphics()
	{

	}

	void GameUI::RefreshActiveBox()
	{
		int active = game->box_manager.getActiveIndex();
		game::debug << "RefreshActiveBox() " << active << std::endl;
		for (auto& it : boxes)
		{
			it->getText().back() = ' ';
			it->getText().front() = ' ';
		}

		if (active < boxes.size())
		{
			boxes[active]->getText().front() = '*';
			boxes[active]->getText().back() = '*';
		}
	}

	void GameUI::Payout()
	{
		displayPlayerInfo();
	}
}
