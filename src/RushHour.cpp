#include "RushHour.h"
#include <stdio.h>
#include <stdlib.h>

// =============================================================================
// CONSTRUCTOR AND INITIALIZATION
// =============================================================================
RushHourGame::RushHourGame(GameSystem *gameSystem, GameState *gameState, UIComponents *uiComponents)
	: system(gameSystem), state(gameState), ui(uiComponents)
{
	initialize();
}

void RushHourGame::initialize()
{
	initializeGameState();
	initializeColorWheel();
}

void RushHourGame::initializeGameState()
{
	// Player car defaults
	gameState.playerCarColor = TFT_YELLOW;
	gameState.playerWindowTint = TFT_SKYBLUE;
	gameState.playerCarPosX = PLAYER_CAR_START_X;
	gameState.playerCarPosY = PLAYER_CAR_START_Y;

	// Initialize enemy cars
	for (int i = 0; i < MAX_ENEMY_CARS; i++)
	{
		gameState.enemyCars[i].active = false;
		gameState.enemyCars[i].speed = DEFAULT_CAR_SPEED;
		gameState.enemyCars[i].posY = ENEMY_CAR_START_Y;
		gameState.enemyCars[i].posX = 186 + (i * 54); // Spread across lanes
		gameState.enemyCars[i].color = 0;
		gameState.enemyCars[i].timer = 0;
	}

	// Game state initialization
	gameState.level = INITIAL_LEVEL;
	gameState.score = 0;
	gameState.rh_highScore = 0;
	gameState.updateScore = 0;
	gameState.gameTimer = 0;
	gameState.maxCars = 2;
	gameState.rh_currency = INITIAL_CURRENCY;
	gameState.endGameTimer = 0;
	gameState.levelChanged = false;
	gameState.rh_speed = 1;
	gameState.carSpawnTimer = 0;

	// Power-ups initialization
	gameState.powerUps.pointMultiplier = INITIAL_POINT_MULTIPLIER;
	gameState.powerUps.invincibility = 0;
	gameState.powerUps.slowTime = 0;
	gameState.powerUps.flameBarrier = 0;
	gameState.powerUps.activePowerUp = 0;
	gameState.powerUps.powerUpTimer = 0;

	// Prices initialization
	gameState.pointMultiPrice = POINT_MULTIPLIER_BASE_PRICE;
	gameState.invincPrice = INVINCIBILITY_PRICE;
	gameState.slowTimePrice = SLOW_TIME_PRICE;
	gameState.flameBarrPrice = FLAME_BARRIER_PRICE;

	// UI state
	gameState.reset = false;
	gameState.colorIndex = 10;
}

void RushHourGame::initializeColorWheel()
{
	gameState.colorWheel[0] = TFT_BLACK;
	gameState.colorWheel[1] = TFT_NAVY;
	gameState.colorWheel[2] = TFT_DARKGREEN;
	gameState.colorWheel[3] = TFT_DARKCYAN;
	gameState.colorWheel[4] = TFT_MAROON;
	gameState.colorWheel[5] = TFT_PURPLE;
	gameState.colorWheel[6] = TFT_OLIVE;
	gameState.colorWheel[7] = TFT_BLUE;
	gameState.colorWheel[8] = TFT_GREEN;
	gameState.colorWheel[9] = TFT_CYAN;
	gameState.colorWheel[10] = TFT_RED;
	gameState.colorWheel[11] = TFT_MAGENTA;
	gameState.colorWheel[12] = TFT_YELLOW;
	gameState.colorWheel[13] = TFT_WHITE;
	gameState.colorWheel[14] = TFT_ORANGE;
	gameState.colorWheel[15] = TFT_GREENYELLOW;
	gameState.colorWheel[16] = TFT_PINK;
	gameState.colorWheel[17] = TFT_BROWN;
	gameState.colorWheel[18] = TFT_GOLD;
	gameState.colorWheel[19] = TFT_SILVER;
	gameState.colorWheel[20] = TFT_VIOLET;
}

void RushHourGame::resetGameState()
{
	gameState.score = 0;
	gameState.level = INITIAL_LEVEL;
	gameState.powerUps.activePowerUp = 0;
	resetEnemyCars();
	gameState.playerCarPosX = PLAYER_CAR_START_X;
}

// =============================================================================
// MAIN GAME SCREENS
// =============================================================================
void RushHourGame::showMenu()
{
	if (state->needsInitialization())
	{
		state->resetMenuSelection();
		ui->drawMenuBackground(TFT_DARKGREY);

		// High score display
		ui->drawHighScore(gameState.rh_highScore, 100, 30, TFT_YELLOW);

		// Game title
		ui->drawGameTitle("RUSH HOUR", 110, 80, TFT_WHITE, TFT_YELLOW);

		// Menu options
		system->setTextProperties(TFT_WHITE, 3);
		system->drawString("PLAY", 205, 160);
		system->drawString("SHOP", 205, 200);
		system->drawString("HOW TO PLAY", 145, 240);
		system->drawString("EXIT", 205, 280);

		state->markAsInitialized();
	}

	handleMenuNavigation();

	// Draw menu cursors
	const int menuY[] = {170, 210, 250, 290};
	const int menuX[] = {180, 180, 115, 180};

	// Clear all cursors
	for (int i = 0; i < 4; i++)
	{
		ui->clearMenuCursor(menuX[i], menuY[i], TFT_DARKGREY);
	}

	// Draw current selection cursor
	int currentSelection = state->getCurrentMenuSelection();
	if (currentSelection >= 0 && currentSelection < 4)
	{
		ui->drawMenuCursor(menuX[currentSelection], menuY[currentSelection], TFT_YELLOW);
	}

	// Handle selection
	if (system->isButton1JustPressed())
	{
		switch (currentSelection)
		{
		case 0: // PLAY
			state->transitionToScreen(RUSH_HOUR_GAME);
			break;
		case 1: // SHOP
			state->transitionToScreen(RUSH_HOUR_SHOP);
			break;
		case 2: // HOW TO PLAY
			state->transitionToScreen(HOW_TO_PLAY_RH);
			break;
		case 3: // EXIT
			state->transitionToScreen(MAIN_MENU);
			break;
		}
	}

	system->delay(MENU_NAVIGATION_DELAY);
}

