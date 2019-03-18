#include <app/Application.hpp>
#include <app/MainMenu.hpp>
#include <app/Config.hpp>
#include <app/Game.hpp>

#include <house/Game.hpp>
#include <house/GameUI.hpp>
#include <house/SetupUI.hpp>

#include <holdem/Game.hpp>
#include <holdem/GameUI.hpp>

#include <player/PlayerCreate.hpp>

#include <fstream>
#include <stdlib.h>

namespace cardgame {

    Application::Application() : game_data(nullptr)
    {
        setName("Card Games");
    }

    Application::~Application()
    {
        delete game_data;
    }

    void Application::onClose()
    {
        system("load_config ./.resources/original_config.conf");
    }

    void Application::Update()
    {

    }

    void Application::onStart()
    {
        appwindow->Bind(new MainMenu(this));
    }

    void Application::SetupGame(unsigned int type)
    {
        GameUI* game_ui;
        switch (type)
        {
            case 0:
                game_data = new house::Game();
                game_ui = new house::GameUI(this, dynamic_cast<house::Game*>(game_data));
                break;
            case 1:
                game_data = new holdem::Game();
                game_ui = new holdem::GameUI(this, dynamic_cast<holdem::Game*>(game_data));
                break;
            case 2:
                game_data = new house::Game();
                game_ui = new house::GameUI(this, dynamic_cast<house::Game*>(game_data));
                break;
        }

        if (game_data->saveExists())
            game_data->Load();
        else
            CreatePlayer(appwindow, this);
                
        game_data->_SetType(type);
        game_data->Setup();

        appwindow->Bind(game_ui);
        //appwindow->Bind(new house::SetupUI(this));
    }
            
    void Application::StartGame()
    {
    
    }

}
