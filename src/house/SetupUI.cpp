#include <house/SetupUI.hpp>
#include <house/GameUI.hpp>

#include <app/Application.hpp>

namespace house
{
        
    SetupUI::SetupUI(cardgame::Application* handle) : app(handle)
    {
    
    }

    void SetupUI::Initialize()
    {
        menu = new ucurses::Menu(target);

        menu->setPosition(0.5f, 0.5f);
        menu->addItem("$10 Min (Recommended)");
        menu->addItem("$25 Min");
        menu->addItem("$50 Min");
        menu->alignMiddle();

        menu->onSelect = [=]()
        {
            app->StartGame(); 
        };

    }
    
}

