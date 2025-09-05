#include "JohnnyGun.h"
#include <stdio.h>
#include <stdlib.h>

// =============================================================================
// CONSTRUCTOR AND INITIALIZATION
// =============================================================================
JohnnyGunGame::JohnnyGunGame(GameSystem *gameSystem, GameState *gameState, UIComponents *uiComponents)
	: system(gameSystem), state(gameState), ui(uiComponents)
{
	initialize();
}

void JohnnyGunGame::initialize()
{
	initializeGameState();
}

void JohnnyGunGame::initializeGameState()
{
	// Player initialization
	gameState.johnnyX = JOHNNY_START_X;
	gameState.johnnyY = JOHNNY_START_Y;

	// Bullet initialization
	gameState.bullet.active = false;
	gameState.bullet.x = 0;
	gameState.bullet.y = 0;
	gameState.bullet.velocity = BULLET_VELOCITY;

	// Enemy initialization
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		gameState.enemies[i].active = false;
		gameState.enemies[i].x = 0;
		gameState.enemies[i].y = 0;
		gameState.enemies[i].timer = 0;
	}

	gameState.enemyCount = 0;
	gameState.spawnTimer = 500;
	gameState.randomSpawn = 0;

	// Game state initialization
	gameState.jgScore = 0;
	gameState.jgHighScore = 0;
	gameState.jgScoreCount = 0;
	gameState.johnnyGameTimer = 0;

	// Environment initialization
	gameState.skyBackground = TFT_RED;
	gameState.groundColor = TFT_DARKGREEN;
	gameState.platformColor = TFT_DARKGREEN;
	gameState.lightsOut = false;
	gameState.bloodMoon = false;
}

void JohnnyGunGame::resetGameState()
{
	gameState.johnnyX = JOHNNY_START_X;
	gameState.johnnyY = JOHNNY_START_Y;
	gameState.jgScore = 0;
	gameState.johnnyGameTimer = 0;
	gameState.spawnTimer = 500;
	gameState.bullet.active = false;
	gameState.lightsOut = false;
	gameState.bloodMoon = false;
	gameState.skyBackground = TFT_RED;
	resetEnemies();
}

// =============================================================================
// MAIN GAME SCREENS
// =============================================================================
void JohnnyGunGame::showMenu()
{
	if (state->needsInitialization())
	{
		gameState.bloodMoon = false;
		gameState.lightsOut = false;
		state->resetMenuSelection();

		ui->drawMenuBackground(TFT_BLACK);

		// High score display
		ui->drawHighScore(gameState.jgHighScore, 100, 30, TFT_RED);

		// Game title
		system->setTextProperties(TFT_BLACK, 5);
		system->fillRect(90, 60, 300, 75, TFT_RED);
		system->drawRect(90, 60, 300, 75, TFT_MAROON);
		system->drawString("JOHNNY GUN", 90, 80);

		// Menu options
		system->setTextProperties(TFT_WHITE, 3);
		system->drawString("PLAY", 205, 160);
		system->drawString("HOW TO PLAY", 145, 200);
		system->drawString("EXIT", 205, 240);

		state->markAsInitialized();
	}

	handleMenuNavigation();

	// Draw menu cursors
	const int menuY[] = {170, 210, 250};
	const int menuX[] = {180, 115, 180};

	// Clear all cursors
	for (int i = 0; i < 3; i++)
	{
		ui->clearMenuCursor(menuX[i], menuY[i], TFT_BLACK);
	}

	// Draw current selection cursor
	int currentSelection = state->getCurrentMenuSelection();
	if (currentSelection >= 0 && currentSelection < 3)
	{
		ui->drawMenuCursor(menuX[currentSelection], menuY[currentSelection], TFT_RED);
	}

	// Handle selection
	if (system->isButton1JustPressed())
	{
		switch (currentSelection)
		{
		case 0: // PLAY
			state->transitionToScreen(JOHNNY_GUN_GAME);
			break;
		case 1: // HOW TO PLAY
			state->transitionToScreen(HOW_TO_PLAY_JG);
			break;
		case 2: // EXIT
			state->transitionToScreen(MAIN_MENU);
			break;
		}
	}

	system->delay(MENU_NAVIGATION_DELAY);
}

