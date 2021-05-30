#include <iostream>
#include <ctime>
#include <chrono>
#include <queue>
#include <fstream>

#include"Game.h"
#include"TextLoader.h"
#include"SpriteButton.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Audio.hpp>

using namespace std::chrono;

/******SOURCE FUNCTIONS START******/

int float_to_index(float& pos)
{
	int index;
	index = 10.0f + pos; //33.4
	index = (int)(pos - (int)pos % 10); //30.4 - 0.4
	index = pos / 10; //3 -- To je index koji trazimo
	index = index / 2; //Jer imamo rezolucija / 20 kvadratica
	return index;
}

std::pair<int, int> make_cooridnates_alive(sf::RenderWindow& window)
{
	sf::Vector2f mousePos{ sf::Mouse::getPosition() };
	std::pair<int, int> coordinates{ float_to_index(mousePos.x), float_to_index(mousePos.y) };
	return coordinates;
}

bool isMouseInWindow(sf::RenderWindow& window)
{
	sf::Vector2f windowSize{ window.getSize() };
	sf::Vector2f mousePos{ sf::Mouse::getPosition() };
	if (mousePos.x >= 0.0f && mousePos.x <= windowSize.x && mousePos.y >= 0.0f && mousePos.y <= windowSize.y)
		return true;
	return false;
}

bool isMouseInCornerSquare(std::pair<int, int>& msp, int xaxis, int yaxis)
{
	//xaxis and yaxis are indexes of each square inside grid
	if (msp.first != 0 && msp.second != 0 && msp.first
		!= xaxis && msp.second != yaxis)
		return false;
	return true;
}

