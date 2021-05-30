#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>

class Button
{
public:

	Button(sf::Vector2f pos, sf::Font font)
		: active_str{ "" }, unactive_str{ "" }
	{
		position = pos;
		textFont = font;
		button.setSize(sf::Vector2f(80.0f, 20.0f));
		button.setPosition(position);

		text.setString("");
		text.setFont(textFont);
		text.setColor(sf::Color::Yellow);
		text.setCharacterSize(20);
		text.setPosition({pos.x+8.0f, pos.y-1.0f});
	}

	void set_strings(std::string active_str, std::string unactive_str)
	{
		this->active_str = active_str;
		this->unactive_str = unactive_str;
		text.setString(this->unactive_str);
	}

	void drawTo(sf::RenderWindow& window)
	{
		check_hover(window);
		window.draw(button);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow& window)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY)
		{
			return true;
		}
		
		return false;
	}

	void check_status(sf::RenderWindow& window)
	{
		if (isMouseOver(window))
		{
			isActive = !isActive;
			if (isActive)
				text.setString(active_str);
			else if (!isActive)
				text.setString(unactive_str);
		}
	}

	void check_hover(sf::RenderWindow& window)
	{
		if (isMouseOver(window))
			button.setFillColor(sf::Color::Green);
		else
			button.setFillColor(sf::Color::Black);
	}

	bool is_active()
	{
		return isActive;
	}

	void set_unactive()
	{
		isActive = false;
		text.setString(unactive_str);
	}

private:
	
	std::string active_str;
	std::string unactive_str;
	bool isActive{ false };
	bool isHovering{ false };

	sf::Vector2f position;
	sf::Color currentColor{ sf::Color::Black };

	sf::Font textFont;
	sf::RectangleShape button;
	sf::Text text;

};
