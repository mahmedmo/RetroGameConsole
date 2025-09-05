#ifndef RUSH_HOUR_H
#define RUSH_HOUR_H

#include "GameSystem.h"
#include "GameState.h"
#include "UIComponents.h"
#include "GameConstants.h"
#include "sprites.h"

// =============================================================================
// RUSH HOUR GAME STATE
// =============================================================================
struct EnemyCar
{
	bool active;
	uint16_t speed;
	int32_t posY;
	uint16_t posX;
	uint16_t color;
	uint16_t timer;
};

struct PowerUp
{
	int pointMultiplier;
	int invincibility;
	int slowTime;
	int flameBarrier;
	int activePowerUp;
	int powerUpTimer;
};

struct RushHourGameState
{
	// Player car
	uint16_t playerCarColor;
	uint16_t playerWindowTint;
	int playerCarPosX;
	int playerCarPosY;

	// Enemy cars
	EnemyCar enemyCars[MAX_ENEMY_CARS];
	int carSpawnTimer;

	// Game progression
	int level;
	int64_t score;
	int rh_highScore;
	int updateScore;
	int gameTimer;
	int maxCars;
	int rh_currency;
	int endGameTimer;
	bool levelChanged;
	int rh_speed;

	// Power-ups
	PowerUp powerUps;

	// Level boundaries
	int carLeftEnd;
	int carRightEnd;

	// Color customization
	int16_t colorWheel[21];
	int16_t colorIndex;

	// Prices
	int pointMultiPrice;
	int invincPrice;
	int slowTimePrice;
	int flameBarrPrice;

	// UI state
	bool reset;
};

// =============================================================================
// RUSH HOUR GAME CLASS
// =============================================================================
class RushHourGame
{
private:
	GameSystem *system;
	GameState *state;
	UIComponents *ui;
	RushHourGameState gameState;

public:
	// Constructor
	RushHourGame(GameSystem *gameSystem = &gameSystem,
				 GameState *gameState = &::gameState,
				 UIComponents *uiComponents = &uiComponents);

	// Initialization
	void initialize();
	void resetGameState();

	// Main game screens
	void showMenu();
	void showGame();
	void showShop();
	void showHowToPlay();
	void showCarCustomization();

	// Game mechanics
	void updateGame();
	void handlePlayerInput();
	void updateEnemyCars();
	void checkCollisions();
	void updateScore();
	void checkLevelProgression();
	void handlePowerUps();

	// Car rendering
	void paintPlayerCar();
	void loadEnemyCar(uint16_t posX, uint16_t posY, uint16_t color);

	// Level management
	void createLevel();
	void transitionToNextLevel();

	// Shop system
	void handleShopInput();
	void purchaseItem(int itemIndex);
	bool canAffordItem(int itemIndex);
	void updateShopDisplay();

	// Car customization
	void handleCustomizationInput();
	void updateColorSelection();
	void purchaseCustomization(bool isTint);

	// Power-up system
	void activatePowerUp(int powerUpType);
	void updateActivePowerUp();
	bool isPowerUpActive(int powerUpType) const;

	// Game state management
	void saveHighScore();
	void gameOver();
	void showGameOverScreen();

	// Utility methods
	void initializeColorWheel();
	void resetEnemyCars();
	void spawnEnemyCar(int index);
	int getRandomEnemyColor();

	// Getters for external access
	int getCurrentScore() const { return gameState.score; }
	int getHighScore() const { return gameState.rh_highScore; }
	int getCurrentLevel() const { return gameState.level; }
	int getCurrency() const { return gameState.rh_currency; }

private:
	// Internal helper methods
	void initializeGameState();
	void updateGameTimer();
	void handleMenuNavigation();
	void drawMenuOptions();
	void drawShopItems();
	void drawPowerUpDisplay();
	void drawCarPreview();
	void calculateCarBoundaries();
	void playLevelMusic();
	void convertScoreToCurrency();
};

#endif // RUSH_HOUR_H