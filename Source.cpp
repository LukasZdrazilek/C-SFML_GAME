#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
//#include "Collisions.h"   nejde zatim
#include "Interface.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Videogame");
    window.setFramerateLimit(60);   // nemusi asi

    // Window + clock promenne
    Map map(window.getSize().x, window.getSize().y);
    sf::Clock clock;
    sf::Clock attackTimer;
    float deltaTime;
    float multiplier = 70.0f;   // kvuli delta timu ( framerate independency )

    // Player
    float playerHeight = 70.0f;
    float playerWidth = 60.0f;
    Player player({ playerWidth, playerHeight });
    player.setPosition({ 100, 430 });   // fall in effect    

    // Enemy
    Enemy enemy({ playerWidth, playerHeight });
    enemy.setPosition({ 400, 829 });

    // UI promenne
    sf::Texture hitpointTexture;
    Interface interface;

    // Utok promenne
    sf::RectangleShape attackHitbox(sf::Vector2f(playerWidth, playerHeight));
    sf::Texture playerAttackEffect_right;
    sf::Texture playerAttackEffect_left;
    playerAttackEffect_right.loadFromFile("Textures/Hornet/attack_right.png");
    playerAttackEffect_left.loadFromFile("Textures/Hornet/attack_left.png");
    

    // Kamera setup
    sf::View camera(sf::Vector2f(player.getPosition().x + playerWidth / 2, player.getPosition().y + playerHeight / 2), sf::Vector2f(1280, 720));
    camera.setSize(sf::Vector2f(800, 450));
    window.setView(camera);


    //////////////////////////////////////////////////////////////////////////

    // Ziskani kolizi
    sf::FloatRect platform1aBounds = map.platform1a.getGlobalBounds();//
    sf::FloatRect platform1bBounds = map.platform1b.getGlobalBounds();//
    sf::FloatRect platform2aBounds = map.platform2a.getGlobalBounds();//
    sf::FloatRect platform2bBounds = map.platform2b.getGlobalBounds();//
    sf::FloatRect floorBounds = map.floor.getGlobalBounds();//

    // nacitani textur (muze pak byt i v .cpp souborech, nevim)
    player.loadTextures();
    map.loadTextures();
    interface.loadTextures();

    while (window.isOpen())        // main game loop kdyz je okno otevreno
    {
        sf::Event event;
        deltaTime = clock.restart().asSeconds();

        
        // Kamera sledovani
        camera.setCenter(player.getPosition().x + playerWidth / 2, player.getPosition().y + playerHeight / 2 - 20 );
        window.setView(camera);
        
        // WINDOW, PLAYER, ENEMY ??, TAK PODOBNE VYMYSLET TO COLLISIONS.H
        interface.handleUI(window, player);                /////////// bere funkce z interface.h
        enemy.handleEnemy();                              /////////// bere funkce z enemy.h
        player.handlePlayer(deltaTime, multiplier);      /////////// vezme ovladani z Player.cpp
        map.draw(window);                               /////////// bere funkce z map.cpp a kresli mapu
        interface.draw(window);                        ///////////  kresli HP z interface.h


        // Utok funkce
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !player.isAttacking)//
        {
            attackTimer.restart();
            player.isAttacking = true;
            if (player.facingLeft == false)
            {
                attackHitbox.setPosition(player.getPosition().x + (player.getGlobalBounds().width), player.getPosition().y);
                float attackTimee = attackTimer.getElapsedTime().asSeconds();
                if (attackTimee < 0.1)                                   // zabraneni spamovani utoku kdyz drzim X
                    attackHitbox.setTexture(&playerAttackEffect_right);
                else
                    player.isAttacking = false;
            }
                
            else
            {
                attackHitbox.setPosition(player.getPosition().x - (player.getGlobalBounds().width), player.getPosition().y);//
                attackHitbox.setTexture(&playerAttackEffect_left);
            }
               
        }

        // Utok na nepritele
        if (player.isAttacking)
        {
            float attackTime = attackTimer.getElapsedTime().asSeconds();
            if (attackTime < 0.1)
            {
                if (attackHitbox.getGlobalBounds().intersects(enemy.getGlobalBounds()))
                {
                    enemy.move({ 10, 0 });
                    // Handle enemy attack logic (e.g., decrease enemy health, remove from the game, or trigger a disappearing effect)
                    // tady pak zabit enemy nebo neco
                }
            }
            
        }

        // Kolize zeme a hrace
        if (player.getGlobalBounds().intersects(floorBounds))//
        {
            float overcock = player.getGlobalBounds().top + player.getGlobalBounds().height - floorBounds.top;//

            if (overcock < playerHeight)
            {
                player.setPosition({ player.getPosition().x, floorBounds.top - playerHeight });
                player.isJumping = false;
                player.jumpsLeft = 1;
            }
        }

        // Kolize platformy1 a hrace zvrchu      //
        if (player.getGlobalBounds().intersects(platform1aBounds)) {    // kolize platformy z vrchu ( PAK NACPAT TOTO DO LOOPU )
            float overlap = player.getGlobalBounds().top + player.getGlobalBounds().height - platform1aBounds.top;

            if (overlap < playerHeight) 
            {
                player.setPosition({ player.getPosition().x, platform1aBounds.top - playerHeight });
                player.jumpsLeft = 1;
            }
        }
        // Kolize platformy2 a hrace zvrchu    //
        if (player.getGlobalBounds().intersects(platform2aBounds)) {    // kolize platformy z vrchu (  TOTO DO LOOPU )
            float overlap = player.getGlobalBounds().top + player.getGlobalBounds().height - platform2aBounds.top;

            if (overlap < playerHeight)
            {
                player.setPosition({ player.getPosition().x, platform2aBounds.top - playerHeight });
                player.jumpsLeft = 1;
            }
        }

        // Kolize platformy1 a hrace zespodu                            
        if (player.getGlobalBounds().intersects(platform1bBounds))//    taky pak loop   
        {
            player.isJumping = false;
        }

        // Kolize platformy2 a hrace zespodu
        if (player.getGlobalBounds().intersects(platform2bBounds))//
        {
            player.isJumping = false;
        }

        // Kolize enemy a hrace
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds()))//
        {
            if (player.facingLeft == false)
                player.move({ -80, -20 });        // enemy bump
            else
                player.move({ +80, -20 });

            interface.hitPoints--;
            if (interface.hitPoints == 0)         // SMRT hrace
                window.close();             // prozatim SMRT = vypni hru ( funguje )
        }
        
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

        player.drawPlayer(window);
        enemy.addEnemy(window);
        if (player.isAttacking)
            window.draw(attackHitbox);
        window.display();

    }

    return 0;
}