void RushHourGame::showGame()
{
	if (state->needsInitialization())
	{
		if (gameState.level == 1)
		{
			gameState.score = 0;
		}
		gameState.powerUps.activePowerUp = 0;

		createLevel();

		// Game start countdown
		system->setTextProperties(TFT_GREEN, 3);
		system->drawString("4:59PM", 187, 120);
		system->setTextProperties(TFT_RED, 5);
		system->drawString("3", 225, 180);
		system->playTone(NOTE_A2, 500);
		system->delay(1000);

		system->setTextProperties(TFT_YELLOW, 5);
		system->fillRect(186, 180, 108, 120, TFT_DARKGREY);
		system->drawString("2", 225, 180);
		system->playTone(NOTE_A2, 500);
		system->delay(1000);

		system->setTextProperties(TFT_GREEN, 5);
		system->fillRect(186, 180, 108, 120, TFT_DARKGREY);
		system->drawString("1", 225, 180);
		system->playTone(NOTE_A2, 500);
		system->delay(1000);

		system->fillRect(186, 110, 108, 130, TFT_DARKGREY);
		system->setTextProperties(TFT_RED, 2);
		system->drawString("RUSH HOUR", 187, 180);
		system->setTextProperties(TFT_RED, 3);
		system->drawString("5:00PM", 187, 120);
		system->playTone(NOTE_C4, 500);
		system->delay(1000);
		system->fillRect(186, 110, 108, 130, TFT_DARKGREY);

		drawPowerUpDisplay();

		// Score display
		system->fillRect(0, 0, 78, 130, TFT_DARKGREEN);
		system->setTextProperties(TFT_WHITE, 2);
		system->drawString("SCORE:", 0, 0);
		char scoreStr[10];
		sprintf(scoreStr, "%d", (int)gameState.score);
		system->drawString(scoreStr, 0, 20);

		gameState.playerCarPosX = PLAYER_CAR_START_X;
		gameState.playerCarPosY = PLAYER_CAR_START_Y;
		paintPlayerCar();

		state->markAsInitialized();
		system->delay(1000);
	}

	updateGame();
}

void RushHourGame::showShop()
{
	if (state->needsInitialization())
	{
		gameState.reset = true;
		state->resetMenuSelection();
		ui->drawMenuBackground(TFT_DARKGREY);

		system->setTextProperties(TFT_WHITE, 5);
		system->drawString("SHOP", 10, 10);

		drawShopItems();

		// Currency display
		ui->drawCurrency({gameState.rh_currency, 10, 50, "RUSH BUCKS:", TFT_WHITE, TFT_GREEN, 3});

		state->markAsInitialized();
	}

	handleShopInput();
}

void RushHourGame::showHowToPlay()
{
	if (state->needsInitialization())
	{
		ui->drawMenuBackground(TFT_DARKGREY);

		system->setTextProperties(TFT_WHITE, 5);
		system->drawString("HOW TO PLAY", 75, 60);

		system->setTextProperties(TFT_WHITE, 2);
		system->drawString("Oh no! You've turned into the wrong lane!", 0, 120);
		system->drawString("Avoid oncoming traffic during Rush Hour.", 0, 150);
		system->drawString("Survive and gain points to spend in the", 0, 180);
		system->drawString("shop for power-ups and more!", 0, 210);

		ui->drawBackToMenuPrompt();

		state->markAsInitialized();
	}

	if (system->isButton1JustPressed())
	{
		state->transitionToScreen(RUSH_HOUR_MENU);
	}
}

void RushHourGame::showCarCustomization()
{
	if (state->needsInitialization())
	{
		gameState.colorIndex = 10;
		state->resetMenuSelection();
		gameState.playerCarPosX = 216;
		gameState.playerCarPosY = 50;

		ui->drawMenuBackground(TFT_DARKGREY);

		system->setTextProperties(TFT_WHITE, 5);
		system->drawString("COLOUR", 10, 10);

		system->fillRect(0, 60, 480, 200, TFT_LIGHTGREY);

		// Color preview
		system->fillRect(190, 160, 100, 100, gameState.colorWheel[gameState.colorIndex]);
		system->drawRect(190, 160, 100, 100, TFT_BLACK);

		// Navigation arrows
		system->setTextProperties(TFT_WHITE, 5);
		system->drawString("<", 140, 200);
		system->drawString(">", 310, 200);

		// Currency and prices
		ui->drawCurrency({gameState.rh_currency, 240, 40, "RUSH BUCKS:", TFT_WHITE, TFT_GREEN, 2});

		system->setTextProperties(TFT_WHITE, 3);
		system->drawString("TINT", 30, 90);
		system->drawString("SPRAY", 30, 120);
		system->drawString("<- SHOP", 35, 280);

		system->setTextProperties(TFT_GREEN, 3);
		system->drawString("$200", 110, 90);
		system->drawString("$500", 130, 120);

		paintPlayerCar();
		state->markAsInitialized();
	}

	handleCustomizationInput();
}

// =============================================================================
// GAME MECHANICS
// =============================================================================
void RushHourGame::updateGame()
{
	updateGameTimer();
	handlePlayerInput();
	updateEnemyCars();
	checkCollisions();
	updateScore();
	checkLevelProgression();
	handlePowerUps();
}