void JohnnyGunGame::showGame()
{
	if (state->needsInitialization())
	{
		gameState.johnnyX = JOHNNY_START_X;
		gameState.johnnyY = JOHNNY_START_Y;

		if (!gameState.lightsOut)
		{
			gameState.jgScore = 0;
		}

		gameState.johnnyGameTimer = 0;
		gameState.spawnTimer = 500;
		gameState.bullet.active = false;
		gameState.enemyCount = -1;

		// Initialize enemy timers
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			gameState.enemies[i].timer = rand() % (gameState.spawnTimer + 1);
		}

		system->clearScreen(gameState.skyBackground);
		createJohnny();
		drawScoreDisplay();

		state->markAsInitialized();
	}

	updateGame();
}

void JohnnyGunGame::showHowToPlay()
{
	if (state->needsInitialization())
	{
		ui->drawMenuBackground(TFT_BLACK);

		system->setTextProperties(TFT_WHITE, 5);
		system->drawString("HOW TO PLAY", 75, 60);

		system->setTextProperties(TFT_WHITE, 2);
		system->drawString("Oh no! Johnny is TRAPPED in the woods..", 0, 120);
		system->drawString("DODGE the HEX or SHOOT them to survive", 0, 150);
		system->drawString("and gain points!", 0, 180);

		ui->drawBackToMenuPrompt();

		state->markAsInitialized();
	}

	if (system->isButton1JustPressed())
	{
		state->transitionToScreen(JOHNNY_GUN_MENU);
	}
}

// =============================================================================
// GAME MECHANICS
// =============================================================================
void JohnnyGunGame::updateGame()
{
	checkEnvironmentChanges();
	updateGameTimer();
	handlePlayerInput();
	handlePlayerMovement();
	handleShooting();
	updateEnemies();
	updateBullet();
	checkCollisions();
	updateScore();
}

void JohnnyGunGame::handlePlayerInput()
{
	const InputState &input = system->getInput();

	// Shooting
	if (system->isButton1JustPressed() && !gameState.bullet.active)
	{
		system->playShootSound();
		gameState.bullet.x = gameState.johnnyX + JOHNNY_WIDTH;
		gameState.bullet.y = gameState.johnnyY + 10;
		gameState.bullet.active = true;
	}
}

void JohnnyGunGame::handlePlayerMovement()
{
	const InputState &input = system->getInput();

	// Multi-directional movement
	if (input.isUp() && input.isRight() && isJohnnyInBounds(gameState.johnnyX + 10, gameState.johnnyY - 10))
	{
		clearJohnnyShadow();
		gameState.johnnyY -= 10;
		gameState.johnnyX += 10;
		createJohnny();
	}
	else if (input.isUp() && input.isLeft() && isJohnnyInBounds(gameState.johnnyX - 10, gameState.johnnyY - 10))
	{
		clearJohnnyShadow();
		gameState.johnnyY -= 10;
		gameState.johnnyX -= 10;
		createJohnny();
	}
	else if (input.isDown() && input.isRight() && isJohnnyInBounds(gameState.johnnyX + 10, gameState.johnnyY + 10))
	{
		clearJohnnyShadow();
		gameState.johnnyY += 10;
		gameState.johnnyX += 10;
		createJohnny();
	}
	else if (input.isDown() && input.isLeft() && isJohnnyInBounds(gameState.johnnyX - 10, gameState.johnnyY + 10))
	{
		clearJohnnyShadow();
		gameState.johnnyY += 10;
		gameState.johnnyX -= 10;
		createJohnny();
	}
	// Single directional movement
	else if (input.isLeft() && isJohnnyInBounds(gameState.johnnyX - 10, gameState.johnnyY))
	{
		clearJohnnyShadow();
		gameState.johnnyX -= 10;
		createJohnny();
	}
	else if (input.isRight() && isJohnnyInBounds(gameState.johnnyX + 10, gameState.johnnyY))
	{
		clearJohnnyShadow();
		gameState.johnnyX += 10;
		createJohnny();
	}
	else if (input.isDown() && isJohnnyInBounds(gameState.johnnyX, gameState.johnnyY + 10))
	{
		clearJohnnyShadow();
		gameState.johnnyY += 10;
		createJohnny();
	}
	else if (input.isUp() && isJohnnyInBounds(gameState.johnnyX, gameState.johnnyY - 10))
	{
		clearJohnnyShadow();
		gameState.johnnyY -= 10;
		createJohnny();
	}
}

