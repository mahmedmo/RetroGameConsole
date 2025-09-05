#include "GameSystem.h"
#include "GameState.h"
#include "UIComponents.h"
#include "RushHour.h"
#include "JohnnyGun.h"
#include "sprites.h"

// =============================================================================
// GLOBAL GAME INSTANCES
// =============================================================================
RushHourGame rushHourGame;
JohnnyGunGame johnnyGunGame;

// =============================================================================
// MAIN MENU FUNCTIONS
// =============================================================================
void showMainMenu()
{
	if (gameState.needsInitialization())
	{
		gameState.resetMenuSelection();
		uiComponents.drawMenuBackground(TFT_BLUE);

		// Game covers
		system.fillRect(30, 70, 200, 200, TFT_DARKGREY);
		system.pushImage(107, 110, 44, 100, bossCar);
		system.pushImage(63, 110, 44, 100, orangeCar);
		system.pushImage(151, 110, 44, 100, purpleCar);

		system.setTextProperties(TFT_WHITE, 5);
		system.drawString("GAME SELECT", 30, 10);

		// RUSH HOUR COVER
		system.setTextProperties(TFT_YELLOW, 3);
		system.drawString("RUSH HOUR", 50, 100);

		// JOHNNY GUN COVER
		system.fillRect(250, 70, 200, 200, TFT_BLACK);
		system.setTextProperties(TFT_RED, 3);
		system.drawString("JOHNNY GUN", 260, 100);

		// Draw Johnny on cover
		int johnnyX = 335;
		int johnnyY = 150;
		system.fillRect(johnnyX, johnnyY, 30, 40, TFT_MAROON);
		system.fillRect(johnnyX, johnnyY - 5, 30, 5, TFT_SKYBLUE);
		system.fillRect(johnnyX, johnnyY, 35, 5, TFT_SKYBLUE);
		system.fillRect(johnnyX + 5, johnnyY + 5, 5, 10, TFT_WHITE);
		system.fillRect(johnnyX + 15, johnnyY + 5, 5, 10, TFT_WHITE);

		gameState.markAsInitialized();
	}

	handleMainMenuInput();
}

void handleMainMenuInput()
{
	const InputState &input = system.getInput();

	if (input.isRight())
	{
		system.playMenuSound();
		gameState.setSelectedGame(1);
	}

	if (input.isLeft())
	{
		system.playMenuSound();
		gameState.setSelectedGame(0);
		int count = 0;
	}

	// Draw selection boxes
	if (gameState.getSelectedGame() == 1)
	{
		uiComponents.drawSelectionBox(250, 70, 200, 200, TFT_WHITE, 12);
		uiComponents.clearSelectionBox(30, 70, 200, 200, TFT_NAVY, 12);
	}

	if (gameState.getSelectedGame() == 0)
	{
		uiComponents.drawSelectionBox(30, 70, 200, 200, TFT_WHITE, 12);
		uiComponents.clearSelectionBox(250, 70, 200, 200, TFT_NAVY, 12);
	}

	if (system.isButton1JustPressed())
	{
		if (gameState.getSelectedGame() == 0)
		{
			system.playSelectSound();
			gameState.setScreen(RUSH_HOUR_MENU);
		}
		if (gameState.getSelectedGame() == 1)
		{
			system.playSelectSound();
			gameState.setScreen(JOHNNY_GUN_MENU);
		}
	}
}

// =============================================================================
// SCREEN MANAGER
// =============================================================================
void updateCurrentScreen()
{
	GameScreen currentScreen = gameState.getCurrentScreen();

	switch (currentScreen)
	{
	case MAIN_MENU:
		showMainMenu();
		break;

	case RUSH_HOUR_MENU:
		rushHourGame.showMenu();
		break;

	case RUSH_HOUR_GAME:
		rushHourGame.showGame();
		break;

	case RUSH_HOUR_SHOP:
		rushHourGame.showShop();
		break;

	case SPRAY_CAR:
		rushHourGame.showCarCustomization();
		break;

	case HOW_TO_PLAY_RH:
		rushHourGame.showHowToPlay();
		break;

	case JOHNNY_GUN_MENU:
		johnnyGunGame.showMenu();
		break;

	case JOHNNY_GUN_GAME:
		johnnyGunGame.showGame();
		break;

	case HOW_TO_PLAY_JG:
		johnnyGunGame.showHowToPlay();
		break;

	default:
		// Fallback to main menu
		gameState.setScreen(MAIN_MENU);
		break;
	}
}

// =============================================================================
// ARDUINO SETUP AND LOOP
// =============================================================================
void setup()
{
	// Initialize all systems
	system.initialize();

	// Set initial state
	gameState.setScreen(MAIN_MENU);

	// Initialize game modules
	rushHourGame.initialize();
	johnnyGunGame.initialize();
}

void loop()
{
	// Update input system
	system.updateInput();

	// Update game state
	gameState.update();

	// Update current screen
	updateCurrentScreen();
}