void RushHourGame::handlePlayerInput()
{
	const InputState &input = system->getInput();

	// Player car movement RIGHT
	if (input.isRight() && gameState.playerCarPosX != gameState.carRightEnd)
	{
		system->fillRect(gameState.playerCarPosX - 1, 240, 45, 88, TFT_DARKGREY);
		if (gameState.playerCarPosX != 186)
		{
			gameState.playerCarPosX += 44;
		}
		else
		{
			gameState.playerCarPosX += 64;
		}
		paintPlayerCar();
	}

	// Player car movement LEFT
	if (input.isLeft() && gameState.playerCarPosX != gameState.carLeftEnd)
	{
		system->fillRect(gameState.playerCarPosX - 1, 240, 45, 88, TFT_DARKGREY);
		if (gameState.playerCarPosX != 250)
		{
			gameState.playerCarPosX -= 44;
		}
		else
		{
			gameState.playerCarPosX -= 64;
		}
		paintPlayerCar();
	}

	// Power-up activation
	if (system->isButton2JustPressed() && gameState.powerUps.activePowerUp == 0 && gameState.powerUps.invincibility >= 1)
	{
		activatePowerUp(1); // Invincibility
	}

	if (system->isButton3JustPressed() && gameState.powerUps.activePowerUp == 0 && gameState.powerUps.slowTime >= 1)
	{
		activatePowerUp(2); // Slow time
	}

	if (system->isButton1JustPressed() && gameState.powerUps.activePowerUp == 0 && gameState.powerUps.flameBarrier >= 1)
	{
		activatePowerUp(3); // Flame barrier
	}
}

void RushHourGame::updateEnemyCars()
{
	// Reset game timer when spawn timer is reached
	if (gameState.gameTimer == gameState.carSpawnTimer)
	{
		gameState.gameTimer = 0;
		for (int i = 0; i < gameState.maxCars; i++)
		{
			gameState.enemyCars[i].timer = rand() % (gameState.carSpawnTimer + 1);
		}
	}

	for (int i = 0; i < gameState.maxCars; i++)
	{
		EnemyCar &car = gameState.enemyCars[i];

		// Reset cars that reach the end of screen
		if (car.posY >= 320)
		{
			car.posY = ENEMY_CAR_START_Y;
			car.active = false;
			if (gameState.powerUps.activePowerUp == 1)
			{
				paintPlayerCar();
			}
		}

		// Move active cars
		if (car.active)
		{
			if (gameState.powerUps.activePowerUp == 2)
			{
				car.posY += 3; // Slow time effect
			}
			else
			{
				if (car.color != 7)
				{
					car.posY += car.speed;
				}
				else
				{
					car.posY += 20; // Boss car moves faster
				}
			}
			loadEnemyCar(car.posX, car.posY, car.color);
		}

		// Spawn new cars based on timer
		if (car.timer == gameState.gameTimer)
		{
			car.active = true;
			car.posY -= car.speed;
			car.color = getRandomEnemyColor();
			loadEnemyCar(car.posX, car.posY, car.color);
		}
	}
}

void RushHourGame::checkCollisions()
{
	for (int i = 0; i < gameState.maxCars; i++)
	{
		EnemyCar &car = gameState.enemyCars[i];

		// Flame barrier collision (destroys enemies)
		if (car.posY >= 141 && car.posX == gameState.playerCarPosX && gameState.powerUps.activePowerUp == 3)
		{
			car.active = false;
			system->fillRect(car.posX, car.posY, CAR_WIDTH, CAR_HEIGHT, TFT_RED);
			system->delay(200);
			system->fillRect(car.posX, car.posY, CAR_WIDTH, CAR_HEIGHT, TFT_ORANGE);

			system->setTextProperties(TFT_GREEN, 2);
			if (car.color != 7)
			{
				gameState.score += NORMAL_ENEMY_POINTS;
				system->playTone(NOTE_B4, 100);
				system->delay(100);
				system->drawString("+100", 0, 60);
				system->drawString("NORMAL", 0, 80);
				system->drawString("ENEMY!", 0, 100);
			}
			else
			{
				gameState.score += BOSS_ENEMY_POINTS;
				system->playTone(NOTE_B4, 100);
				system->delay(100);
				system->drawString("+500!", 0, 60);
				system->drawString("BOSS", 0, 80);
				system->drawString("ENEMY!", 0, 100);
			}

			system->delay(200);
			system->fillRect(car.posX, car.posY, CAR_WIDTH, CAR_HEIGHT, TFT_DARKGREY);
			system->delay(200);
			paintPlayerCar();
			system->fillRect(0, 20, 78, 130, TFT_DARKGREEN);
			car.posY = ENEMY_CAR_START_Y;
		}

		// Regular collision (game over unless invincible)
		if (car.posY >= 141 && car.posX == gameState.playerCarPosX &&
			gameState.powerUps.activePowerUp != 1 && gameState.powerUps.activePowerUp != 3)
		{
			gameOver();
			break;
		}
	}
}

void RushHourGame::updateScore()
{
	if (gameState.updateScore == 40)
	{
		gameState.score += (BASE_POINTS_PER_SECOND * gameState.powerUps.pointMultiplier);

		system->setTextProperties(TFT_WHITE, 2);
		system->fillRect(0, 20, 78, 50, TFT_DARKGREEN);
		char scoreStr[10];
		sprintf(scoreStr, "%d", (int)gameState.score);
		system->drawString(scoreStr, 0, 20);

		gameState.levelChanged = false;
		gameState.updateScore = 0;
	}

	if (gameState.score >= 1000)
	{
		gameState.endGameTimer++;
	}

	if (gameState.endGameTimer >= 100 && gameState.enemyCars[0].speed != 20)
	{
		for (int i = 0; i < gameState.maxCars; i++)
		{
			gameState.enemyCars[i].speed++;
		}
		gameState.endGameTimer = 0;
	}

	gameState.updateScore++;
}

