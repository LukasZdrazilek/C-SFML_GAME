#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#pragma once
#ifndef MAP_H
#define MAP_H

class Map 
{
public:
    Map();

    void draw(sf::RenderWindow& window);

    void drawPlatform(sf::RenderWindow& window, sf::RectangleShape& platform);
    
    sf::RectangleShape setPlatform(float width, float height, float x, float y);

    sf::RectangleShape setFloor(float width, float height, float x, float y);

    void loadTextures();

    void handleCollisions(Player& player);

    

private:

    bool move_right = false;
    int floor1X = 2000;
    int floor2X = 1400;
    int floor3X = 1400;

    int floor1Height = 900;
    int floor2Height = 200;
    int floor3Height = -500;

    sf::Texture floorTexture1;
    sf::Texture floorTexture2;    
    sf::Sprite stoneFloor1;
    sf::Sprite stoneFloor2;

    sf::Texture backgroundTexture1;
    sf::Sprite background1;
    sf::Texture backgroundTexture2;
    sf::Sprite background2;
    sf::Texture platformTexture;

    std::vector<sf::RectangleShape> floors;
    std::vector<sf::RectangleShape> platformsTop;
    std::vector<sf::RectangleShape> platformsBot;

};

#endif