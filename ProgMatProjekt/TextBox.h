#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

class TextBox
{
public:
	//TextBox() {}

	TextBox(int size, sf::Color color, bool sel)
	{
		textbox.setCharacterSize(size);
		textbox.setColor(color);
		isSelected = sel;
		if (sel)
		{
			textbox.setString("_");
		}
		else
		{
			textbox.setString("");
		}
		rectangle.setSize(sf::Vector2f(70.0f, 20.0f));
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setOutlineThickness(1.0f);
		rectangle.setOutlineColor(sf::Color::Magenta);
	}

	void setFont(sf::Font &font)
	{
		textbox.setFont(font);
	}

	void setPosition(sf::Vector2f pos)
	{
		textbox.setPosition(pos);
		rectangle.setPosition(pos);
	}

	void setLimit(bool ToF)
	{
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim)
	{
		hasLimit = ToF;
		limit = lim - 1;
	}

	void setSelected(bool sel)
	{
		isSelected = sel;
		if (!sel)
		{
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++)
			{
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	std::string getText()
	{
		return text.str();
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(rectangle);
		window.draw(textbox);
	}

	void typedOn(sf::Event input)
	{
		if (isSelected)
		{
			int charTyped = input.text.unicode;
			if ((charTyped <= 57 && charTyped >= 48) || charTyped == 46 || charTyped == 45 || charTyped == DELETE_KEY)
			{
				if (hasLimit)
				{
					if (text.str().length() <= limit)
					{
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
				}
				else
				{
					inputLogic(charTyped);
				}
			}
		}
	}

	bool isMouseOver(sf::RenderWindow& window)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = rectangle.getPosition().x;
		float btnPosY = rectangle.getPosition().y;

		float btnxPosWidth = rectangle.getPosition().x + rectangle.getLocalBounds().width;
		float btnyPosHeight = rectangle.getPosition().y + rectangle.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY)
		{
			return true;
		}

		return false;
	}

private:

	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;

	sf::RectangleShape rectangle;

	void inputLogic(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		{
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "_");
	}
	void deleteLastChar()
	{
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		text.str("");
		text << newT;

		textbox.setString(text.str());
	}
};

