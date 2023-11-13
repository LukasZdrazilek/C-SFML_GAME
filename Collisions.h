#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Map.h"
#ifndef COLLISIONS_H
#define COLLISIONS_H

void getCollisions(Map map)
{
    sf::FloatRect platform1aBounds = map.platform1a.getGlobalBounds();//
    sf::FloatRect platform1bBounds = map.platform1b.getGlobalBounds();//
    sf::FloatRect platform2aBounds = map.platform2a.getGlobalBounds();//
    sf::FloatRect platform2bBounds = map.platform2b.getGlobalBounds();//
    sf::FloatRect floorBounds = map.floor.getGlobalBounds();//
}

void handleCollisions(Player player, Enemy enemy, Map map)
{
    sf::FloatRect platform1aBounds = map.platform1a.getGlobalBounds();//
    sf::FloatRect platform1bBounds = map.platform1b.getGlobalBounds();//
    sf::FloatRect platform2aBounds = map.platform2a.getGlobalBounds();//
    sf::FloatRect platform2bBounds = map.platform2b.getGlobalBounds();//
    sf::FloatRect floorBounds = map.floor.getGlobalBounds();//

    // Kolize zeme a hrace
    if (player.getGlobalBounds().intersects(floorBounds))//
    {
        float overcock = player.getGlobalBounds().top + player.getGlobalBounds().height - floorBounds.top;//

        if (overcock < player.playerHeight)
        {
            player.setPosition({ player.getPosition().x, floorBounds.top - player.playerHeight });
            player.jumpsLeft = 1;
        }
    }

    // Kolize platformy a hrace zvrchu      //
    if (player.getGlobalBounds().intersects(platform1aBounds)) {    // kolize platformy z vrchu ( PAK NACPAT PLATFORMY DO LISTU A TOTO DO LOOPU )
        float overlap = player.getGlobalBounds().top + player.getGlobalBounds().height - platform1aBounds.top;

        if (overlap < player.playerHeight)
        {
            player.setPosition({ player.getPosition().x, platform1aBounds.top - player.playerHeight });
            player.jumpsLeft = 1;
        }
    }

    // Kolize platformy a hrace zvrchu 2    //
    if (player.getGlobalBounds().intersects(platform2aBounds)) {    // kolize platformy z vrchu ( PAK NACPAT PLATFORMY DO LISTU A TOTO DO LOOPU )
        float overlap = player.getGlobalBounds().top + player.getGlobalBounds().height - platform2aBounds.top;

        if (overlap < player.playerHeight)
        {
            player.setPosition({ player.getPosition().x, platform2aBounds.top - player.playerHeight });
            player.jumpsLeft = 1;
        }
    }

    // Kolize platformy a hrace zespodu
    if (player.getGlobalBounds().intersects(platform1bBounds))//       
    {
        player.isJumping = false;
    }
    // Kolize platformy a hrace zespodu 2
    if (player.getGlobalBounds().intersects(platform2bBounds))//
    {
        player.isJumping = false;
    }

    // Kolize enemy a hrace
    if (player.getGlobalBounds().intersects(enemy.getGlobalBounds()))//
    {
        if (player.facingLeft == false)      // hrac narazi do enemy = HP down, pridany v mainu
            player.move({ -60, 0 });        // enemy bump
        else
            player.move({ +60, 0 });
    }
}

#endif