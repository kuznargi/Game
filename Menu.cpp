#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Menu.h"

MainMenu::MainMenu(float WIDTH, float HEIGHT)
{
	if (!font.loadFromFile("Font/troika.otf"))
	{
		std::cout << "Font don't download" << endl;
	}
	
mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::Red);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(400, 500);
	mainMenu[0].setOutlineThickness(3);
	mainMenu[0].setOutlineColor(Color::Black);
	
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::Red);
	mainMenu[1].setString("About author");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(250, 600);
	mainMenu[1].setOutlineThickness(3);
	mainMenu[1].setOutlineColor(Color::Black);

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::Red);
	mainMenu[2].setString("About game");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(280, 700);
	mainMenu[2].setOutlineThickness(3);
	mainMenu[2].setOutlineColor(Color::Black);


	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::Red);
	mainMenu[3].setString("Exit");
	mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(400, 800);
	mainMenu[3].setOutlineThickness(3);
	mainMenu[3].setOutlineColor(Color::Black);


	MainMenuSelected = 0;

	mainMenu[MainMenuSelected].setFillColor(Color::Yellow);

}
MainMenu::~MainMenu()
{

}
void MainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < Max_Count_Menu; ++i)
	{
		window.draw(mainMenu[i]);
	}
}
void MainMenu::MoveUp()
{
	MainMenuSelected--;
	if (MainMenuSelected >= 0)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::Yellow);
		mainMenu[MainMenuSelected + 1].setFillColor(Color::Red);
	}
	else {
		mainMenu[0].setFillColor(Color::Red);
		MainMenuSelected = Max_Count_Menu - 1;
		mainMenu[MainMenuSelected].setFillColor(Color::Yellow);
	}
	
}
void MainMenu::MoveDown()
{
		MainMenuSelected++;
	if (MainMenuSelected  < Max_Count_Menu)
	{
		mainMenu[MainMenuSelected-1].setFillColor(Color::Red);
		mainMenu[MainMenuSelected].setFillColor(Color::Yellow);
	
	}
	else
	{
		mainMenu[Max_Count_Menu - 1].setFillColor(Color::Red);
		MainMenuSelected = 0;
		mainMenu[MainMenuSelected].setFillColor(Color::Yellow);

	}

}