void RushHourGame::checkLevelProgression()
{
	const int levelScores[] = {LEVEL_2_SCORE, LEVEL_3_SCORE, LEVEL_4_SCORE, LEVEL_5_SCORE,
							   LEVEL_6_SCORE, LEVEL_7_SCORE, LEVEL_8_SCORE, LEVEL_9_SCORE};

	for (int level = 2; level <= 9; level++)
	{
		if (gameState.score >= levelScores[level - 2] && !gameState.levelChanged && gameState.level < level)
		{
			transitionToNextLevel();
			gameState.level = level;
			break;
		}
	}
}

void RushHourGame::transitionToNextLevel()
{
	uint16_t levelColor = TFT_GREEN;
	if (gameState.level >= 4)
		levelColor = TFT_BLUE;
	if (gameState.level >= 5)
		levelColor = TFT_MAROON;
	if (gameState.level >= 6)
		levelColor = TFT_PURPLE;
	if (gameState.level >= 7)
		levelColor = TFT_CYAN;
	if (gameState.level >= 8)
		levelColor = TFT_SILVER;
	if (gameState.level >= 9)
		levelColor = TFT_GOLD;

	system->clearScreen(levelColor);
	system->setTextProperties(TFT_BLACK, 5);
	system->drawString("Next Level!", 90, 140);

	system->playLevelUpSound();

	system->delay(LEVEL_TRANSITION_DELAY);
	gameState.levelChanged = true;
	state->markScreenForRedraw();
}

void RushHourGame::handlePowerUps()
{
	if (gameState.powerUps.activePowerUp != 0)
	{
		gameState.powerUps.powerUpTimer++;
	}

	const int durations[] = {0, INVINCIBILITY_DURATION, SLOW_TIME_DURATION, FLAME_BARRIER_DURATION};

	if (gameState.powerUps.activePowerUp > 0 && gameState.powerUps.activePowerUp <= 3)
	{
		if (gameState.powerUps.powerUpTimer >= durations[gameState.powerUps.activePowerUp])
		{
			gameState.powerUps.activePowerUp = 0;
			gameState.powerUps.powerUpTimer = -1;
		}
	}
}

// =============================================================================
// CAR RENDERING
// =============================================================================
void RushHourGame::paintPlayerCar()
{
	if (gameState.powerUps.activePowerUp == 1)
	{
		// Invincibility - black and white
		system->fillRect(gameState.playerCarPosX + 2, gameState.playerCarPosY + 8, 39, 74, TFT_BLACK);
		system->fillRect(gameState.playerCarPosX + 4, gameState.playerCarPosY + 13, 35, 67, TFT_BLACK);
		system->fillRect(gameState.playerCarPosX - 1, gameState.playerCarPosY + 70, 45, 5, TFT_WHITE);
		// Windows and mirrors
		system->fillRect(gameState.playerCarPosX + 4, gameState.playerCarPosY + 36, 35, 13, TFT_WHITE);
		system->fillRect(gameState.playerCarPosX - 1, gameState.playerCarPosY + 36, 5, 2, TFT_BLACK);
		system->fillRect(gameState.playerCarPosX + 39, gameState.playerCarPosY + 36, 5, 2, TFT_BLACK);
	}
	else if (gameState.powerUps.activePowerUp == 2)
	{
		// Slow time - blue theme
		system->fillRect(gameState.playerCarPosX + 2, gameState.playerCarPosY + 8, 39, 74, TFT_BLACK);
		system->fillRect(gameState.playerCarPosX + 4, gameState.playerCarPosY + 13, 35, 67, TFT_SKYBLUE);
		system->fillRect(gameState.playerCarPosX - 1, gameState.playerCarPosY + 70, 45, 5, TFT_WHITE);
		// Windows and mirrors
		system->fillRect(gameState.playerCarPosX + 4, gameState.playerCarPosY + 36, 35, 13, TFT_WHITE);
		system->fillRect(gameState.playerCarPosX - 1, gameState.playerCarPosY + 36, 5, 2, TFT_SKYBLUE);
		system->fillRect(gameState.playerCarPosX + 39, gameState.playerCarPosY + 36, 5, 2, TFT_SKYBLUE);
	}
	else if (gameState.powerUps.activePowerUp == 3)
	{
		// Flame barrier - red/orange theme
		system->fillRect(gameState.playerCarPosX + 2, gameState.playerCarPosY + 8, 39, 74, TFT_BLACK);
		system->fillRect(gameState.playerCarPosX + 4, gameState.playerCarPosY + 13, 35, 67, TFT_RED);
		system->fillRect(gameState.playerCarPosX - 1, gameState.playerCarPosY + 70, 45, 5, TFT_ORANGE);
		// Windows and mirrors
		system->fillRect(gameState.playerCarPosX + 4, gameState.playerCarPosY + 36, 35, 13, TFT_ORANGE);
		system->fillRect(gameState.playerCarPosX - 1, gameState.playerCarPosY + 36, 5, 2, TFT_RED);
		system->fillRect(gameState.playerCarPosX + 39, gameState.playerCarPosY + 36, 5, 2, TFT_RED);
	}
	else
	{
		// Normal car
		system->fillRect(gameState.playerCarPosX + 2, gameState.playerCarPosY + 8, 39, 74, TFT_BLACK);
		system->fillRect(gameState.playerCarPosX + 4, gameState.playerCarPosY + 13, 35, 67, gameState.playerCarColor);
		system->fillRect(gameState.playerCarPosX - 1, gameState.playerCarPosY + 70, 45, 5, gameState.playerCarColor);
		// Windows and mirrors
		system->fillRect(gameState.playerCarPosX + 4, gameState.playerCarPosY + 36, 35, 13, gameState.playerWindowTint);
		system->fillRect(gameState.playerCarPosX - 1, gameState.playerCarPosY + 36, 5, 2, gameState.playerCarColor);
		system->fillRect(gameState.playerCarPosX + 39, gameState.playerCarPosY + 36, 5, 2, gameState.playerCarColor);
	}
}

