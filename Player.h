#include <SFML/Graphics.hpp>
#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player
{

public:

	Player()
	{

	}

	Player(sf::Vector2f size)
	{
		player.setSize(size);
	}

	void drawPlayer(sf::RenderWindow& window)
	{
		window.draw(player);
		window.draw(attackEffect);
	}

	void handlePlayer(float deltaTime, float multiplier);

	void move(sf::Vector2f distance)
	{
		player.move(distance);
	}

	void setPosition(sf::Vector2f newPos)
	{
		player.setPosition(newPos);
	}

	int getY()		// vrati souradnici vysky hrace (y) kvuli gravitaci
	{
		return player.getPosition().y;
	}

	int getX()
	{
		return player.getPosition().x;
	}

	sf::Vector2f getPosition()
	{
		return player.getPosition();
	}

	sf::Vector2f getSize()
	{
		return player.getSize();
	}

	sf::FloatRect getGlobalBounds()
	{
		sf::Vector2f position = player.getPosition();
		sf::Vector2f size = player.getSize();
		return sf::FloatRect(position, size);
	}

	void loadTextures();


	bool facingLeft = false;	//THIS
	float playerHeight = 70;	//
	float playerWidth = 60;
	bool isAttacking = false;

	float moveSpeed = 5;
	int floorHeight = 900;
	float gravitySpeed = 9;

	float jumpSpeed = 7;
	int jumpsLeft = 1;
	bool isJumping = false;

	sf::Clock jumpTimer;
	sf::Clock runTimer;
	sf::Clock attackAnimationTimer;


private:

	sf::RectangleShape player;
	sf::RectangleShape attackEffect;

	float run_animationTime = 0.3f;
	bool attackAnimation = false;

	sf::Texture playerTexture_right;
	sf::Texture playerTexture_left;
	sf::Texture playerAttack_right;
	sf::Texture playerAttack_left;
	sf::Texture playerFall_right;
	sf::Texture playerFall_left;
	sf::Texture playerJump_left;
	sf::Texture playerJump_right;
	sf::Texture playerRun1_left;
	sf::Texture playerRun1_right;
	sf::Texture playerRun2_left;
	sf::Texture playerRun2_right;
	sf::Texture playerAttackEffect_right;
	sf::Texture playerAttackEffect_left;

};

#endif
