#pragma once
#include <class/Game.hpp>
#include <gui/GameUI.hpp>
#include <gui/MainMenu.hpp>
#include <gui/SingleplayerScreen.hpp>
class UI
{

    public:

        // GUI states
        GameUI game_ui;
        MainMenu main_menu;

        Game* game_data;

};