void RushHourGame::loadEnemyCar(uint16_t posX, uint16_t posY, uint16_t color)
{
	if (color == 1 || color == 3 || color == 4)
	{
		system->pushImage(posX, posY, CAR_WIDTH, CAR_HEIGHT, purpleCar);
	}
	else if (color == 2 || color == 5 || color == 6)
	{
		system->pushImage(posX, posY, CAR_WIDTH, CAR_HEIGHT, orangeCar);
	}
	else if (color == 7)
	{
		system->pushImage(posX, posY, CAR_WIDTH, CAR_HEIGHT, bossCar);
	}
}

// =============================================================================
// LEVEL MANAGEMENT
// =============================================================================
void RushHourGame::createLevel()
{
	if (gameState.level == 1)
	{
		gameState.gameTimer = 0;
		system->clearScreen(TFT_DARKGREEN);
		system->fillRect(166, 0, 20, 320, TFT_WHITE);
		system->fillRect(186, 0, 108, 320, TFT_DARKGREY);
		system->fillRect(294, 0, 20, 320, TFT_WHITE);
		gameState.carSpawnTimer = 500;
		gameState.carRightEnd = 250;
		gameState.carLeftEnd = 186;
		gameState.maxCars = 2;
		for (int i = 0; i < gameState.maxCars; i++)
		{
			gameState.enemyCars[i].speed = 5;
			gameState.enemyCars[i].timer = rand() % (gameState.carSpawnTimer + 1);
		}
	}
	else if (gameState.level == 2)
	{
		gameState.gameTimer = 0;
		system->clearScreen(TFT_DARKGREEN);
		system->fillRect(122, 0, 20, 320, TFT_WHITE);
		system->fillRect(142, 0, 196, 320, TFT_DARKGREY);
		system->fillRect(338, 0, 20, 320, TFT_WHITE);
		gameState.carSpawnTimer = 300;
		gameState.carRightEnd = 294;
		gameState.carLeftEnd = 142;
		gameState.maxCars = 4;
		for (int i = 0; i < gameState.maxCars; i++)
		{
			gameState.enemyCars[i].speed = 8;
			gameState.enemyCars[i].timer = rand() % (gameState.carSpawnTimer + 1);
		}
	}
	else if (gameState.level == 3)
	{
		gameState.gameTimer = 0;
		system->clearScreen(TFT_DARKGREEN);
		system->fillRect(78, 0, 20, 320, TFT_WHITE);
		system->fillRect(98, 0, 284, 320, TFT_DARKGREY);
		system->fillRect(382, 0, 20, 320, TFT_WHITE);
		gameState.carSpawnTimer = 200;
		gameState.carRightEnd = 338;
		gameState.carLeftEnd = 98;
		gameState.maxCars = 6;
		for (int i = 0; i < gameState.maxCars; i++)
		{
			gameState.enemyCars[i].speed = 10;
			gameState.enemyCars[i].timer = rand() % (gameState.carSpawnTimer + 1);
		}
	}
	else
	{
		// Levels 4-9 use same road layout but different colors
		gameState.gameTimer = 0;
		system->clearScreen(TFT_DARKGREEN);
		system->fillRect(98, 0, 284, 320, TFT_DARKGREY);

		uint16_t sideColor = TFT_BLUE;
		if (gameState.level == 5)
			sideColor = TFT_MAROON;
		else if (gameState.level == 6)
			sideColor = TFT_PURPLE;
		else if (gameState.level == 7)
			sideColor = TFT_CYAN;
		else if (gameState.level == 8)
			sideColor = TFT_SILVER;
		else if (gameState.level == 9)
			sideColor = TFT_GOLD;

		system->fillRect(78, 0, 20, 320, sideColor);
		system->fillRect(382, 0, 20, 320, sideColor);

		for (int i = 0; i < gameState.maxCars; i++)
		{
			gameState.enemyCars[i].timer = rand() % (gameState.carSpawnTimer + 1);
		}
	}

	calculateCarBoundaries();
}

void RushHourGame::calculateCarBoundaries()
{
	// Set enemy car positions based on level
	if (gameState.level == 1)
	{
		gameState.enemyCars[0].posX = 186;
		gameState.enemyCars[1].posX = 250;
	}
	else if (gameState.level == 2)
	{
		gameState.enemyCars[0].posX = 142;
		gameState.enemyCars[1].posX = 250;
		gameState.enemyCars[2].posX = 294;
		gameState.enemyCars[3].posX = 338;
	}
	else if (gameState.level >= 3)
	{
		gameState.enemyCars[0].posX = 98;
		gameState.enemyCars[1].posX = 142;
		gameState.enemyCars[2].posX = 186;
		gameState.enemyCars[3].posX = 250;
		gameState.enemyCars[4].posX = 294;
		gameState.enemyCars[5].posX = 338;
	}
}

// =============================================================================
// SHOP SYSTEM
// =============================================================================
void RushHourGame::handleShopInput()
{
	const InputState &input = system->getInput();

	if (input.isUp() && state->getCurrentMenuSelection() != 0)
	{
		system->fillRect(0, 80, 480, 55, TFT_BLACK);
		state->decrementMenuSelection(6);
	}

	if (input.isDown() && state->getCurrentMenuSelection() != 5)
	{
		system->fillRect(0, 80, 480, 55, TFT_BLACK);
		state->incrementMenuSelection(6);
	}

	drawShopItems();
	updateShopDisplay();

	if (system->isButton1JustPressed())
	{
		int selection = state->getCurrentMenuSelection();
		switch (selection)
		{
		case 0: // Tints/Sprays
			state->transitionToScreen(SPRAY_CAR);
			break;
		case 1: // Point Multiplier
			if (gameState.powerUps.pointMultiplier < MAX_POINT_MULTIPLIER)
			{
				purchaseItem(1);
			}
			break;
		case 2: // Invincibility
			purchaseItem(2);
			break;
		case 3: // Slow Time
			purchaseItem(3);
			break;
		case 4: // Flame Barrier
			purchaseItem(4);
			break;
		case 5: // Exit
			state->transitionToScreen(RUSH_HOUR_MENU);
			break;
		}
	}

	system->delay(MENU_NAVIGATION_DELAY);
}

