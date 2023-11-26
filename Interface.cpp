#include "Interface.h"

void Interface::loadTextures()
{
	hitpointTexture.loadFromFile("Textures/HP.png");
	//hitpointTexture.setSmooth(true);
	font.loadFromFile("font.ttf");
	moneyText.setFont(font);
	moneyText.setCharacterSize(16);
	moneyText.setFillColor(sf::Color::White);
}

void Interface::loadFont()
{
	
}

void Interface::draw(sf::RenderWindow& window)
{
	window.draw(moneyText);

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
}

void Interface::updatePositions(Player player)
{
	hitPoint1.setPosition({ (float)player.getX() - 340, (float)player.getY() - 160 });
	hitPoint2.setPosition({ (float)player.getX() - 290, (float)player.getY() - 160 });
	hitPoint3.setPosition({ (float)player.getX() - 240, (float)player.getY() - 160 });

	moneyText.setString(std::to_string(money));
	moneyText.setPosition({ (float)player.getX() - 333, (float)player.getY() - 115 });
}

void Interface::handleUI(sf::RenderWindow& window, Player player)
{

	HP.push_back(hitPoint1);
	HP.push_back(hitPoint2);
	HP.push_back(hitPoint3);

	hitPoint1.setTexture(hitpointTexture);
	hitPoint3.setTexture(hitpointTexture);
	hitPoint2.setTexture(hitpointTexture);
       
	updatePositions(player);
}