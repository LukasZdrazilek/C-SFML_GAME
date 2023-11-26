#include "Player.h"

// Nacitani textur hrace
void Player::loadTextures()
{
    playerTexture_right.loadFromFile("Textures/Hornet/Hornet_right.png");
    playerTexture_left.loadFromFile("Textures/Hornet/Hornet_left.png");
    playerAttack_right.loadFromFile("Textures/Hornet/Hornet_attack1_right.png");
    playerAttack_left.loadFromFile("Textures/Hornet/Hornet_attack1_left.png");
    playerFall_right.loadFromFile("Textures/Hornet/Hornet_fall_right.png");
    playerFall_left.loadFromFile("Textures/Hornet/Hornet_fall_left.png");
    playerJump_right.loadFromFile("Textures/Hornet/Hornet_jump_right.png");
    playerJump_left.loadFromFile("Textures/Hornet/Hornet_jump_left.png");
    playerRun1_right.loadFromFile("Textures/Hornet/Hornet_run1_right.png");
    playerRun1_left.loadFromFile("Textures/Hornet/Hornet_run1_left.png");
    playerAttackEffect_right.loadFromFile("Textures/Hornet/Attack_right.png");
    playerAttackEffect_left.loadFromFile("Textures/Hornet/Attack_left.png");
    playerRun2_right.loadFromFile("Textures/Hornet/Hornet_run2_right.png");
    playerRun2_left.loadFromFile("Textures/Hornet/Hornet_run2_left.png");  
}

sf::Clock attackCooldown;
sf::Clock attackAnimationTime;

void Player::handlePlayer(float deltaTime, float multiplier) 
{

    if (facingLeft == false)
        player.setTexture(&playerTexture_right);
    else
        player.setTexture(&playerTexture_left);
       

    // Utok funkce
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !isAttacking && attackCooldown.getElapsedTime().asMilliseconds() > 600) 
    {
        isAttacking = true;
        attackCooldown.restart();
        attackAnimationTime.restart();

        if (!facingLeft) 
            attackHitbox.setPosition(player.getPosition().x + (player.getGlobalBounds().width), player.getPosition().y);

        else 
            attackHitbox.setPosition(player.getPosition().x - (player.getGlobalBounds().width), player.getPosition().y);
    }
    
    // Zakaz spamu utoku
    if (isAttacking && attackCooldown.getElapsedTime().asMilliseconds() > 200) 
        isAttacking = false;


    // Aktivace textur utoku
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)  && attackAnimationTime.getElapsedTime().asMilliseconds() < 200)
    {
        if (facingLeft == false )
        {
            attackHitbox.setTexture(&playerAttackEffect_right);
            player.setTexture(&playerAttack_right);
        }
        else
        {
            attackHitbox.setTexture(&playerAttackEffect_left);
            player.setTexture(&playerAttack_left);
        }      
    }

    // Pohyb vlevo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
    {
        move({ -moveSpeed * deltaTime * multiplier, 0 });
        facingLeft = true;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && attackAnimationTime.getElapsedTime().asMilliseconds() < 200)
        {

            if (facingLeft == false) 
                player.setTexture(&playerAttack_right);
            else
                player.setTexture(&playerAttack_left);
        }
        else
        {   // animace behani vlevo
            player.setTexture(&playerRun1_left);
            if (runTimer.getElapsedTime().asSeconds() > run_animationTime)
            {
                if (player.getTexture() == &playerRun1_left)
                    player.setTexture(&playerRun2_left);
                else
                    player.setTexture(&playerRun1_left);

                if (runTimer.getElapsedTime().asSeconds() > run_animationTime * 2)
                    runTimer.restart();
            }
        } 
    }

    // Pohyb vpravo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
    {
        move({ +moveSpeed * deltaTime * multiplier, 0 });
        facingLeft = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && attackAnimationTime.getElapsedTime().asMilliseconds() < 200)
        {
            if (facingLeft == false)
                player.setTexture(&playerAttack_right);
            else
                player.setTexture(&playerAttack_left);
        }
        else
        {   // animace behani vpravo
            player.setTexture(&playerRun1_right);
            if (runTimer.getElapsedTime().asSeconds() > run_animationTime)
            {
                if (player.getTexture() == &playerRun1_right)
                    player.setTexture(&playerRun2_right);
                else
                    player.setTexture(&playerRun1_right);

                if (runTimer.getElapsedTime().asSeconds() > run_animationTime * 2)
                    runTimer.restart();
            }
        }        
    }

    // Gravitace
    if (getY() + playerHeight < floorHeight && isJumping == false)      // pokud je hrac vys nez zeme + nedrzi mezernik
    {
        player.move({ 0, gravitySpeed * deltaTime * multiplier });

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            if (facingLeft == false)
                player.setTexture(&playerAttack_right);
            else
                player.setTexture(&playerAttack_left);
        }
        else
        {
            if (facingLeft == false)
                player.setTexture(&playerFall_right);
            else
                player.setTexture(&playerFall_left);
        }
    }

    // funkce pro "zapnuti" skoku
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jumpsLeft > 0)
    {
        if (isJumping == false)   
        {
            isJumping = true;
            jumpTimer.restart();
            jumpsLeft = 0; 
        }
    }

    // funkce na skok
    if (isJumping)
    {
        float jumpTime = jumpTimer.getElapsedTime().asSeconds();
        if (jumpTime < 0.4)        // max vyska skoku
        {
            player.move({ 0, -jumpSpeed * deltaTime * multiplier });
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                if (facingLeft == false)
                    player.setTexture(&playerAttack_right);
                else
                    player.setTexture(&playerAttack_left);
            }
            else
            {
                if (facingLeft == false)
                    player.setTexture(&playerJump_right);   //
                else
                    player.setTexture(&playerJump_left);    //
            }
        }
        else
        {
            isJumping = false;
        }      
        
    }

    // Bounds mapy zleva
    if (getX() <= 0)
        setPosition({ 0, (float)getY() });

    // Bounds mapy zprava
    if (getX() >= (2000 - playerWidth))
        setPosition({ 2000 - (playerWidth), (float)getY()});


}