void RushHourGame::drawShopItems()
{
	system->setTextProperties(TFT_BLACK, 3);
	system->fillRect(0, 80, 480, 55, TFT_BLACK);
	system->setTextColor(TFT_BLUE);
	system->drawString("Tints/Sprays...", 40, 140);

	system->setTextColor(TFT_YELLOW);
	system->drawString("Point Multiplier", 40, 170);
	char priceStr[10];
	sprintf(priceStr, "%d", gameState.pointMultiPrice);
	system->setTextColor(TFT_GREEN);
	system->drawString("$", 380, 170);
	system->drawString(priceStr, 400, 170);

	// Invincibility
	system->setTextColor(TFT_BLACK);
	system->drawString("Invincibility", 40, 200);
	system->fillCircle(300, 210, 16, TFT_BLACK);
	system->fillCircle(300, 210, 8, TFT_WHITE);
	sprintf(priceStr, "%d", gameState.invincPrice);
	system->setTextColor(TFT_GREEN);
	system->drawString("$", 380, 200);
	system->drawString(priceStr, 400, 200);

	// Slow Time
	system->setTextColor(TFT_SKYBLUE);
	system->drawString("Slow Time", 40, 230);
	system->fillCircle(230, 240, 16, TFT_SKYBLUE);
	system->fillRect(230, 236, 16, 5, TFT_WHITE);
	sprintf(priceStr, "%d", gameState.slowTimePrice);
	system->setTextColor(TFT_GREEN);
	system->drawString("$", 380, 230);
	system->drawString(priceStr, 400, 230);

	// Flame Barrier
	system->setTextColor(TFT_ORANGE);
	system->drawString("Flame Barrier", 40, 260);
	system->fillCircle(300, 270, 16, TFT_RED);
	system->fillCircle(300, 278, 8, TFT_ORANGE);
	sprintf(priceStr, "%d", gameState.flameBarrPrice);
	system->setTextColor(TFT_GREEN);
	system->drawString("$", 380, 260);
	system->drawString(priceStr, 400, 260);

	system->setTextColor(TFT_WHITE);
	system->drawString("<- MENU", 40, 290);
}

void RushHourGame::updateShopDisplay()
{
	int selection = state->getCurrentMenuSelection();
	const int menuY[] = {150, 180, 210, 240, 270, 300};

	// Clear all cursors
	for (int i = 0; i < 6; i++)
	{
		ui->clearMenuCursor(15, menuY[i], TFT_DARKGREY);
	}

	// Draw current selection
	if (selection >= 0 && selection < 6)
	{
		ui->drawMenuCursor(15, menuY[selection], TFT_WHITE);
	}

	// Show item description
	system->fillRect(0, 80, 480, 55, TFT_BLACK);
	system->setTextProperties(TFT_WHITE, 2);

	switch (selection)
	{
	case 0:
		system->setTextColor(TFT_BLUE);
		system->drawString("Change the colour of your car.", 10, 90);
		break;
	case 1:
		system->setTextColor(TFT_YELLOW);
		system->drawString("Gain more points per second.", 10, 90);
		if (gameState.powerUps.pointMultiplier != MAX_POINT_MULTIPLIER)
		{
			system->drawString("Current multiplier is: ", 10, 110);
			char multiStr[5];
			sprintf(multiStr, "%d", gameState.powerUps.pointMultiplier);
			system->drawString(multiStr, 275, 110);
			system->drawString("X", 290, 110);
		}
		else
		{
			system->drawString("Points Multiplier is MAXED (3X): ", 10, 110);
		}
		break;
	case 2:
		system->setTextColor(TFT_DARKGREY);
		system->setTextSize(1);
		system->drawString("Powerup! Phase through oncoming cars for 5 seconds.", 10, 90);
		system->drawString("Amount: ", 10, 110);
		char invincStr[5];
		sprintf(invincStr, "%d", gameState.powerUps.invincibility);
		system->drawString(invincStr, 70, 110);
		break;
	case 3:
		system->setTextColor(TFT_SKYBLUE);
		system->setTextSize(1);
		system->drawString("Powerup! Slows time for oncoming cars 10 seconds.", 10, 90);
		system->drawString("Amount: ", 10, 110);
		char slowStr[5];
		sprintf(slowStr, "%d", gameState.powerUps.slowTime);
		system->drawString(slowStr, 70, 110);
		break;
	case 4:
		system->setTextColor(TFT_ORANGE);
		system->setTextSize(1);
		system->drawString("Powerup! Casts a flame around your car for 10 seconds.", 10, 90);
		system->drawString("Incinerates incoming cars and gives 100 points.", 10, 105);
		system->drawString("Amount: ", 10, 120);
		char flameStr[5];
		sprintf(flameStr, "%d", gameState.powerUps.flameBarrier);
		system->drawString(flameStr, 70, 120);
		break;
	case 5:
		system->setTextColor(TFT_WHITE);
		system->setTextSize(3);
		system->drawString("Leave shop?", 10, 90);
		break;
	}
}

