#ifndef JOHNNY_GUN_H
#define JOHNNY_GUN_H

#include "GameSystem.h"
#include "GameState.h"
#include "UIComponents.h"
#include "GameConstants.h"

// =============================================================================
// JOHNNY GUN GAME STATE
// =============================================================================
struct Enemy
{
	bool active;
	int x;
	int y;
	int timer;
};

struct Bullet
{
	bool active;
	int x;
	int y;
	int velocity;
};

struct JohnnyGunGameState
{
	// Player
	int johnnyX;
	int johnnyY;

	// Shooting system
	Bullet bullet;

	// Enemy system
	Enemy enemies[MAX_ENEMIES];
	int enemyCount;
	int spawnTimer;
	int randomSpawn;

	// Game progression
	int jgScore;
	int jgHighScore;
	int jgScoreCount;
	int johnnyGameTimer;

	// Environment
	uint16_t skyBackground;
	uint16_t groundColor;
	uint16_t platformColor;
	bool lightsOut;
	bool bloodMoon;
};

// =============================================================================
// JOHNNY GUN GAME CLASS
// =============================================================================
class JohnnyGunGame
{
private:
	GameSystem *system;
	GameState *state;
	UIComponents *ui;
	JohnnyGunGameState gameState;

public:
	// Constructor
	JohnnyGunGame(GameSystem *gameSystem = &gameSystem,
				  GameState *gameState = &::gameState,
				  UIComponents *uiComponents = &uiComponents);

	// Initialization
	void initialize();
	void resetGameState();

	// Main game screens
	void showMenu();
	void showGame();
	void showHowToPlay();

	// Game mechanics
	void updateGame();
	void handlePlayerInput();
	void handlePlayerMovement();
	void handleShooting();
	void updateEnemies();
	void updateBullet();
	void checkCollisions();
	void checkBulletEnemyCollisions();
	void checkPlayerEnemyCollisions();
	void updateScore();
	void checkEnvironmentChanges();

	// Entity rendering
	void createJohnny();
	void createEnemy(int x, int y);
	void clearJohnnyShadow();
	void clearEnemyShadow(int x, int y);

	// Enemy management
	void spawnEnemy(int index);
	void updateEnemySpawnTimers();
	void moveEnemies();
	void cleanupOffscreenEnemies();

	// Game state management
	void saveHighScore();
	void gameOver();
	void showGameOverScreen();

	// Environment management
	void updateEnvironment();
	void activateLightsOut();
	void activateBloodMoon();

	// Utility methods
	void resetEnemies();
	void resetBullet();
	int getRandomEnemySpawnY();

	// Getters for external access
	int getCurrentScore() const { return gameState.jgScore; }
	int getHighScore() const { return gameState.jgHighScore; }

private:
	// Internal helper methods
	void initializeGameState();
	void handleMenuNavigation();
	void drawMenuOptions();
	void updateGameTimer();
	bool isJohnnyInBounds(int newX, int newY) const;
	void drawScoreDisplay();
};

#endif // JOHNNY_GUN_H