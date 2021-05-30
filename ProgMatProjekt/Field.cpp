#include "Field.h"

int Field::rnd(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

sf::Color Field::currentColor(int colorSelection)
{
    sf::Color returnColor;
    switch (colorSelection)
    {
    case 0:
        returnColor = sf::Color(rnd(155,255), 0 , 0);
        break;
    case 1:
        returnColor = sf::Color(0, rnd(155, 255), 0);
        break;
    case 2:
        returnColor = sf::Color(0, 0, rnd(155, 255));
        break;
    }
    return returnColor;
}

Field::Field(int x, int y)
{
    float size{ 20.0f };
    sqr.setSize({ size, size });
    sqr.setPosition({ size * x, size * y });
    sqr.setFillColor(sf::Color(rnd(10,20),rnd(10,20),rnd(10,20)));
    sqr.setOutlineThickness(0.5f);
    sqr.setOutlineColor(sf::Color(30, 30, 30));
    set_xy(x, y);
}

bool Field::is_alive()
{
    return isAlive;
}

void Field::set_xy(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Field::set_status(bool status, int colorSelection)
{
    if (status)
    {
        sqr.setFillColor(currentColor(colorSelection));
        hasDied = false;
    }
    else if (!status && !hasDied)
    {
        hasDied = true;
    }
    isAlive = status;
}

void Field::draw_field(sf::RenderWindow& window)
{
    window.draw(sqr);
}

void Field::recolor_dead()
{
    if (!isAlive && hasDied)
        sqr.setFillColor(sf::Color(rnd(30, 70), 0, 0));
}

void Field::reset_status()
{
    hasDied = false;
    isAlive = false;
    sqr.setFillColor(sf::Color(rnd(10, 20), rnd(10, 20), rnd(10, 20)));
}
