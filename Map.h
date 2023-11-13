#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#ifndef MAP_H
#define MAP_H

class Map 
{
public:
    Map(float windowWidth, float windowHeight);

    void draw(sf::RenderWindow& window);

    void drawPlatform(sf::RenderWindow& window, sf::RectangleShape& platform);
    
    // funkce na platformy
    sf::RectangleShape setPlatform(int width, int height, int x, int y, int position)
    {                                                                
        sf::RectangleShape platform(sf::Vector2f(width, height));
        platform.setPosition(x, y);
        if (position == 1)
            platformsTop.push_back(platform);      // top platformy do vektoru
        else
            platformsBot.push_back(platform);      // bottom

        return platform;
    } 

    void loadTextures();

    sf::RectangleShape platform1a = setPlatform(100, 10, 800, 720, 1);        // PAK SMAZAT
    sf::RectangleShape platform1b = setPlatform(100, 10, 800, 730, 2);        // PAK SMAZAT, BUDE JEN V .CPP ASI

    sf::RectangleShape platform2a = setPlatform(100, 10, 1000, 620, 1);        // PAK SMAZAT
    sf::RectangleShape platform2b = setPlatform(100, 10, 1000, 630, 2);        // PAK SMAZAT, BUDE JEN V .CPP ASI

    sf::RectangleShape floor;                                                  // SVIJANSKÝ SMÁZ PAK

private:

    sf::Texture floorTexture1;
    sf::Sprite floor1;
    sf::Texture backgroundTexture1;
    sf::Sprite background1;
    sf::Texture platformTexture;

    std::vector<sf::RectangleShape> platformsTop;
    std::vector<sf::RectangleShape> platformsBot;

};

#endif