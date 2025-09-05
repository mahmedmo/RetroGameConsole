#include "UIComponents.h"
#include <stdio.h>

// Global UI components instance
UIComponents uiComponents;

// =============================================================================
// CONSTRUCTOR
// =============================================================================
UIComponents::UIComponents(GameSystem *gameSystem) : system(gameSystem)
{
}

// =============================================================================
// MENU COMPONENTS
// =============================================================================
void UIComponents::drawMenu(const MenuItem *items, int itemCount, int selectedIndex)
{
	for (int i = 0; i < itemCount; i++)
	{
		system->setTextProperties(items[i].textColor, items[i].textSize);
		system->drawString(items[i].text, items[i].x, items[i].y);
	}

	// Draw cursor for selected item
	if (selectedIndex >= 0 && selectedIndex < itemCount)
	{
		int cursorX = items[selectedIndex].x - 25;
		int cursorY = items[selectedIndex].y + (items[selectedIndex].textSize * 4); // Approximate center
		drawMenuCursor(cursorX, cursorY, TFT_WHITE);
	}
}

void UIComponents::drawMenuCursor(int32_t x, int32_t y, uint16_t color, int radius)
{
	system->fillCircle(x, y, radius, color);
}

void UIComponents::clearMenuCursor(int32_t x, int32_t y, uint16_t backgroundColor, int radius)
{
	system->fillCircle(x, y, radius, backgroundColor);
}

// =============================================================================
// SCORE AND CURRENCY DISPLAY
// =============================================================================
void UIComponents::drawScore(const ScoreDisplay &scoreConfig)
{
	char scoreStr[20];
	formatScoreString(scoreConfig.score, scoreStr, sizeof(scoreStr));

	system->setTextProperties(scoreConfig.labelColor, scoreConfig.textSize);
	system->drawString(scoreConfig.label, scoreConfig.x, scoreConfig.y);

	system->setTextProperties(scoreConfig.scoreColor, scoreConfig.textSize);
	system->drawString(scoreStr, scoreConfig.x, scoreConfig.y + (scoreConfig.textSize * 10));
}

void UIComponents::drawCurrency(const CurrencyDisplay &currencyConfig)
{
	char currencyStr[20];
	formatCurrencyString(currencyConfig.amount, currencyStr, sizeof(currencyStr));

	system->setTextProperties(currencyConfig.labelColor, currencyConfig.textSize);
	system->drawString(currencyConfig.label, currencyConfig.x, currencyConfig.y);

	system->setTextProperties(currencyConfig.amountColor, currencyConfig.textSize);
	system->drawString("$", currencyConfig.x + 120, currencyConfig.y);
	system->drawString(currencyStr, currencyConfig.x + 140, currencyConfig.y);
}

void UIComponents::drawHighScore(int32_t score, int32_t x, int32_t y, uint16_t color)
{
	char scoreStr[20];
	formatScoreString(score, scoreStr, sizeof(scoreStr));

	system->setTextProperties(color, 2);
	system->drawString("HIGH SCORE:", x, y);
	system->drawString(scoreStr, x + 130, y);
}

// =============================================================================
// GAME TITLE AND HEADERS
// =============================================================================
void UIComponents::drawGameTitle(const char *title, int32_t x, int32_t y, uint16_t textColor, uint16_t bgColor, uint8_t textSize)
{
	int32_t titleWidth = getTextWidth(title, textSize);
	int32_t titleHeight = getTextHeight(textSize);

	// Draw background rectangle
	system->fillRect(x - 10, y - 10, titleWidth + 20, titleHeight + 20, bgColor);
	system->drawRect(x - 10, y - 10, titleWidth + 20, titleHeight + 20, TFT_BLACK);

	// Draw title text
	system->setTextProperties(textColor, textSize);
	system->drawString(title, x, y);
}

void UIComponents::drawSectionHeader(const char *header, int32_t x, int32_t y, uint16_t color, uint8_t textSize)
{
	system->setTextProperties(color, textSize);
	system->drawString(header, x, y);
}

