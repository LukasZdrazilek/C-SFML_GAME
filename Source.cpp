#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Interface.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Videogame");
    window.setFramerateLimit(60);   // nemusi asi

    Map map;
    Player player;
    Enemies allEnemies;
    Interface interface;

    // Clock promenne
    sf::Clock clock;
    sf::Clock attackTimer;      // pak vymazat aimplementovat do Player.cpp
    float deltaTime;
    float multiplier = 70.0f;   // kvuli delta timu ( framerate independency )

    // UI promenne
    sf::Texture hitpointTexture;
    

    // Kamera setup
    sf::View camera(sf::Vector2f(player.getPosition().x + player.playerWidth / 2, player.getPosition().y + player.playerHeight / 2), sf::Vector2f(1280, 720));
    camera.setSize(sf::Vector2f(800, 450));
    window.setView(camera);


    // Nacitani textur
    player.loadTextures();
    map.loadTextures();
    interface.loadTextures();
    allEnemies.loadTextures();

    
    // Main game loop ( hra je otevrena )
    while (window.isOpen())
    {
        sf::Event event;
        deltaTime = clock.restart().asSeconds();

        // Kamera sledovani
        camera.setCenter(player.getPosition().x + player.playerWidth / 2, player.getPosition().y + player.playerHeight / 2 - 20 );
        window.setView(camera);
        
        
        // Aktivace .h a .cpp souboru
        interface.handleUI(window, player);
        allEnemies.handleEnemies(player, window, interface, player.attackHitbox);
        player.handlePlayer(deltaTime, multiplier);
        map.handleCollisions(player);

        //std::cout << "deltaTime: " << deltaTime << "\n";


        while (window.pollEvent(event))         // sem psat eventy  ->  sf::Event:: ... edit  radsi ne kvuli pameti
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();

            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Space)
                    player.isJumping = false;

                if (event.key.code == sf::Keyboard::X)
                    player.isAttacking = false;
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        // Kresleni prvku hry
        map.draw(window);
        interface.draw(window);
        player.drawPlayer(window);
        allEnemies.drawEnemies(window);

        window.display();

    }

    return 0;
}