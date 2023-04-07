#pragma once

#include "View.h"

using namespace sf;
#define Pole_h 20
#define Pole_W 30

enum Dir { Right, Left, Down, Up };
String Pole[Pole_h] = {
	"##############################",
	"#     l           l          #",
	"# l         l                #",
	"#     bb    b    b     b b   #",
	"#                            #",
	"#     l   b  l      l b      #",
	"#     b                b     #",
	"#       l      l             #",
	"#             b       b      #",
	"#   l         b          l   #",
	"#                            #",
	"#                            #",
	"#    lb     lbl    lb        #",
	"#                            #",
	"#           b     l     b    #",
	"#   b       b        l       #",
	"#                            #",
	"#   l      l       l    l    #",
	"#                            #",
	"##############################",
};

class Player
{
	Texture texture;

	Image image;
protected:

	float row;                       //координата по оси X
	float col;						 //координата по оси X
	int health;						 //жизнь
	float spx;						 //скорость по X
	float spy;						 //скорость по Y
	float width;
	float height;
	bool IsAlive;
	String Type;
	Sprite sprite;
	int Dir = 0;
	float speed = 0;
public:

	Player(Image& image, float row, float col, float w, float h, String type, int health = 100) :row(row), col(col), width(w), spx(), spy(), height(h), Type(type), health(health), IsAlive(true)
	{
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setPosition(row, col);
	}

	float getspy() { return spy; }
	float getspx() { return spx; }
	float getplayerX() { return row; }
	float getplayY() { return col; }
	int getHealthy() { return health; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	bool getIsAlive() { return health >= 0; }
	Sprite getSprite() { return sprite; }
	float Getspeed() { return speed; }
};

class Main_Character : public Player
{
private:
	int Score;        //oчки

public:
	int GetScore() { return Score; }
	Main_Character(Image& image, float row, float col, float w, float h, String name, int health = 100) :Player(image, row, col, w, h, name, health), Score()
	{
		sprite.setTextureRect(IntRect(47, 51, w, h));
	}
	void update(float time)
	{
		control(time);
		switch (Dir)
		{
		case Right: spx = speed; spy = 0; break;// вправо
		case Left: spx = -speed; spy = 0; break;// влево
		case Down: spx = 0; spy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case Up: spx = 0; spy = -speed; break;
		}
		row += spx * time;
		ActionWithPole(spx, 0);
		col += spy * time;
		ActionWithPole(0, spy);
		if (speed != 0) {
			speed = 0;//для того чтобы персонаж не шел вечно
			sprite.setPosition(row, col);
		}
		if (health <= 0) { IsAlive = false; speed = 0; }
		if (IsAlive) {
			setPlayerCoordinateView(row, col);
		}
	}

	//Столновение персонажа с картой
	void ActionWithPole(float spx, float spy)
	{
		int size = 50;
		for (int i = col / size; i < (col + height) / size; i++)

			for (int j = row / size; j < (row + width) / size; j++) {
				if (Pole[i][j] == '#')
				{
					if (spy > 0) { col = i * size - height; spy = 0; }
					if (spy < 0) { col = i * size + size; spy = 0; }
					if (spx > 0) { row = j * size - width; }
					if (spx < 0) { row = j * size + size; }
				}
				if (Pole[i][j] == 'l')
				{
					Score += 10;
					Pole[i][j] = ' ';
				}
				if (Pole[i][j] == 'b')
				{
					speed = 0;
					spx = 0; spy = 0;
				}

			}
	}
	//Управления с персонажем
	void control(float time) {
		float flame = 0;
		if (Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))
		{

			Dir = Left; speed = 0.1;
			flame += 0.005 * time;
			
			if (flame > 3) { flame -= 3; }

			sprite.setTextureRect(IntRect(47 * int(flame), 53, 51, 47));
			setPlayerCoordinateView(row, col);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))
		{
			Dir = Right; speed = 0.1;
			flame += 0.005 * time;
			
			if (flame > 3) { flame -= 3; }
			sprite.setTextureRect(IntRect(47 * int(flame), 103, 51, 47));
			setPlayerCoordinateView(row, col);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{

			Dir = Up; speed = 0.1;
			flame += 0.005 * time;
			
			if (flame > 3) { flame -= 3; }
			sprite.setTextureRect(IntRect(47 * int(flame), 154, 51, 47));
			setPlayerCoordinateView(row, col);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			Dir = Down; speed = 0.1;
			flame += 0.005 * time;
			
			if (flame > 3) { flame -= 3; }
			sprite.setTextureRect(IntRect(47 * int(flame), 3, 51, 47));
			setPlayerCoordinateView(row, col);
		}

	}

	//оружие игрока (бомба)
	void bomb(RenderWindow& window)
	{
		window.setMouseCursorVisible(false);
		Image bomb_image;
		bomb_image.loadFromFile("image/bomb.png");
		Texture bomb_png;
		bomb_png.loadFromImage(bomb_image);
		Sprite bomb_sprite;
		bomb_sprite.setTexture(bomb_png);
		bomb_sprite.setPosition(row - 50, col);
		window.draw(bomb_sprite);

		window.display();
	}
};
class Enemy : public Player
{
public:
	Enemy(Image& image, float row, float col, float w, float h, String name, int health = 100) :Player(image, row, col, w, h, name, health) {
		sprite.setTextureRect(IntRect(0, 0, w, h));
		spx = 0.1;
	}

	void ActionWithPole(float Spx, float Spy)
	{
		
		int size = 50;
		for (int i = col / size; i < (col + height) / size; i++)
			for (int j = row / size; j < (row + width) / size; j++)
			{
				if (Pole[i][j] == '#')//если элемент наш тайлик земли, то
				{
					if (Spy > 0) { col = i * size - height; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
					if (Spy < 0) { col = i * size + size; }//столкновение с верхними краями карты(может и не пригодиться)
					if (Spx > 0) { row = j * size - width; spx = -0.1; sprite.scale(-1, 1); }//с правым краем карты
					if (Spx < 0) { row = j * size + size; spx = 0.1; sprite.scale(-1, 1); }// с левым краем карты
				}

				if (Pole[i][j] == 'l')
				{
					spx = 0;
				}
			
			}
	}

	void update(float time)
	{

		ActionWithPole(spx, 0);
		row += spx * time;
		sprite.setPosition(row + width / 2, col + height / 2);
		if (health <= 0) {
			IsAlive = false;
		}
	}


};


