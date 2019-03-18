#include <player/StatusScreen.hpp>
#include <ctk/io/conversion.hpp>

namespace blackjack {


	StatusScreen::StatusScreen(Player* subject) : player(subject)
	{
	
	}

	void StatusScreen::Initialize()
	{

		action_screen = new Menu(target);
		action_screen->setPosition(0.1f, 0.5f);
		action_screen->addItem("Deposit");
		action_screen->addItem("Withdraw");
		// Deletes the game save allowing another
		action_screen->addItem("Give up");

		display = new Label(target);
		display->setPosition(0.1f, 0.1f);

		display->setText(player->getName());
		display->appendLine("$" + ctk::to_string(player->getBalance()));
	
	}
}