/******SOURCE FUNCTIONS END******/

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "GameOfLife Leon Kruslin", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	srand(time(nullptr));

	sf::Font font;
	if (!font.loadFromFile("\Fonts\\ralewayFont.ttf"))
	{
		std::cout << "ERROR: Loading resource file failed" << std::endl;
		return 1;
	}

	Game game;
	sf::Clock clock;

	sf::RectangleShape signature;
	sf::Texture signatureTexture;
	if (!signatureTexture.loadFromFile("\Textures\\signature.png"))
	{
		std::cout << "ERROR: Loading signature.png failed" << std::endl;
		return 1;
	}
	signature.setTexture(&signatureTexture);
	signature.setSize({ 100.0f,100.0f });
	signature.setPosition({ 1800.0f,1000.0f });

	sf::RectangleShape menu;
	menu.setFillColor(sf::Color(20, 20, 20));
	menu.setPosition({ 10.0f, 980.0f });
	menu.setSize({ 700.0f,100.0f });

	TwoStateButton playButton{ {10.0f,980.0f}, 1.0f, "\Textures\\playButton.png", "\Textures\\pauseButton.png" };
	playButton.setHoverTextures("\Textures\\pauseHoveredButton.png","\Textures\\playHoveredButton.png");
	playButton.setSounds("\Sounds\\mehSound.ogg", "\Sounds\\fartSound.ogg");
	//HoverTextures su obrnute zbog izgleda

	TwoStateButton clearButton{ {10.0f + 100.0f,980.0f}, 1.0f, "\Textures\\clearButton.png","\Textures\\clearButton.png" };
	clearButton.setHoverTextures("\Textures\\clearHoveredButton.png", "\Textures\\clearHoveredButton.png");
	clearButton.setSounds("\Sounds\\mehSound.ogg", "\Sounds\\fartSound.ogg");

	TwoStateButton undoButton{ {10.0f + 200.0f,980.0f}, 1.0f, "\Textures\\undoButton.png","\Textures\\undoButton.png" };
	undoButton.setHoverTextures("\Textures\\undoHoveredButton.png", "\Textures\\undoHoveredButton.png");
	undoButton.setSounds("\Sounds\\mehSound.ogg", "\Sounds\\fartSound.ogg");

	TwoStateButton exitButton{ {10.0f + 300.0f,980.0f}, 1.0f, "\Textures\\exitButton.png","\Textures\\exitButton.png" };
	exitButton.setHoverTextures("\Textures\\exitHoveredButton.png", "\Textures\\exitHoveredButton.png");
	exitButton.setSounds("\Sounds\\mehSound.ogg", "\Sounds\\fartSound.ogg");

	TwoStateButton colorRedButton{ {10.0f + 400.0f,980.0f}, 1.0f, "\Textures\\red.png","\Textures\\red.png" };
	colorRedButton.setHoverTextures("\Textures\\redHovered.png", "\Textures\\redHovered.png");
	colorRedButton.setSounds("\Sounds\\mehSound.ogg", "\Sounds\\fartSound.ogg");

	TwoStateButton colorGreenButton{ {10.0f + 500.0f,980.0f}, 1.0f, "\Textures\\green.png","\Textures\\green.png" };
	colorGreenButton.setHoverTextures("\Textures\\greenHovered.png", "\Textures\\greenHovered.png");
	colorGreenButton.setSounds("\Sounds\\mehSound.ogg", "\Sounds\\fartSound.ogg");

	TwoStateButton colorBlueButton{ {10.0f + 600.0f,980.0f}, 1.0f, "\Textures\\blue.png","\Textures\\blue.png" };
	colorBlueButton.setHoverTextures("\Textures\\blueHovered.png", "\Textures\\blueHovered.png");
	colorBlueButton.setSounds("\Sounds\\mehSound.ogg", "\Sounds\\fartSound.ogg");

	std::queue<std::pair<int, int>> previousState;
	int colorSelection{ 1 };

	//Main variables end

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //If left button is clicked
			{
				playButton.checkActiveStatus(window); //Jedini ima ovako jer je trenutno jedini gumb koji se drzi u dva stanja
				if (playButton.isMouseOver(window))
				{
					playButton.playClickSound();
				}
				else if (clearButton.isMouseOver(window)) //Kliknut je clearButton
				{
					clearButton.playClickSound();
					game.clear_grid();
				}
				else if (exitButton.isMouseOver(window)) //Kliknut je exitButton
				{
					clearButton.playClickSound();
					window.close();
				}
				else if (colorRedButton.isMouseOver(window) && !playButton.is_active()) //Kliknut je redButton
				{
					colorRedButton.playClickSound();
					colorSelection = 0;
					game.set_colorSwitch(colorSelection);
				}
				else if (colorGreenButton.isMouseOver(window) && !playButton.is_active()) //Kliknut je greenButton
				{
					colorGreenButton.playClickSound();
					colorSelection = 1;
					game.set_colorSwitch(colorSelection);
				}
				else if (colorBlueButton.isMouseOver(window) && !playButton.is_active()) //kliknut je blueButton
				{
					colorBlueButton.playClickSound();
					colorSelection = 2;
					game.set_colorSwitch(colorSelection);
				}
				else if (undoButton.isMouseOver(window) && playButton.is_active()) //Kliknut je undoButton
				{
					undoButton.playClickSound();
					while (!previousState.empty())
					{
						game.set_startField(previousState.front().first, previousState.front().second);
						previousState.pop();
					}
				}
			}
		}

		sf::Time dt = clock.restart();
		auto begin{ high_resolution_clock::now() };

		/******START DRAWING*******/

		game.draw_grid(window);

		window.draw(menu);
		playButton.drawTo(window);
		exitButton.drawTo(window);
		clearButton.drawTo(window);
		undoButton.drawTo(window);

		colorRedButton.drawTo(window);
		colorGreenButton.drawTo(window);
		colorBlueButton.drawTo(window);

		window.draw(signature);
		

		/******END DRAWING*******/

		/******START LOOP CONTROLS*******/

		if (!playButton.is_active())
		{
			game.update_grid();
		}

		else if (playButton.is_active())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseInWindow(window))
			{
				std::pair<int, int> aliveCoordinates{ make_cooridnates_alive(window) };
				if (!isMouseInCornerSquare(aliveCoordinates, game.get_x_axis(), game.get_y_axis()))
				{
					game.set_startField(aliveCoordinates.first, aliveCoordinates.second);
					previousState.push(aliveCoordinates);
				}
			}
		}

		/******END LOOP CONTROLS*******/

		window.display();

		//Frametime output
		auto end{ high_resolution_clock::now() };
		auto total{ duration_cast<milliseconds>(end - begin).count() };
		std::cout << "Frame time -> " << total << " ms" << std::endl;
	}

	//Console start
	std::string s("\Files\\Banner.txt");
	TextLoader txtldr(s);
	std::cout << txtldr.output() << std::endl;
	//Console end

	//Debug start -- Nije jos potrebno
	std::ofstream out("\Files\\previousStateOutput.csv");
	if (!out)
	{
		std::cout << "ERROR: File can't open" << std::endl;
		return 1;
	}
	out << "x;y" << std::endl;
	while (!previousState.empty())
		//Problem kod previouseStatea je sto sprema duplikate
	{
		out << previousState.front().first << ";" << previousState.front().second
			<< std::endl;
		previousState.pop();
	}
	out.close();
	//Debug end
	return 0;
}