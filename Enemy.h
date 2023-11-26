#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Interface.h"
#pragma once
#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{

public:
	Enemy(sf::Vector2f size, sf::Vector2f position);

	void handleEnemy(Player& player, sf::RenderWindow& window, const sf::Texture& leftTexture1, const sf::Texture& rightTexture1, const sf::Texture& leftTexture2, const sf::Texture& rightTexture2);

	void drawEnemy(sf::RenderWindow& window)
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
		return (int)enemy.getPosition().y;
	}

	int getX()
	{
		return (int)enemy.getPosition().x;
	}

	sf::Vector2f getPosition()
	{
		return enemy.getPosition();
	}

	sf::Vector2f getSize()
	{
		return enemy.getSize();
	}

	int getHitPoints() 
	{
		return hitPoints;
	}

	void takeDamage(int damage) 
	{
		hitPoints -= damage;
	}

	bool isAlive() 
	{
		if (hitPoints > 0)
			return true;
		else
			return false;
	}

	bool checkPlayerCollision(Player& player);

	bool checkPlayerAttackCollision(Player& player, sf::RectangleShape attackHitbox);

	void handlePlayerCollision(Player& player, Interface& interface, sf::RenderWindow& window);

	void handlePlayerAttackCollision(Player& player, Interface& interface, sf::RenderWindow& window, sf::RectangleShape attackHitbox);

	sf::FloatRect getGlobalBounds()
	{
		sf::Vector2f position = enemy.getPosition();
		sf::Vector2f size = enemy.getSize();
		return sf::FloatRect(position, size);
	}

	// Timer pro pohyb enemy, rychlost = 2
	float movementTimer = 0;      
	float movementDuration = 2.0f;
	bool movingLeft = true;

private:

	float speed = 2.0f;     // enemy rychlost
	int hitPoints = 3;
	float multiplier = 60.0f;
	sf::RectangleShape enemy;
	sf::Clock clock;

	sf::Clock runTimer;
	float run_animationTime = 0.3f;

};

class Enemies
{

public:
	Enemies();

	void loadTextures();

	void handleEnemies(Player& player, sf::RenderWindow& window, Interface& interface, sf::RectangleShape attackHitbox);

	// pridat utok 
	// pridat enemy utok


	void drawEnemies(sf::RenderWindow& window);

private:

	sf::Texture crawlid1_right;
	sf::Texture crawlid1_left;
	sf::Texture crawlid2_right;
	sf::Texture crawlid2_left;
	std::vector<Enemy> enemies;
};

#endif
