#include <ucurses/gui/Config.hpp>

#include <player/PlayerCreate.hpp>

#include <app/Application.hpp>
#include <app/MainMenu.hpp>

namespace cardgame 
{
    MainMenu::MainMenu(Application* handle) : app(handle)
    {

    }

    void MainMenu::Initialize()
    {
        target->setDefaultColor(1);
        mode_select = new Menu(target);
        mode_select->setPosition(0.5f, 0.5f);

        mode_select->addItem("House Poker");
        mode_select->addItem("Hold 'em");
        mode_select->addItem("Blackjack");
        mode_select->addItem("Settings"); 
        mode_select->alignMiddle();
        target->Commands.Add(10, std::bind(&MainMenu::Select, this));
    }

    void MainMenu::Update()
    {
        mode_select->setPosition(0.5f, 0.5f);
        mode_select->alignMiddle();
    }

    void MainMenu::Select()
    {
        auto lambda = [](Window* target, Application* handle) { target->Bind(new MainMenu(handle)); };

        int selection = mode_select->getSelectedIndex();
        if (selection == 3)
        {
            target->callback_stack.Push(KEY_F(3), std::bind(lambda, target, app));
            target->Bind(new Config());
        }
        else
            app->SetupGame(selection);
    }
}
