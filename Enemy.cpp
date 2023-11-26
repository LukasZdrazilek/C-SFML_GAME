#include "Enemy.h"

void Enemies::loadTextures()
{
    // enemy textury
    crawlid1_right.loadFromFile("Textures/Crawlid/Crawlid1_right.png");
    crawlid1_left.loadFromFile("Textures/Crawlid/Crawlid1_left.png");
    crawlid2_right.loadFromFile("Textures/Crawlid/Crawlid2_right.png");
    crawlid2_left.loadFromFile("Textures/Crawlid/Crawlid2_left.png");
}

Enemy::Enemy(sf::Vector2f size, sf::Vector2f position)
{
    enemy.setSize(size);
    enemy.setPosition(position);
    //enemy.setTexture(path);
}

void Enemy::handleEnemy(Player& player, sf::RenderWindow& window, const sf::Texture& leftTexture1, const sf::Texture& rightTexture1, const sf::Texture& leftTexture2, const sf::Texture& rightTexture2)
{
    if (isAlive() == true)
    {
        float deltaTime = clock.restart().asSeconds();
        movementTimer += deltaTime;


        if (movementTimer >= movementDuration)
        {
            // Change direction
            movingLeft = !movingLeft;
            movementTimer = 0;
        }

        // Pohyb enemy
        if (movingLeft)
        {
            move({ -speed * deltaTime * multiplier, 0 });
            enemy.setTexture(&leftTexture1);
            if (runTimer.getElapsedTime().asSeconds() > run_animationTime)
            {
                if (enemy.getTexture() == &leftTexture1)
                    enemy.setTexture(&leftTexture2);
                else
                    enemy.setTexture(&leftTexture1);

                if (runTimer.getElapsedTime().asSeconds() > run_animationTime * 2)
                    runTimer.restart();
            }
        }
        else
        {
            move({ speed * deltaTime * multiplier, 0 });
            enemy.setTexture(&rightTexture1);
            enemy.setTexture(&rightTexture1);
            if (runTimer.getElapsedTime().asSeconds() > run_animationTime)
            {
                if (enemy.getTexture() == &rightTexture1)
                    enemy.setTexture(&rightTexture2);
                else
                    enemy.setTexture(&rightTexture1);

                if (runTimer.getElapsedTime().asSeconds() > run_animationTime * 2)
                    runTimer.restart();
            }
        }

        // Enemy detekce hrace
        if (player.getX() >= getX() - 300 && player.getX() <= getX() && player.getY() <= getY())  // detekce hrace vlevo ( hrac je blize jak 300 pixelu )
        {
            movingLeft = true;
        }
        else if (player.getX() <= getX() + 300 && player.getX() >= getX() && player.getY() <= getY())  // vpravo 300 pixelu
        {
            movingLeft = false;
        }      
    }
}

// Check kolize hrace a enemy
bool Enemy::checkPlayerCollision(Player& player)
{
    return getGlobalBounds().intersects(player.getGlobalBounds());
}

// Check utoku hrace a enemy
bool Enemy::checkPlayerAttackCollision(Player& player, sf::RectangleShape attackHitbox)
{
    return getGlobalBounds().intersects(attackHitbox.getGlobalBounds());
}

// Logika utoku na hrace
void Enemy::handlePlayerCollision(Player& player, Interface& interface, sf::RenderWindow& window)
{
    if (checkPlayerCollision(player) && isAlive() == true)   // && player.isAlive() mozna
    {
        interface.hitPoints--;
        if (interface.hitPoints == 0)         // SMRT hrace
            window.close();             // prozatim SMRT = vypni hru ( funguje )

        if (player.facingLeft == false)
            player.move({ -80, -20 });        // enemy bump
        else
            player.move({ +80, -20 });
    }
}

// Logika utoku na enemy
void Enemy::handlePlayerAttackCollision(Player& player, Interface& interface, sf::RenderWindow& window, sf::RectangleShape attackHitbox)
{
    if (player.isAttacking)
    {
        if (checkPlayerAttackCollision(player, attackHitbox) && isAlive() == true)
        {
            if (player.facingLeft == false)
                enemy.move({ 60, 0 });
            else
                enemy.move({ -60, 0 });
            takeDamage(1);
            interface.money += 100;
        }
    }
}

// Zde vytvaret enemy - funguje
Enemies::Enemies()
{
    enemies.push_back(Enemy({ 70, 40 }, { 1200, 860 }));
    enemies.push_back(Enemy({ 70, 40 }, { 1000, 160 }));
    //enemies.push_back(Enemy({ 60, 70 }, { 1400, 830 }));
}

void Enemies::handleEnemies(Player& player, sf::RenderWindow& window, Interface& interface, sf::RectangleShape attackHitbox)
{
    for (auto& enemy : enemies)
    {
        enemy.handleEnemy(player, window, crawlid1_left, crawlid1_right, crawlid2_left, crawlid2_right);
        enemy.handlePlayerCollision(player, interface, window);
        enemy.handlePlayerAttackCollision(player, interface, window, attackHitbox);
    }
}

void Enemies::drawEnemies(sf::RenderWindow& window)
{
    for (auto& enemy : enemies)
    {
        if (enemy.isAlive() == true)
            enemy.drawEnemy(window);
    }
}
