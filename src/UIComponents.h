#ifndef UI_COMPONENTS_H
#define UI_COMPONENTS_H

#include <TFT_eSPI.h>
#include "GameSystem.h"
#include "GameConstants.h"

// =============================================================================
// UI COMPONENT STRUCTURES
// =============================================================================
struct MenuItem
{
	const char *text;
	uint16_t textColor;
	int32_t x;
	int32_t y;
	uint8_t textSize;
};

struct ScoreDisplay
{
	int32_t score;
	int32_t x;
	int32_t y;
	const char *label;
	uint16_t labelColor;
	uint16_t scoreColor;
	uint8_t textSize;
};

struct CurrencyDisplay
{
	int32_t amount;
	int32_t x;
	int32_t y;
	const char *label;
	uint16_t labelColor;
	uint16_t amountColor;
	uint8_t textSize;
};

// =============================================================================
// UI COMPONENTS CLASS
// =============================================================================
class UIComponents
{
private:
	GameSystem *system;

public:
	// Constructor
	UIComponents(GameSystem *gameSystem = &gameSystem);

	// Menu Components
	void drawMenu(const MenuItem *items, int itemCount, int selectedIndex);
	void drawMenuCursor(int32_t x, int32_t y, uint16_t color, int radius = MENU_CURSOR_SIZE);
	void clearMenuCursor(int32_t x, int32_t y, uint16_t backgroundColor, int radius = MENU_CURSOR_SIZE);

	// Score and Currency Display
	void drawScore(const ScoreDisplay &scoreConfig);
	void drawCurrency(const CurrencyDisplay &currencyConfig);
	void drawHighScore(int32_t score, int32_t x, int32_t y, uint16_t color = TFT_WHITE);

	// Game Title and Headers
	void drawGameTitle(const char *title, int32_t x, int32_t y, uint16_t textColor, uint16_t bgColor, uint8_t textSize = 5);
	void drawSectionHeader(const char *header, int32_t x, int32_t y, uint16_t color = TFT_WHITE, uint8_t textSize = 3);

	// Status and Info Displays
	void drawPowerUpStatus(int32_t x, int32_t y, int count, uint16_t iconColor, const char *label);
	void drawLevelIndicator(int level, int32_t x, int32_t y);
	void drawTimer(int32_t time, int32_t x, int32_t y, const char *label = "TIME:");

	// Selection and Highlighting
	void drawSelectionBox(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color, int thickness = 2);
	void clearSelectionBox(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t backgroundColor, int thickness = 2);

	// Common UI Elements
	void drawButton(int32_t x, int32_t y, int32_t width, int32_t height, const char *text,
					uint16_t bgColor, uint16_t textColor, uint16_t borderColor = TFT_BLACK);
	void drawProgressBar(int32_t x, int32_t y, int32_t width, int32_t height,
						 float percentage, uint16_t fillColor, uint16_t bgColor);

	// Game-specific UI helpers
	void drawCarCustomizationInterface(int32_t previewX, int32_t previewY, uint16_t selectedColor);
	void drawShopInterface(int32_t currency, const char *itemName, int32_t price, bool canAfford);

	// Message Display
	void showMessage(const char *message, int32_t x, int32_t y, uint16_t color = TFT_WHITE,
					 uint8_t textSize = 2, int displayTime = 2000);
	void showCenteredMessage(const char *message, uint16_t color = TFT_WHITE, uint8_t textSize = 3);
	void showGameOverScreen(int32_t finalScore, int32_t highScore, bool isNewHighScore);
	void showLevelUpScreen(int newLevel);

	// Input Helpers
	void drawControlPrompts(int32_t x, int32_t y);
	void drawBackToMenuPrompt(int32_t x = 50, int32_t y = 250);

	// Utility Methods
	void formatScoreString(int32_t score, char *buffer, size_t bufferSize);
	void formatCurrencyString(int32_t currency, char *buffer, size_t bufferSize);
	int32_t getTextWidth(const char *text, uint8_t textSize = 1);
	int32_t getTextHeight(uint8_t textSize = 1);

	// Screen clearing and backgrounds
	void drawMenuBackground(uint16_t color = TFT_DARKGREY);
	void drawGameBackground(uint16_t color = TFT_BLACK);
	void clearArea(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color);
};

// Global UI components instance
extern UIComponents uiComponents;

#endif // UI_COMPONENTS_H