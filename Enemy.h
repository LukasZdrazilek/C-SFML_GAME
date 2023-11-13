#include <iostream>
#include <SFML/Graphics.hpp>
#pragma once

class Enemy
{

public:
	Enemy(sf::Vector2f size)
	{
		enemy.setSize(size);
		enemy.setFillColor(sf::Color::Red);
	}

	void handleEnemy();

	void addEnemy(sf::RenderWindow& window)
	{
		window.draw(enemy);
	}

	void move(sf::Vector2f distance)
	{
		enemy.move(distance);
	}

	void setPosition(sf::Vector2f newPos)
	{
		enemy.setPosition(newPos);
	}

	int getY()								// vrati souradnici vysky hrace (y) kvuli gravitaci
	{
		return enemy.getPosition().y;
	}

	int getX()
	{
		return enemy.getPosition().x;
	}

	sf::Vector2f getPosition()
	{
		return enemy.getPosition();
	}

	sf::Vector2f getSize()
	{
		return enemy.getSize();
	}

	sf::FloatRect getGlobalBounds()
	{
		sf::Vector2f position = enemy.getPosition();
		sf::Vector2f size = enemy.getSize();
		return sf::FloatRect(position, size);
	}

	float movementTimer = 0;        // Timer for the enemy movement
	float movementDuration = 2.0f;  // 2 seconds for each movement
	bool movingLeft = true;


private:

	float multiplier = 60.0f;
	sf::RectangleShape enemy;
	sf::Clock clock;

};