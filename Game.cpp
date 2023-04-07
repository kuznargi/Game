#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
#include "Menu.h"
#include "Player.h"
#include "View.h"


void StartGame() {

	//создание окна самой »гры
	RenderWindow Play(VideoMode(1920, 1080), L"Bamberman", Style::Fullscreen);
	//изображение дл€ игрока
	Image image_main_player;
	image_main_player.loadFromFile("image/person.png");
	Main_Character play(image_main_player, 50, 50, 47, 51, "Mainplayer", 100);

	//изображение дл€ врага
	Image image_enamy;
	image_enamy.loadFromFile("image/enemy.png");
	Enemy enemy(image_enamy, 350, 500, 50, 50, "Enemy", 100);
	
	//изображение дл€ поле
	Image pole_image;
	pole_image.loadFromFile("image/blocks.png");
	Texture pole_texture;
	pole_texture.loadFromImage(pole_image);
	Sprite pole_sprite;
	pole_sprite.setTexture(pole_texture);


	Image image;
	image.loadFromFile("image/bomba.png");
	Texture texture;
	texture.loadFromImage(image);
	Sprite sprite;
	sprite.setTexture(texture);

	

	Event event_play;// —обытие дл€ игрока
	Clock clock;
	while (Play.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		
		clock.restart();
		time /= 700;
		Event event;

		while (Play.pollEvent(event))
		{
			if (event.key.code == Keyboard::Escape)
				Play.close();
		}

		enemy.update(time);
		play.update(time);
		viewmap(time);
		Play.setView(view);
		Play.clear();

		for (int i = 0; i < Pole_h; i++)
			for (int j = 0; j < Pole_W; j++)
			{

				if (Pole[i][j] == ' ')  pole_sprite.setTextureRect(IntRect(0, 0, 50, 50)); //если встретили символ пробел, то рисуем 1й квадратик
				if (Pole[i][j] == 'l')  pole_sprite.setTextureRect(IntRect(50, 0, 50, 50));//если встретили символ l, то рисуем ломающий квадратик
				
				if (Pole[i][j] == 'b')  pole_sprite.setTextureRect(IntRect(100, 0, 50, 50));//если встретили символ l, то рисуем неломающий квадратик

				if ((Pole[i][j] == '#')) pole_sprite.setTextureRect(IntRect(150, 0, 50, 50));//если встретили символ #, то рисуем границу
				//если встретили символ 0, то рисуем 3й квадратик
			


				pole_sprite.setPosition(j * 50, i * 50);

				Play.draw(pole_sprite);//рисуем квадратики на экран
			}
if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			int i = 0;
			while (i <= 500)
			{
				play.bomb(Play);
				i++;
			}
			i = 0;
			sprite.setTextureRect(IntRect(0, 0, 30, 100));
			sprite.setPosition(play.getplayerX() - 50, play.getplayY());
			while (i <= 500) {
				Play.draw(sprite); Play.display();
				i++;
			}
		}

		
		Play.draw(enemy.getSprite());
		Play.draw(play.getSprite());
		Play.display();
	}
}
void Options(Music& mus) {
	mus.stop();
	Music music;
	if (!music.openFromFile("aboutgame.ogg")) return;
	music.setLoop(true);
	music.setVolume(50);
	music.play();
	RenderWindow Options(VideoMode(1920, 1080), "Options");
	Image nastroiki_image;
	nastroiki_image.loadFromFile("image/nastroiki.jpg");
	Texture n_texture;
	n_texture.loadFromImage(nastroiki_image);
	Sprite n_sprite;
	n_sprite.setTexture(n_texture);

	Event event_option;
	while (Options.isOpen())
	{
		while (Options.pollEvent(event_option))
		{
			if (event_option.type == Event::KeyPressed) {
				if (event_option.key.code == Keyboard::Escape)	Options.close();
			}

		}
		Options.draw(n_sprite);
		//Options.display();

	   // Options.clear();
		Options.display();
	}
	music.stop();
	mus.play();

}
void About_Authour() {



	RenderWindow About_author(VideoMode(1920, 1080), "Author_Nargiz");

	Image about_author;
	about_author.loadFromFile("Nargiza.png");
	Texture about_texture;
	about_texture.loadFromImage(about_author);
	Sprite about_author_S;
	about_author_S.setTexture(about_texture);

	Event event_option;
	while (About_author.isOpen())
	{
		while (About_author.pollEvent(event_option))
		{

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				About_author.close();

			}


		}

		About_author.draw(about_author_S);
		/*	Option.display();
				Option.clear();*/

		About_author.display();
	}


}
int main()
{
	RenderWindow Menu(VideoMode(1920, 1080), "Main Menu", Style::Default);
	view.reset(sf::FloatRect(0, 0, 1920, 1080));



	//Photo for main menu
	MainMenu menu(Menu.getSize().x, Menu.getSize().y);
	RectangleShape background;
	background.setSize(Vector2f(1920, 1080));
	Texture texture;
	texture.loadFromFile("image/menu.png");
	background.setTexture(&texture);


	Music music;
	if (!music.openFromFile("horror.ogg")) return 25;
	music.setLoop(true);
	music.setVolume(50);
	music.play();

	while (Menu.isOpen())
	{

		
		Event event;
		while (Menu.pollEvent(event))
		{
			
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)
				{
					menu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down)
				{
					menu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Return)
				{



					switch (menu.GetMainMenuPressed())
					{
					case 0: StartGame(); break;
					case 1: About_Authour();  break;
					case 2: Options(music); break;
					case 3: Menu.close(); break;
					
					}
				}
			}
					
			}
			Menu.clear();
			Menu.draw(background);
			menu.draw(Menu);
			Menu.display();
		}
	return 0;
	}


void Exit(){}