// =============================================================================
// STATUS AND INFO DISPLAYS
// =============================================================================
void UIComponents::drawPowerUpStatus(int32_t x, int32_t y, int count, uint16_t iconColor, const char *label)
{
	char countStr[10];
	sprintf(countStr, "%d", count);

	// Draw power-up icon (simple circle representation)
	system->fillCircle(x, y, 16, iconColor);
	system->fillCircle(x, y + 8, 8, TFT_WHITE);

	// Draw count
	system->setTextProperties(TFT_WHITE, 2);
	system->drawString(countStr, x + 25, y - 10);
}

void UIComponents::drawLevelIndicator(int level, int32_t x, int32_t y)
{
	char levelStr[10];
	sprintf(levelStr, "Level %d", level);

	system->setTextProperties(TFT_YELLOW, 2);
	system->drawString(levelStr, x, y);
}

void UIComponents::drawTimer(int32_t time, int32_t x, int32_t y, const char *label)
{
	char timeStr[20];
	sprintf(timeStr, "%ld", time);

	system->setTextProperties(TFT_WHITE, 2);
	system->drawString(label, x, y);
	system->drawString(timeStr, x + 60, y);
}

// =============================================================================
// SELECTION AND HIGHLIGHTING
// =============================================================================
void UIComponents::drawSelectionBox(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color, int thickness)
{
	for (int i = 0; i < thickness; i++)
	{
		system->drawRect(x + i, y + i, width - (2 * i), height - (2 * i), color);
	}
}

void UIComponents::clearSelectionBox(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t backgroundColor, int thickness)
{
	for (int i = 0; i < thickness; i++)
	{
		system->drawRect(x + i, y + i, width - (2 * i), height - (2 * i), backgroundColor);
	}
}

// =============================================================================
// COMMON UI ELEMENTS
// =============================================================================
void UIComponents::drawButton(int32_t x, int32_t y, int32_t width, int32_t height, const char *text,
							  uint16_t bgColor, uint16_t textColor, uint16_t borderColor)
{
	// Draw button background
	system->fillRect(x, y, width, height, bgColor);
	system->drawRect(x, y, width, height, borderColor);

	// Draw button text (centered)
	int32_t textX = x + (width - getTextWidth(text, 2)) / 2;
	int32_t textY = y + (height - getTextHeight(2)) / 2;

	system->setTextProperties(textColor, 2);
	system->drawString(text, textX, textY);
}

void UIComponents::drawProgressBar(int32_t x, int32_t y, int32_t width, int32_t height,
								   float percentage, uint16_t fillColor, uint16_t bgColor)
{
	// Draw background
	system->fillRect(x, y, width, height, bgColor);
	system->drawRect(x, y, width, height, TFT_BLACK);

	// Draw fill
	int32_t fillWidth = (int32_t)(width * percentage);
	if (fillWidth > 0)
	{
		system->fillRect(x + 2, y + 2, fillWidth - 4, height - 4, fillColor);
	}
}

// =============================================================================
// GAME-SPECIFIC UI HELPERS
// =============================================================================
void UIComponents::drawCarCustomizationInterface(int32_t previewX, int32_t previewY, uint16_t selectedColor)
{
	// Draw color preview box
	system->fillRect(previewX, previewY, 100, 100, selectedColor);
	system->drawRect(previewX, previewY, 100, 100, TFT_BLACK);

	// Draw navigation arrows
	system->setTextProperties(TFT_WHITE, 5);
	system->drawString("<", previewX - 50, previewY + 40);
	system->drawString(">", previewX + 120, previewY + 40);
}

void UIComponents::drawShopInterface(int32_t currency, const char *itemName, int32_t price, bool canAfford)
{
	char priceStr[20];
	sprintf(priceStr, "$%ld", price);

	uint16_t priceColor = canAfford ? TFT_GREEN : TFT_RED;

	system->setTextProperties(TFT_WHITE, 3);
	system->drawString(itemName, 40, 170);

	system->setTextProperties(priceColor, 3);
	system->drawString(priceStr, 400, 170);
}

