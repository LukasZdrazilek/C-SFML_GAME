#include "Interface.h"
#include <iostream>

void Interface::loadTextures()
{
	hitpointTexture.loadFromFile("Textures/HP.png");
}

void Interface::drawFont(sf::RenderWindow& window)
{
	this->font = font;
	font.loadFromFile("font.ttf");
	hitpointText.setFont(font);
	hitpointText.setCharacterSize(24);
	hitpointText.setFillColor(sf::Color::White);
	hitpointText.setPosition(10.0f, 10.0f);			// pozice textu	
}

void Interface::update(int hitpoints)
{
	hitpointText.setString("HP: " + std::to_string(hitpoints));
}

void Interface::draw(sf::RenderWindow& window)
{
	//window.draw(hitpointText);	nejde zatim
	if (hitPoints == 3)
	{
		window.draw(hitPoint1);
		window.draw(hitPoint2);
		window.draw(hitPoint3);
	}
	else if (hitPoints == 2)
	{
		window.draw(hitPoint1);
		window.draw(hitPoint2);
	}
	else
		window.draw(hitPoint1);
	//drawFont(window);
}

void Interface::updateHPPositions(Player player)
{
	hitPoint1.setPosition({ (float)player.getX() - 340, (float)player.getY() - 160 });
	hitPoint2.setPosition({ (float)player.getX() - 290, (float)player.getY() - 160 });
	hitPoint3.setPosition({ (float)player.getX() - 240, (float)player.getY() - 160 });
}

void Interface::handleUI(sf::RenderWindow& window, Player player)
{

	HP.push_back(hitPoint1);
	HP.push_back(hitPoint2);
	HP.push_back(hitPoint3);

	hitPoint1.setTexture(hitpointTexture);
	hitPoint3.setTexture(hitpointTexture);
	hitPoint2.setTexture(hitpointTexture);
       
	updateHPPositions(player);
}