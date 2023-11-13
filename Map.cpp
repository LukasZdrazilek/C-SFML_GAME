#include "Map.h"
#include "iostream"

Map::Map(float windowWidth, float windowHeight)
{

    floor.setSize(sf::Vector2f(5000, 10));
    floor.setFillColor(sf::Color::Blue);
    floor.setPosition(0, 900);

    sf::RectangleShape platform1a = setPlatform(100, 10, 800, 720, 1);
    sf::RectangleShape platform1b = setPlatform(100, 10, 800, 730, 2);

    sf::RectangleShape platform2a = setPlatform(100, 10, 1000, 620, 1); 
    sf::RectangleShape platform2b = setPlatform(100, 10, 1000, 630, 2);   

    background1.setScale(1.0f, 1.5f);


}

// Nacitani textur                      mimo kvuli memory
void Map::loadTextures()
{
    backgroundTexture1.loadFromFile("Textures/background1.png");        // textura pozadi
    background1.setTexture(backgroundTexture1);
    floorTexture1.loadFromFile("Textures/stoneFloor.png");           // textura zeme
    floor1.setTexture(floorTexture1);
    platformTexture.loadFromFile("Textures/platformTexture.png");          // textura platformy
}


void Map::drawPlatform(sf::RenderWindow& window, sf::RectangleShape& platform)
{
    window.draw(platform);
}

void Map::draw(sf::RenderWindow& window)
{
    // Draw the map elements (floor, platforms) on the window
    window.draw(floor);
    int x = -400;
    int xx = 0;

    
    // kresleni pozadi
    for (int i = 0; i < 6; i++)
    {
        background1.setPosition(x, 250);
        window.draw(background1);
        //background1.setPosition(0 + 300 * i, 610 + 297);
       // window.draw(background1);
        x += backgroundTexture1.getSize().x;
    }
    
    // kresleni zeme
    for (int i = 0; i < 30; i++)      // 30x textura za sebou
    {
        floor1.setPosition(xx, 900);
        window.draw(floor1);
        xx += floorTexture1.getSize().x;
    }

    

    for (sf::RectangleShape& platform : platformsTop)
    {
        drawPlatform(window, platform);
        platform.setTexture(&platformTexture);
    }

    for (sf::RectangleShape& platform : platformsBot)
    {
        drawPlatform(window, platform);
        platform.setTexture(&platformTexture);
    }


}