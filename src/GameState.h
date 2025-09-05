#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameConstants.h"

// =============================================================================
// GAME STATES ENUM
// =============================================================================
enum GameScreen
{
	MAIN_MENU = SCREEN_MAIN_MENU,
	RUSH_HOUR_GAME = SCREEN_RUSH_HOUR_GAME,
	RUSH_HOUR_MENU = SCREEN_RUSH_HOUR_MENU,
	RUSH_HOUR_SHOP = SCREEN_RUSH_HOUR_SHOP,
	SPRAY_CAR = SCREEN_SPRAY_CAR,
	HOW_TO_PLAY_RH = SCREEN_HOW_TO_PLAY_RH,
	JOHNNY_GUN_GAME = SCREEN_JOHNNY_GUN_GAME,
	JOHNNY_GUN_MENU = SCREEN_JOHNNY_GUN_MENU,
	HOW_TO_PLAY_JG = SCREEN_HOW_TO_PLAY_JG
};

// =============================================================================
// SCREEN STATE MANAGEMENT
// =============================================================================
class GameState
{
private:
	GameScreen currentScreen;
	GameScreen previousScreen;
	bool stayScreen;
	int currentMenuSelect;

	// Selected game on main menu
	int gameSelected;

	// Screen initialization flags
	bool screenNeedsInitialization;

public:
	// Constructor
	GameState();

	// Screen Management
	void setScreen(GameScreen screen);
	GameScreen getCurrentScreen() const { return currentScreen; }
	GameScreen getPreviousScreen() const { return previousScreen; }

	// Screen state management
	bool shouldStayOnScreen() const { return stayScreen; }
	void setStayOnScreen(bool stay) { stayScreen = stay; }
	void markScreenForRedraw() { stayScreen = true; }

	bool needsInitialization() const { return screenNeedsInitialization; }
	void markAsInitialized() { screenNeedsInitialization = false; }

	// Menu selection management
	int getCurrentMenuSelection() const { return currentMenuSelect; }
	void setCurrentMenuSelection(int selection) { currentMenuSelect = selection; }
	void resetMenuSelection() { currentMenuSelect = 0; }

	void incrementMenuSelection(int maxOptions);
	void decrementMenuSelection(int maxOptions);

	// Main menu game selection
	int getSelectedGame() const { return gameSelected; }
	void setSelectedGame(int game) { gameSelected = game; }

	// Update method called each frame
	void update();

	// Screen transition helpers
	void transitionToScreen(GameScreen newScreen);
	bool isTransitioning() const;

	// Screen-specific state queries
	bool isInGame() const;
	bool isInMenu() const;
	bool isInRushHour() const;
	bool isInJohnnyGun() const;
};

// Global game state instance
extern GameState gameState;

#endif // GAME_STATE_H