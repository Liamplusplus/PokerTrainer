#include <gui/MainMenu.hpp>


int main()
{
   	UCurses gui;
	Window* mainwindow = gui.createWindow();


    Game game;
	mainwindow->Bind(new blackjack::MainMenu(&game));

	gui.Run(); 
}
