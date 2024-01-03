#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Map.h"
#include "Interface.h"
#include "Camera.h"
#include "Menu.h"

enum class GameState 
{
    MENU,
    GAMEPLAY
};

int main() 
{
    // Okno hry a FPS limit ( zde neni nutne potreba )
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Song of the Knights of Silk");
    window.setFramerateLimit(60);

    Map map;
    Boss boss;
    Enemy enemy({1,1},{1,1},1);
    Enemies enemies;
    Player player;
    sf::View camera;
    Enemies allEnemies;
    Interface interface;
    sf::Texture hitpointTexture;

    // 'Real time' hodiny, casovac utoku, delta time + multiplier proti zavislosti hre na FPS
    sf::Clock clock;
    sf::Clock attackTimer;
    float deltaTime;
    float multiplier = 70.0f;

    // Nacitani textur
    player.loadTextures();
    boss.loadTextures();
    map.loadTextures();
    interface.loadTextures();
    //enemy.loadSound();
    allEnemies.loadTextures();

    GameState gameState = GameState::MENU;
    Menu mainMenu((float)window.getSize().x, (float)window.getSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        deltaTime = clock.restart().asSeconds();

        if (gameState == GameState::MENU) 
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                mainMenu.handleEvents(window, event);

                if (mainMenu.startGame == true)
                {
                    gameState = GameState::GAMEPLAY;
                }
                else if (mainMenu.bossRush == true)
                {
                    gameState = GameState::GAMEPLAY;
                    player.setPosition({ 700, -800 });
                }
                else if (mainMenu.exitGame == true)
                {
                    window.close();
                }
            }

            window.clear();
            mainMenu.draw(window);
            window.display();
        }
        else if (gameState == GameState::GAMEPLAY) 
        {
            if (interface.isPlayerAlive(player) == false)
            {
                interface.playerReset(player);
                enemies.resetEnemies();
            }

            handleCamera(camera, player, window);
            interface.handleUI(window, player);
            if (mainMenu.bossRush == false)
                allEnemies.handleEnemies(deltaTime, player, window, interface, player.attackHitbox);
            player.handlePlayer(deltaTime, multiplier);
            map.handleCollisions(player);
            boss.handleBoss(player, window, interface, player.attackHitbox, deltaTime, multiplier);

            while (window.pollEvent(event)) 
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

            window.clear();
            map.draw(window, player, deltaTime, multiplier);
            boss.drawBoss(window, interface, player);
            interface.draw(window);
            player.drawPlayer(window);
            allEnemies.drawEnemies(window);
            window.display();
        }
    }
    return 0;
}