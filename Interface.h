#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H


class Interface
{
public:

	void handleUI(sf::RenderWindow& window, Player player);

	void updatePositions(Player player);

	void loadFont();

	void draw(sf::RenderWindow& window);

	int hitPoints = 3;

	int money = 0;

	void loadTextures();

private:

	
	sf::Texture hitpointTexture;
	sf::Sprite hitPoint1;
	sf::Sprite hitPoint2;
	sf::Sprite hitPoint3;
	sf::Font font;
	sf::Text moneyText;
	std::vector<sf::Sprite> HP;

};

#endif
