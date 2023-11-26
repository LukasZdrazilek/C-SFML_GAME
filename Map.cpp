#include "Map.h"

// Nacitani textur                      mimo kvuli memory
void Map::loadTextures()
{
    backgroundTexture1.loadFromFile("Textures/background1.png");        // textura pozadi1
    background1.setTexture(backgroundTexture1);
    backgroundTexture2.loadFromFile("Textures/background2.png");       // textura pozadi2
    background2.setTexture(backgroundTexture2);
    floorTexture1.loadFromFile("Textures/stoneFloor.png");           // textura zeme
    floorTexture2.loadFromFile("Textures/stoneFloorSmall.png");
    stoneFloor1.setTexture(floorTexture1);
    stoneFloor2.setTexture(floorTexture2);
    platformTexture.loadFromFile("Textures/platformTexture.png");          // textura platformy
}

Map::Map()
{
    // Zde vytvaret logicke zeme - funguje
    sf::RectangleShape floor1 = setFloor(floor1X, 10, 0, floor1Height);
    sf::RectangleShape floor2 = setFloor(floor2X, 10, 0, floor2Height);
    sf::RectangleShape floor3 = setFloor(floor3X, 10, 0, floor3Height);


    // Zde vytvaret platformy - funguje
    sf::RectangleShape platform1 = setPlatform(100, 10, 1400, 720);
    sf::RectangleShape platform2 = setPlatform(100, 10, 1500, 550); 
    sf::RectangleShape platform3 = setPlatform(100, 10, 1500, 370);
    sf::RectangleShape platform4 = setPlatform(100, 50, 1200, 100);
    //sf::RectangleShape platform4 = setPlatform(100, 10, 1000, 420);

    background1.setScale(1.0f, 1.5f);
}

// Setup logicke zeme ( ne textury )
sf::RectangleShape Map::setFloor(float width, float height, float x, float y)
{
    sf::RectangleShape floor(sf::Vector2f(width, height));
    floor.setPosition(x, y);
    floors.push_back(floor);

    return floor;
}

// Setup platformy vrchni + spodni a push_back do vektoru vrchnich nebo spodnich platforem
sf::RectangleShape Map::setPlatform(float width, float height, float x, float y)
{
    sf::RectangleShape platformA(sf::Vector2f(width, height));
    platformA.setPosition(x, y);
    sf::RectangleShape platformB(sf::Vector2f(width, height));
    platformB.setPosition(x, y + 10);

    platformsTop.push_back(platformA);
    platformsBot.push_back(platformB);

    return platformA;
}

void Map::handleCollisions(Player& player)
{
    // Kolize zeme a hrace
    for (sf::RectangleShape floor : floors)
    {
        if (player.getGlobalBounds().intersects(floor.getGlobalBounds()))
        {
            float overlap = player.getGlobalBounds().top + player.getGlobalBounds().height - floor.getGlobalBounds().top;//
            if (overlap < player.playerHeight)
            {
                player.setPosition({ player.getPosition().x, floor.getGlobalBounds().top - player.playerHeight });
                player.isJumping = false;
                player.jumpsLeft = 1;
            }
            player.floorHeight = floor.getGlobalBounds().top; //
        }
        // Zmena pozice logicke zeme z pohledu hrace, kvuli gravitaci
        else
        {
            player.floorHeight = floor1Height;

            if (player.getY() <= floor2Height && player.getX() <= floor2X)
                player.floorHeight = floor2Height;

            else if (player.getY() <= floor3Height)
                player.floorHeight = floor3Height;
        }
            
    }
    
    // Kolize platformy a hrace zvrchu
    for (sf::RectangleShape& platform : platformsTop)
    {
        if (player.getGlobalBounds().intersects(platform.getGlobalBounds()))
        {
            player.floorHeight = platform.getGlobalBounds().top;
            float overlap = player.getGlobalBounds().top + player.getGlobalBounds().height - platform.getGlobalBounds().top;

            if (overlap < player.playerHeight)
            {
                player.setPosition({ player.getPosition().x, platform.getGlobalBounds().top - player.playerHeight + 1 });
                player.isJumping = false;
                player.jumpsLeft = 1;
            }
        }
    }

    // Kolize platformy a hrace zespodu
    for (sf::RectangleShape& platform : platformsBot)
    {
        if (player.getGlobalBounds().intersects(platform.getGlobalBounds()))   
        {
            player.isJumping = false;
        }
    }
}

// Kresleni platformy
void Map::drawPlatform(sf::RenderWindow& window, sf::RectangleShape& platform)
{
    window.draw(platform);
}

// Kresleni mapy
void Map::draw(sf::RenderWindow& window)
{
    float x = -400;
    float xx = 0;
    float xxx = 0;

    // Kresleni pozadi
    for (int i = 0; i < 3; i++)       // 1800 wide
    {
        background1.setPosition(x, 250);
        background2.setPosition(x, -350);

        window.draw(background1);
        window.draw(background2);

        x += backgroundTexture1.getSize().x;
    }
    
    
    // Kresleni textur zeme
    for (int i = 0; i < 20; i++)      //  2000 wide
    {
        stoneFloor1.setPosition(xx, 900);
        window.draw(stoneFloor1);
        xx += floorTexture1.getSize().x;
    }
    for (int j = 0; j < 14; j++)    //  1400 wide
    {
        stoneFloor1.setPosition(xxx, 200);
        window.draw(stoneFloor1);
        xxx += floorTexture1.getSize().x;
    }

    
    // Vektor na vrchni cast platformy
    for (sf::RectangleShape& platform : platformsTop)
    {
        drawPlatform(window, platform);
        platform.setTexture(&platformTexture);
    }

    // Vektor na spodni cast platformy
    for (sf::RectangleShape& platform : platformsBot)
    {
        drawPlatform(window, platform);
        platform.setTexture(&platformTexture);
    }


}