void JohnnyGunGame::handleShooting()
{
	// Shooting is handled in handlePlayerInput()
}

void JohnnyGunGame::updateEnemies()
{
	// Update spawn timers and reset when needed
	if (gameState.johnnyGameTimer >= 500)
	{
		gameState.johnnyGameTimer = 0;
	}

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		Enemy &enemy = gameState.enemies[i];

		// Spawn new enemy if timer matches
		if (gameState.johnnyGameTimer == enemy.timer)
		{
			enemy.active = true;
			enemy.x = 510;
			enemy.y = rand() % (320 + 1);
		}

		// Move active enemies
		if (enemy.active)
		{
			clearEnemyShadow(enemy.x, enemy.y);
			enemy.x -= 10;
			createEnemy(enemy.x, enemy.y);
		}

		// Remove off-screen enemies
		if (enemy.x < -30)
		{
			enemy.active = false;
		}

		// Reset timer for inactive enemies
		if (!enemy.active)
		{
			enemy.timer = rand() % (gameState.spawnTimer + 1);
		}
	}
}

void JohnnyGunGame::updateBullet()
{
	if (gameState.bullet.active)
	{
		system->fillRect(gameState.bullet.x, gameState.bullet.y, BULLET_WIDTH, BULLET_HEIGHT, gameState.skyBackground);
		gameState.bullet.x += gameState.bullet.velocity;
		system->fillRect(gameState.bullet.x, gameState.bullet.y, BULLET_WIDTH, BULLET_HEIGHT, TFT_YELLOW);
	}

	if (gameState.bullet.x >= 480)
	{
		gameState.bullet.active = false;
	}
}

void JohnnyGunGame::checkCollisions()
{
	checkPlayerEnemyCollisions();
	checkBulletEnemyCollisions();
}

void JohnnyGunGame::checkPlayerEnemyCollisions()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		Enemy &enemy = gameState.enemies[i];

		if (enemy.active &&
			gameState.johnnyX < enemy.x && enemy.x < gameState.johnnyX + JOHNNY_WIDTH &&
			gameState.johnnyY < enemy.y && enemy.y < gameState.johnnyY + JOHNNY_HEIGHT)
		{
			gameOver();
			break;
		}
	}
}

void JohnnyGunGame::checkBulletEnemyCollisions()
{
	if (!gameState.bullet.active)
		return;

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		Enemy &enemy = gameState.enemies[i];

		if (enemy.active &&
			enemy.x < gameState.bullet.x && gameState.bullet.x < enemy.x + ENEMY_WIDTH &&
			enemy.y < gameState.bullet.y && gameState.bullet.y < enemy.y + ENEMY_HEIGHT)
		{

			gameState.bullet.active = false;
			system->playHitSound();

			// Update score display
			system->setTextProperties(TFT_WHITE, 2);
			system->fillRect(0, 0, 60, 40, gameState.skyBackground);
			gameState.jgScore += ENEMY_POINTS;
			drawScoreDisplay();

			// Clear bullet and enemy
			system->fillRect(gameState.bullet.x, gameState.bullet.y, BULLET_WIDTH, BULLET_HEIGHT, gameState.skyBackground);
			clearEnemyShadow(enemy.x, enemy.y);

			enemy.active = false;
			enemy.x = 0;
			enemy.y = 0;

			break;
		}
	}
}

void JohnnyGunGame::updateScore()
{
	// Score updates are handled in collision detection
}

void JohnnyGunGame::checkEnvironmentChanges()
{
	if (gameState.jgScore >= LIGHTS_OUT_SCORE && !gameState.lightsOut)
	{
		activateLightsOut();
	}

	if (gameState.jgScore >= BLOOD_MOON_SCORE && !gameState.bloodMoon)
	{
		activateBloodMoon();
	}
}

// =============================================================================
// ENTITY RENDERING
// =============================================================================
void JohnnyGunGame::createJohnny()
{
	system->fillRect(gameState.johnnyX, gameState.johnnyY, JOHNNY_WIDTH, JOHNNY_HEIGHT, TFT_MAROON);
	system->fillRect(gameState.johnnyX, gameState.johnnyY - 5, JOHNNY_WIDTH, 5, TFT_SKYBLUE);
	system->fillRect(gameState.johnnyX, gameState.johnnyY, 35, 5, TFT_SKYBLUE);
	system->fillRect(gameState.johnnyX + 5, gameState.johnnyY + 5, 5, 10, TFT_WHITE);
	system->fillRect(gameState.johnnyX + 15, gameState.johnnyY + 5, 5, 10, TFT_WHITE);
}

