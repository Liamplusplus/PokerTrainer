#include <player/PlayerCreate.hpp>
#include <app/Application.hpp>
#include <app/Game.hpp>

namespace cardgame {

	void CreatePlayer(Window* target, Application* handle)
	{
		target->Clear();
        target->ucurses->Render();
        TextEntry* name_enter = new TextEntry(target);
        name_enter->setPosition(0.5f, 0.5f);
        name_enter->setSubject("Name");
        while (name_enter->getText() == "")
            name_enter->getInput();

        handle->game_data->createNewPlayer(name_enter->getText());
	
	}

}
