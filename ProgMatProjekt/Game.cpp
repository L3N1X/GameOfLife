#include "Game.h"
#include<iostream>

Game::Game()
{
	start_game();
}

void Game::start_game() //Inicijalizira igru, popunjuje sve kvadratice
{
	grid.reserve(yaxis);
	for (int y = 0; y < yaxis; ++y)
	{
		std::vector<Field> row;
		row.reserve(xaxis);
		for (int x = 0; x < xaxis; ++x)
		{
			row.emplace_back(x, y);
		}
		grid.push_back(row);
	}
	if (!fieldSoundBuffer.loadFromFile("\Sounds\\boopSound.ogg"))
	{
		std::cout << "ERROR : LOADING SOUND FAILED" << std::endl;
	}
	fieldSound.setBuffer(fieldSoundBuffer);
}

void Game::set_startField(int x, int y) //Postavlja pocetne zive kvadratice
{
	grid[y][x].set_status(true, colorSwitch);
}

void Game::update_grid() //Osvjezava stanje polja za svaki frame
{
	std::vector<std::vector<Field>> nextGenerationGrid{ grid };
	for (int i{ 1 }; i < yaxis - 1; ++i)
	{
		for (int j{ 1 }; j < xaxis - 1; ++j)
		{
			int aliveCount{ 0 };
			for (int index{ 0 }; index < 8; ++index)
			{
				int nbrX{ j }, nbrY{ i };
				get_nbr_coordinates(nbrX, nbrY, index);
				if (grid[nbrY][nbrX].is_alive())
					++aliveCount;
			}
			if (grid[i][j].is_alive() && aliveCount <= 1) //Polje umre od usamljenjosti
			{
				nextGenerationGrid[i][j].set_status(false, colorSwitch);
				fieldSound.play();
			}
			else if (grid[i][j].is_alive() && aliveCount >= 4) //Ubije prenapuceno polje
			{
				nextGenerationGrid[i][j].set_status(false, colorSwitch);
				fieldSound.play();
			}
			else if (grid[i][j].is_alive() && aliveCount >= 2 && aliveCount <= 3)
				nextGenerationGrid[i][j].set_status(true, colorSwitch); //Sprema konstantnte promjene za zive - moze biti iskljuceno.
			else if (!grid[i][j].is_alive() && aliveCount == 3) //Ozivi mrtvo polje
			{
				nextGenerationGrid[i][j].set_status(true, colorSwitch);
				fieldSound.play();
			}
		}
	}
	grid = nextGenerationGrid;
}

void Game::draw_grid(sf::RenderWindow& window) //Iscrtava sve kvadratice
{
	for (int i{ 0 }; i != grid.size(); ++i)
	{
		for (int j{ 0 }; j != grid[i].size(); ++j)
		{
			grid[i][j].recolor_dead(); //Stalno mijenjaj boju onih  koji su umrli.
			grid[i][j].draw_field(window);
		}
	}
}

void Game::get_nbr_coordinates(int& x, int& y, int index) //Dobiva koordinate susjeda
{
	switch (index)
	{
	case 0:
		x--;
		y--;
		break;
	case 1:
		y--;
		break;
	case 2:
		x++;
		y--;
		break;
	case 3:
		x++;
		break;
	case 4:
		x++;
		y++;
		break;
	case 5:
		y++;
		break;
	case 6:
		x--;
		y++;
		break;
	case 7:
		x--;
		break;
	}
}

void Game::clear_grid()
{
	for (int i{ 0 }; i != grid.size(); ++i)
	{
		for (int j{ 0 }; j != grid[i].size(); ++j)
		{
			grid[i][j].reset_status();
		}
	}
}

void Game::set_colorSwitch(int colorSwitch)
{
	this->colorSwitch = colorSwitch;
}

int Game::get_x_axis()
{
	return xaxis - 1; //-1 Zato jer koristim get_x_axis kao zadnji index
}

int Game::get_y_axis()
{
	return yaxis - 1;
}