void JohnnyGunGame::createEnemy(int x, int y)
{
	system->fillRect(x, y, ENEMY_WIDTH, ENEMY_HEIGHT, TFT_BLACK);
	system->fillRect(x + 5, y + 5, 5, 10, TFT_RED);
	system->fillRect(x + 15, y + 5, 5, 10, TFT_RED);
}

void JohnnyGunGame::clearJohnnyShadow()
{
	system->fillRect(gameState.johnnyX, gameState.johnnyY - 5, 50, 85, gameState.skyBackground);
}

void JohnnyGunGame::clearEnemyShadow(int x, int y)
{
	system->fillRect(x, y, ENEMY_WIDTH, ENEMY_HEIGHT, gameState.skyBackground);
	system->fillRect(x + 5, y + 5, 5, 10, gameState.skyBackground);
	system->fillRect(x + 15, y + 5, 5, 10, gameState.skyBackground);
}

// =============================================================================
// ENVIRONMENT MANAGEMENT
// =============================================================================
void JohnnyGunGame::activateLightsOut()
{
	gameState.skyBackground = TFT_BLACK;
	gameState.lightsOut = true;
	state->markScreenForRedraw();
}

void JohnnyGunGame::activateBloodMoon()
{
	gameState.skyBackground = TFT_MAROON;
	gameState.bloodMoon = true;
	state->markScreenForRedraw();
}

// =============================================================================
// GAME OVER AND UTILITIES
// =============================================================================
void JohnnyGunGame::gameOver()
{
	system->playGameOverSound();
	system->clearScreen(TFT_BLACK);

	if (gameState.jgScore >= gameState.jgHighScore)
	{
		gameState.jgHighScore = gameState.jgScore;
		system->setTextProperties(TFT_GREEN, 3);
		system->drawString("NEW HIGH SCORE!", 110, 30);
	}

	system->setTextProperties(TFT_RED, 5);
	system->drawString("You LOSE!", 110, 90);

	// Purge all enemies
	resetEnemies();

	// Reset Johnny
	gameState.johnnyX = JOHNNY_START_X;
	gameState.johnnyY = JOHNNY_START_Y;

	// Show final stats
	char scoreStr[10];
	sprintf(scoreStr, "%d", gameState.jgScore);
	system->setTextProperties(TFT_WHITE, 2);
	system->drawString("Score:", 180, 140);
	system->drawString(scoreStr, 255, 140);

	system->setTextProperties(TFT_RED, 2);
	system->drawString("Returning to Main Menu...", 100, 220);

	system->delay(GAME_OVER_DELAY);

	state->transitionToScreen(JOHNNY_GUN_MENU);
}

void JohnnyGunGame::resetEnemies()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		gameState.enemies[i].active = false;
		gameState.enemies[i].x = 510;
		gameState.enemies[i].y = 0;
	}
}

void JohnnyGunGame::resetBullet()
{
	gameState.bullet.active = false;
}

// =============================================================================
// UTILITY METHODS
// =============================================================================
bool JohnnyGunGame::isJohnnyInBounds(int newX, int newY) const
{
	return (newX - 25 >= 0 && newX + 25 <= 480 && newY - 35 >= 0 && newY + 35 <= 320);
}

void JohnnyGunGame::updateGameTimer()
{
	gameState.johnnyGameTimer++;
}

void JohnnyGunGame::handleMenuNavigation()
{
	const InputState &input = system->getInput();

	if (input.isUp() && state->getCurrentMenuSelection() != 0)
	{
		state->decrementMenuSelection(3);
	}

	if (input.isDown() && state->getCurrentMenuSelection() != 2)
	{
		state->incrementMenuSelection(3);
	}
}

void JohnnyGunGame::drawScoreDisplay()
{
	char scoreStr[10];
	sprintf(scoreStr, "%d", gameState.jgScore);
	system->setTextProperties(TFT_WHITE, 2);
	system->drawString("SCORE:", 0, 0);
	system->drawString(scoreStr, 0, 20);
}