#include "Enemy.h"

void Enemy::handleEnemy()
{
    float deltaTime = clock.restart().asSeconds();
    movementTimer += deltaTime;
    

    if (movementTimer >= movementDuration) 
    {
        // Change direction
        movingLeft = !movingLeft;
        movementTimer = 0;
    }

    // Move the enemy
    float speed = 2.0f; // Adjust the speed as needed
    if (movingLeft) 
    {
        enemy.move({ -speed * deltaTime * multiplier, 0 });
    }
    else 
    {
        enemy.move({ speed * deltaTime * multiplier, 0 });
    }

  
}