// =============================================================================
// MESSAGE DISPLAY
// =============================================================================
void UIComponents::showMessage(const char *message, int32_t x, int32_t y, uint16_t color,
							   uint8_t textSize, int displayTime)
{
	system->setTextProperties(color, textSize);
	system->drawString(message, x, y);

	if (displayTime > 0)
	{
		system->delay(displayTime);
		// Clear message area
		int32_t messageWidth = getTextWidth(message, textSize);
		int32_t messageHeight = getTextHeight(textSize);
		system->fillRect(x, y, messageWidth, messageHeight, TFT_BLACK);
	}
}

void UIComponents::showCenteredMessage(const char *message, uint16_t color, uint8_t textSize)
{
	int32_t messageWidth = getTextWidth(message, textSize);
	int32_t x = (TEXT_AREA_WIDTH - messageWidth) / 2;
	int32_t y = TEXT_AREA_HEIGHT / 2;

	showMessage(message, x, y, color, textSize, 0);
}

void UIComponents::showGameOverScreen(int32_t finalScore, int32_t highScore, bool isNewHighScore)
{
	system->clearScreen(TFT_RED);

	if (isNewHighScore)
	{
		system->setTextProperties(TFT_GREEN, 3);
		system->drawString("NEW HIGH SCORE!", 110, 30);
	}

	system->setTextProperties(TFT_WHITE, 5);
	system->drawString("You LOSE!", 110, 90);

	// Show final score
	char scoreStr[20];
	formatScoreString(finalScore, scoreStr, sizeof(scoreStr));
	system->setTextProperties(TFT_WHITE, 2);
	system->drawString("Score:", 180, 140);
	system->drawString(scoreStr, 255, 140);
}

void UIComponents::showLevelUpScreen(int newLevel)
{
	system->clearScreen(TFT_GREEN);
	system->setTextProperties(TFT_BLACK, 5);
	system->drawString("Next Level!", 90, 140);

	char levelStr[20];
	sprintf(levelStr, "Level %d", newLevel);
	system->drawString(levelStr, 120, 200);
}

// =============================================================================
// INPUT HELPERS
// =============================================================================
void UIComponents::drawControlPrompts(int32_t x, int32_t y)
{
	system->setTextProperties(TFT_WHITE, 2);
	system->drawString("Use joystick to navigate", x, y);
	system->drawString("Press A to select", x, y + 20);
	system->drawString("Press B for back", x, y + 40);
}

void UIComponents::drawBackToMenuPrompt(int32_t x, int32_t y)
{
	system->setTextProperties(TFT_RED, 2);
	system->drawString("Press A to return to menu.", x, y);
}

// =============================================================================
// UTILITY METHODS
// =============================================================================
void UIComponents::formatScoreString(int32_t score, char *buffer, size_t bufferSize)
{
	snprintf(buffer, bufferSize, "%ld", score);
}

void UIComponents::formatCurrencyString(int32_t currency, char *buffer, size_t bufferSize)
{
	snprintf(buffer, bufferSize, "%ld", currency);
}

int32_t UIComponents::getTextWidth(const char *text, uint8_t textSize)
{
	return strlen(text) * 6 * textSize; // Approximate width
}

int32_t UIComponents::getTextHeight(uint8_t textSize)
{
	return 8 * textSize; // Approximate height
}

// =============================================================================
// SCREEN CLEARING AND BACKGROUNDS
// =============================================================================
void UIComponents::drawMenuBackground(uint16_t color)
{
	system->clearScreen(color);
}

void UIComponents::drawGameBackground(uint16_t color)
{
	system->clearScreen(color);
}

void UIComponents::clearArea(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color)
{
	system->fillRect(x, y, width, height, color);
}