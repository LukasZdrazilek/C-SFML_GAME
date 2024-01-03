#include "Interface.h"

// Load textur a textu + fontu
void Interface::loadTextures()
{
	hitpointTexture.loadFromFile("Textures/HP.png");
	font.loadFromFile("font.ttf");

	healthBarText.setFont(font);
	healthBarText.setCharacterSize(16);
	healthBarText.setLetterSpacing(-1);
	healthBarText.setFillColor(sf::Color::White);

	bossHealthBarText.setFont(font);
	bossHealthBarText.setCharacterSize(16);
	bossHealthBarText.setLetterSpacing(-1);
	bossHealthBarText.setFillColor(sf::Color::White);

	tutorialAttackText.setFont(font);
	tutorialAttackText.setCharacterSize(12);
	tutorialAttackText.setFillColor(sf::Color::White);
	tutorialAttackText.setString("Press X to attack");

	tutorialHealingText.setFont(font);
	tutorialHealingText.setCharacterSize(12);
	tutorialHealingText.setFillColor(sf::Color::White);
	tutorialHealingText.setString("Hold C to heal 1 HP if bar is half \n 2 HP if the bar is full");

	tutorialShiftjumpText.setFont(font);
	tutorialShiftjumpText.setCharacterSize(12);
	tutorialShiftjumpText.setFillColor(sf::Color::White);
	tutorialShiftjumpText.setString("Hold shift while jumping \n to jump extra distance");

	healthBackground.setFillColor(sf::Color::Black);
	healthBackground.setSize({ 134, 13 });

	bossHealthBackground.setFillColor(sf::Color::Black);
	bossHealthBackground.setSize({ 400, 15 });

	bossNameText.setFont(font);
	bossNameText.setCharacterSize(16);
	bossNameText.setFillColor(sf::Color::White);
	bossNameText.setString("Perjurer Knight");

	endingText.setFont(font);
	endingText.setCharacterSize(64);
	endingText.setFillColor(sf::Color::Yellow);
	endingText.setString("			 THE END \n Thank You for playing \n     press ESC to quit");
}

void Interface::draw(sf::RenderWindow& window)
{
	window.draw(healthBackground);
	window.draw(healthBarText);

	if (enteredBossfight == true && bossHitPoints > 0)
	{
		window.draw(bossHealthBackground);
		window.draw(bossHealthBarText);
		window.draw(bossNameText);
	}


	// Tutorial utoku, zde nejakym zpusobem zatezuje mene pameti nez v samotne funkci
	if (learnedAttacking == false)
	{
		tutorialAttackText.setPosition({ 700, 800 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		learnedAttacking = true;
	if (learnedAttacking == false)
		window.draw(tutorialAttackText);

	// Tutorial leceni
	if (learnedHealing == false)
	{
		tutorialHealingText.setPosition({ 1300, 800 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		learnedHealing = true;
	if (learnedHealing == false)
		window.draw(tutorialHealingText);

	// Tutorial shift jump
	if (learnedShifting == false)
	{
		tutorialShiftjumpText.setPosition({ 200, 100 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		learnedShifting = true;
	if (learnedShifting == false)
		window.draw(tutorialShiftjumpText);

	// Vykresleni textur HP
	if (hitPoints == 3)
	{
		window.draw(hitPoint1);
		window.draw(hitPoint2);
		window.draw(hitPoint3);
	}
	else if (hitPoints == 2)
	{
		window.draw(hitPoint1);
		window.draw(hitPoint2);
	}
	else
		window.draw(hitPoint1);

	if (bossHitPoints <= 0)
	{
		window.draw(endingText);
	}
}

// Abilita leceni
void Interface::healing(Player& player) 
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) 
	{
        if (!cKeyPressed) 
		{
            healingTimer.restart();
            cKeyPressed = true;
        }

		// Leceni po 2 sekundach drzeni 'C'
        if (healingTimer.getElapsedTime() >= holdDuration) 
		{
            if (hitPoints < 3 && healingPoints >= 50 && !player.isJumping && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
            {
            hitPoints += 1;
			healingPoints -= 50;
			}
        }
    } 
	else 
		cKeyPressed = false;
    
}

// Real time update interface dle pozice hrace
void Interface::updatePositions(Player& player)
{
	// Logika vykreslovani baru na leceni
	std::string health;
	for (int i = 0; i < healingPoints; i++)
	{
		health.append("|");
	}
	healthBarText.setString(health);

	// Logika vykreslovani HP bosse
	std::string bossHealth;
	for (int j = 0; j < bossHitPoints; j++)
	{
		bossHealth.append("|");
	}
	bossHealthBarText.setString(bossHealth);

	// Korekce pozice interfacu po zmene kamery v boss arene
	if (player.enterBossfight == true)
	{
		enteredBossfight = true;
		hitPoint1.setPosition({ (float)player.getX() - 390, -850 });
		hitPoint2.setPosition({ (float)player.getX() - 340, -850 });
		hitPoint3.setPosition({ (float)player.getX() - 290, -850 });

		healthBarText.setPosition({ (float)player.getX() - 388, -800 });
		healthBackground.setPosition((float)player.getX() - 387, (float)player.getY() - 805);

		bossHealthBarText.setPosition({ (float)player.getX() - 170, -465 });
		bossHealthBackground.setPosition({ (float)player.getX() - 170, -462 });
		bossNameText.setPosition({ (float)player.getX() - 170, -480 });
	}
	// Neni v boss arene = klasicke pozice
	else
	{
		hitPoint1.setPosition({ (float)player.getX() - 340, (float)player.getY() - 160 });
		hitPoint2.setPosition({ (float)player.getX() - 290, (float)player.getY() - 160 });
		hitPoint3.setPosition({ (float)player.getX() - 240, (float)player.getY() - 160 });

		healthBarText.setPosition({ (float)player.getX() - 338, (float)player.getY() - 115 });

		healthBackground.setPosition((float)player.getX() - 337, (float)player.getY() - 110);
	}

	if (bossHitPoints <= 0)
	{
		endingText.setPosition({ 1150, -900 });
	}
}

bool Interface::isPlayerAlive(Player& player)
{
	if (hitPoints == 0)
		return false;
	else
		return true;
}

void Interface::handleUI(sf::RenderWindow& window, Player& player)
{
	// Push textur HP do vektoru
	HP.push_back(hitPoint1);
	HP.push_back(hitPoint2);
	HP.push_back(hitPoint3);

	// Nastaveni textur HP
	hitPoint1.setTexture(hitpointTexture);
	hitPoint3.setTexture(hitpointTexture);
	hitPoint2.setTexture(hitpointTexture);
       
	updatePositions(player);
	healing(player);
}

void Interface::playerReset(Player& player)
{
	hitPoints = 3;
	healingPoints = 20;
	player.setPosition({ 100, 400 });
}