#include "GameState.h"
#include "GameSystem.h"

// Global game state instance
GameState gameState;

// =============================================================================
// CONSTRUCTOR
// =============================================================================
GameState::GameState()
{
	currentScreen = MAIN_MENU;
	previousScreen = MAIN_MENU;
	stayScreen = true;
	currentMenuSelect = 0;
	gameSelected = 0;
	screenNeedsInitialization = true;
}

// =============================================================================
// SCREEN MANAGEMENT
// =============================================================================
void GameState::setScreen(GameScreen screen)
{
	if (currentScreen != screen)
	{
		previousScreen = currentScreen;
		currentScreen = screen;
		stayScreen = true;
		screenNeedsInitialization = true;
		currentMenuSelect = 0; // Reset menu selection when changing screens
	}
}

void GameState::transitionToScreen(GameScreen newScreen)
{
	gameSystem.playSelectSound();
	gameSystem.delay(DEFAULT_REST_DURATION);
	setScreen(newScreen);
}

bool GameState::isTransitioning() const
{
	return screenNeedsInitialization;
}

// =============================================================================
// MENU NAVIGATION
// =============================================================================
void GameState::incrementMenuSelection(int maxOptions)
{
	if (currentMenuSelect < maxOptions - 1)
	{
		currentMenuSelect++;
		gameSystem.playMenuSound();
	}
}

void GameState::decrementMenuSelection(int maxOptions)
{
	if (currentMenuSelect > 0)
	{
		currentMenuSelect--;
		gameSystem.playMenuSound();
	}
}

// =============================================================================
// STATE QUERIES
// =============================================================================
bool GameState::isInGame() const
{
	return (currentScreen == RUSH_HOUR_GAME || currentScreen == JOHNNY_GUN_GAME);
}

bool GameState::isInMenu() const
{
	return !isInGame();
}

bool GameState::isInRushHour() const
{
	return (currentScreen == RUSH_HOUR_GAME ||
			currentScreen == RUSH_HOUR_MENU ||
			currentScreen == RUSH_HOUR_SHOP ||
			currentScreen == SPRAY_CAR ||
			currentScreen == HOW_TO_PLAY_RH);
}

bool GameState::isInJohnnyGun() const
{
	return (currentScreen == JOHNNY_GUN_GAME ||
			currentScreen == JOHNNY_GUN_MENU ||
			currentScreen == HOW_TO_PLAY_JG);
}

// =============================================================================
// UPDATE METHOD
// =============================================================================
void GameState::update()
{
	// This method can be used for any per-frame state management
	// Currently, most state changes are handled reactively through input

	// Handle any time-based state transitions here if needed
}

// =============================================================================
// NAVIGATION HELPERS
// =============================================================================
void GameState::markScreenForRedraw()
{
	stayScreen = true;
	screenNeedsInitialization = true;
}