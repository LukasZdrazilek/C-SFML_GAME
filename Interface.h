#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H
#include <SFML/Graphics.hpp>
#include "Player.h"

class Interface
{
public:
	
	void handleUI(sf::RenderWindow& window, Player player);

	void updateHPPositions(Player player);

	void update(int hitpoints);

	void drawFont(sf::RenderWindow& window);

	void draw(sf::RenderWindow& window);

	int hitPoints = 3;

	void loadTextures();

private:

	sf::Texture hitpointTexture;
	sf::Sprite hitPoint1;
	sf::Sprite hitPoint2;
	sf::Sprite hitPoint3;
	sf::Font font;
	sf::Text hitpointText;
	std::vector<sf::Sprite> HP;

};

#endif