#pragma once

#include<vector>
#include<iostream>
#include"Field.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Audio.hpp>

class Game
{
private:
	const int xaxis{ 96 };
	const int yaxis{ 54 };
	int colorSwitch{ 1 };
	std::vector<std::vector<Field>> grid;
	sf::SoundBuffer fieldSoundBuffer;
	sf::Sound fieldSound;
public:
	Game();
	void start_game();
	void set_startField(int x, int y);
	void update_grid();
	void draw_grid(sf::RenderWindow& window);
	void get_nbr_coordinates(int& x, int& y, int index);
	void clear_grid();
	void set_colorSwitch(int colorSwitch);
	int get_x_axis();
	int get_y_axis();
};