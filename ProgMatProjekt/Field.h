#pragma once
#include<string>
#include<vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

class Field
{
private:
	int x{ 0 };
	int y{ 0 };
	bool isAlive{ false };
	bool hasDied{ false };
	//Graphics
	sf::RectangleShape sqr;
	sf::Color aliveColor;
private:
	int rnd(int min, int max);
	sf::Color currentColor(int colorSelection);
public:
	Field(int x, int y);
	bool is_alive();
	void set_xy(int x, int y);
	void set_status(bool status, int colorSelection);
	//Graphics
	void draw_field(sf::RenderWindow& window);
	void recolor_dead();
	void reset_status();
};