void RushHourGame::purchaseItem(int itemIndex)
{
	int price = 0;
	bool purchased = false;

	switch (itemIndex)
	{
	case 1: // Point Multiplier
		price = gameState.pointMultiPrice;
		if (gameState.rh_currency >= price && gameState.powerUps.pointMultiplier < MAX_POINT_MULTIPLIER)
		{
			gameState.rh_currency -= price;
			gameState.powerUps.pointMultiplier++;
			gameState.pointMultiPrice += 3000;
			purchased = true;

			system->fillRect(400, 170, 80, 25, TFT_DARKGREY);
			char priceStr[10];
			sprintf(priceStr, "%d", gameState.pointMultiPrice);
			system->setTextProperties(TFT_GREEN, 3);
			system->drawString(priceStr, 400, 170);
		}
		break;
	case 2: // Invincibility
		price = gameState.invincPrice;
		if (gameState.rh_currency >= price)
		{
			gameState.rh_currency -= price;
			gameState.powerUps.invincibility++;
			purchased = true;
		}
		break;
	case 3: // Slow Time
		price = gameState.slowTimePrice;
		if (gameState.rh_currency >= price)
		{
			gameState.rh_currency -= price;
			gameState.powerUps.slowTime++;
			purchased = true;
		}
		break;
	case 4: // Flame Barrier
		price = gameState.flameBarrPrice;
		if (gameState.rh_currency >= price)
		{
			gameState.rh_currency -= price;
			gameState.powerUps.flameBarrier++;
			purchased = true;
		}
		break;
	}

	if (purchased)
	{
		system->playSuccessSound();
		system->fillRect(0, 80, 480, 55, TFT_BLACK);
		system->setTextProperties(TFT_GREEN, 2);
		system->drawString("Purchased!", 10, 90);
		system->delay(POWERUP_NOTIFICATION_DELAY);

		// Update currency display
		system->fillRect(230, 50, 250, 25, TFT_DARKGREY);
		char currencyStr[10];
		sprintf(currencyStr, "%d", gameState.rh_currency);
		system->setTextProperties(TFT_GREEN, 3);
		system->drawString(currencyStr, 230, 50);
	}
	else
	{
		system->playErrorSound();
		system->fillRect(0, 80, 480, 55, TFT_BLACK);
		system->setTextProperties(TFT_RED, 2);
		system->drawString("Not enough Rush Bucks!", 10, 90);
		system->delay(POWERUP_NOTIFICATION_DELAY);
		system->fillRect(0, 80, 480, 55, TFT_BLACK);
	}
}

// =============================================================================
// CAR CUSTOMIZATION
// =============================================================================
void RushHourGame::handleCustomizationInput()
{
	const InputState &input = system->getInput();

	if (input.isRight() && gameState.colorIndex != 0)
	{
		gameState.colorIndex--;
		system->setTextProperties(TFT_DARKGREY, 5);
		system->drawString(">", 310, 200);
		system->playMenuSound();
		system->delay(100);

		system->fillRect(190, 160, 100, 100, gameState.colorWheel[gameState.colorIndex]);
		system->drawRect(190, 160, 100, 100, TFT_BLACK);
		system->setTextProperties(TFT_WHITE, 5);
		system->drawString(">", 310, 200);
	}

	if (input.isLeft() && gameState.colorIndex != 20)
	{
		gameState.colorIndex++;
		system->setTextProperties(TFT_DARKGREY, 5);
		system->drawString("<", 140, 200);
		system->playMenuSound();
		system->delay(100);

		system->fillRect(190, 160, 100, 100, gameState.colorWheel[gameState.colorIndex]);
		system->drawRect(190, 160, 100, 100, TFT_BLACK);
		system->setTextProperties(TFT_WHITE, 5);
		system->drawString("<", 140, 200);
	}

	if (input.isUp() && state->getCurrentMenuSelection() != 0)
	{
		state->decrementMenuSelection(3);
	}

	if (input.isDown() && state->getCurrentMenuSelection() != 2)
	{
		state->incrementMenuSelection(3);
	}

	// Draw menu cursors
	const int menuY[] = {98, 128, 290};
	for (int i = 0; i < 3; i++)
	{
		ui->clearMenuCursor(15, menuY[i], TFT_DARKGREY);
	}

	int selection = state->getCurrentMenuSelection();
	if (selection >= 0 && selection < 3)
	{
		ui->drawMenuCursor(15, menuY[selection], TFT_WHITE);
	}

	if (system->isButton1JustPressed())
	{
		switch (selection)
		{
		case 0: // Tint
			purchaseCustomization(true);
			break;
		case 1: // Spray
			purchaseCustomization(false);
			break;
		case 2: // Back to shop
			state->transitionToScreen(RUSH_HOUR_SHOP);
			break;
		}
	}

	system->delay(100);
}

void RushHourGame::purchaseCustomization(bool isTint)
{
	int price = isTint ? 200 : 500;

	if (gameState.rh_currency >= price)
	{
		if (isTint)
		{
			gameState.playerWindowTint = gameState.colorWheel[gameState.colorIndex];
		}
		else
		{
			gameState.playerCarColor = gameState.colorWheel[gameState.colorIndex];
		}

		gameState.rh_currency -= price;

		system->setTextProperties(TFT_GREEN, 2);
		system->fillRect(370, 40, 120, 20, TFT_DARKGREY);
		system->drawString("PURCHASED", 370, 40);
		system->playSuccessSound();
		system->delay(POWERUP_NOTIFICATION_DELAY);

		paintPlayerCar();

		// Update currency display
		system->fillRect(370, 40, 120, 20, TFT_DARKGREY);
		system->setTextColor(TFT_WHITE);
		system->drawString("$", 370, 40);
		char currencyStr[10];
		sprintf(currencyStr, "%d", gameState.rh_currency);
		system->setTextColor(TFT_GREEN);
		system->drawString(currencyStr, 383, 40);
	}
	else
	{
		system->playErrorSound();
		system->delay(DEFAULT_REST_DURATION);
	}
}

