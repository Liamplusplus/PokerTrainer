/*
 * Contains player information and action menu
 *
 */

#pragma once

#include <player/Player.hpp>

#include <ucurses/ucurses.hpp>
using namespace ucurses;

namespace blackjack {

	class StatusScreen : public Interface
	{

		public:

			StatusScreen(Player* player);

		protected:

			virtual void Initialize();

			Menu* action_screen;
			Label* display;

			Player* player;

	};
}
