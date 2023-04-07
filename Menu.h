#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#define WIDTH
#define HEIGHT
#define Max_Count_Menu 4
class MainMenu
{
private:
	int MainMenuSelected;
	Font font;
	Text mainMenu[Max_Count_Menu];
public:
	MainMenu(float WIDTH, float HEIGHT);

	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	
	int GetMainMenuPressed()
	{
		return MainMenuSelected;
}
	~MainMenu();

};//Person