// =============================================================================
// POWER-UP SYSTEM
// =============================================================================
void RushHourGame::activatePowerUp(int powerUpType)
{
	switch (powerUpType)
	{
	case 1: // Invincibility
		if (gameState.powerUps.invincibility >= 1)
		{
			gameState.powerUps.activePowerUp = 1;
			gameState.powerUps.invincibility--;
			gameState.powerUps.powerUpTimer = 0;
			system->playSelectSound();
			updatePowerUpDisplay(1);
			paintPlayerCar();
		}
		break;
	case 2: // Slow Time
		if (gameState.powerUps.slowTime >= 1)
		{
			gameState.powerUps.activePowerUp = 2;
			gameState.powerUps.slowTime--;
			gameState.powerUps.powerUpTimer = 0;
			system->playSelectSound();
			updatePowerUpDisplay(2);
			paintPlayerCar();
		}
		break;
	case 3: // Flame Barrier
		if (gameState.powerUps.flameBarrier >= 1)
		{
			gameState.powerUps.activePowerUp = 3;
			gameState.powerUps.flameBarrier--;
			gameState.powerUps.powerUpTimer = 0;
			system->playSelectSound();
			updatePowerUpDisplay(3);
			paintPlayerCar();
		}
		break;
	}
}

void RushHourGame::updatePowerUpDisplay(int powerUpType)
{
	int yPos[] = {164, 224, 284};
	if (powerUpType >= 1 && powerUpType <= 3)
	{
		system->fillRect(37, yPos[powerUpType - 1], 20, 20, TFT_DARKGREEN);
		char countStr[5];

		switch (powerUpType)
		{
		case 1:
			sprintf(countStr, "%d", gameState.powerUps.invincibility);
			break;
		case 2:
			sprintf(countStr, "%d", gameState.powerUps.slowTime);
			break;
		case 3:
			sprintf(countStr, "%d", gameState.powerUps.flameBarrier);
			break;
		}

		system->setTextProperties(TFT_WHITE, 2);
		system->drawString(countStr, 37, yPos[powerUpType - 1]);
	}
}

void RushHourGame::drawPowerUpDisplay()
{
	system->setTextProperties(TFT_WHITE, 2);

	// Invincibility
	system->fillCircle(16, 170, 16, TFT_BLACK);
	system->fillCircle(16, 170, 8, TFT_WHITE);
	system->fillCircle(16, 140, 10, TFT_BLACK);
	system->drawString("B", 12, 135);
	char invincStr[5];
	sprintf(invincStr, "%d", gameState.powerUps.invincibility);
	system->drawString(invincStr, 37, 164);

	// Slow Time
	system->fillCircle(16, 230, 16, TFT_SKYBLUE);
	system->fillRect(16, 226, 16, 5, TFT_WHITE);
	system->fillCircle(16, 200, 10, TFT_BLACK);
	system->drawString("Y", 12, 195);
	char slowStr[5];
	sprintf(slowStr, "%d", gameState.powerUps.slowTime);
	system->drawString(slowStr, 37, 224);

	// Flame Barrier
	system->fillCircle(16, 290, 16, TFT_RED);
	system->fillCircle(16, 298, 8, TFT_ORANGE);
	system->fillCircle(16, 262, 10, TFT_BLACK);
	system->drawString("A", 11, 256);
	char flameStr[5];
	sprintf(flameStr, "%d", gameState.powerUps.flameBarrier);
	system->drawString(flameStr, 37, 284);
}

// =============================================================================
// GAME OVER AND UTILITIES
// =============================================================================
void RushHourGame::gameOver()
{
	system->playGameOverSound();
	system->clearScreen(TFT_RED);

	if (gameState.score >= gameState.rh_highScore)
	{
		gameState.rh_highScore = gameState.score;
		system->setTextProperties(TFT_GREEN, 3);
		system->drawString("NEW HIGH SCORE!", 110, 30);
	}

	system->setTextProperties(TFT_WHITE, 5);
	system->drawString("You LOSE!", 110, 90);

	// Purge all enemy cars
	resetEnemyCars();

	// Reset player car
	gameState.playerCarPosX = PLAYER_CAR_START_X;

	// Convert score to currency and reset
	convertScoreToCurrency();

	// Show final stats
	char scoreStr[10];
	sprintf(scoreStr, "%d", (int)gameState.score);
	system->setTextProperties(TFT_WHITE, 2);
	system->drawString("Score:", 180, 140);
	system->drawString(scoreStr, 255, 140);

	system->setTextProperties(TFT_GREEN, 2);
	system->drawString("Converted to RUSH BUCKS! $$ ", 70, 180);
	system->setTextColor(TFT_WHITE);
	system->drawString("RUSH BUCKS:", 135, 220);
	system->setTextColor(TFT_GREEN);
	system->drawString("$", 275, 220);
	char currencyStr[10];
	sprintf(currencyStr, "%d", gameState.rh_currency);
	system->drawString(currencyStr, 290, 220);

	system->setTextProperties(TFT_YELLOW, 2);
	system->drawString("Returning to Main Menu...", 80, 260);

	system->delay(GAME_OVER_DELAY);

	gameState.score = 0;
	gameState.updateScore = 0;
	gameState.level = INITIAL_LEVEL;
	state->transitionToScreen(RUSH_HOUR_MENU);
}

void RushHourGame::convertScoreToCurrency()
{
	gameState.rh_currency += gameState.score;
}

void RushHourGame::resetEnemyCars()
{
	for (int i = 0; i < MAX_ENEMY_CARS; i++)
	{
		gameState.enemyCars[i].active = false;
		gameState.enemyCars[i].posY = ENEMY_CAR_START_Y;
	}
}

int RushHourGame::getRandomEnemyColor()
{
	return (rand() % 7) + 1;
}

void RushHourGame::updateGameTimer()
{
	gameState.gameTimer++;
}

void RushHourGame::handleMenuNavigation()
{
	const InputState &input = system->getInput();

	if (input.isUp() && state->getCurrentMenuSelection() != 0)
	{
		state->decrementMenuSelection(4);
	}

	if (input.isDown() && state->getCurrentMenuSelection() != 3)
	{
		state->incrementMenuSelection(4);
	}
}