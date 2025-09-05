#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include <TFT_eSPI.h>
#include "GameConstants.h"

// =============================================================================
// INPUT STRUCTURE
// =============================================================================
struct InputState
{
	int joystickX;
	int joystickY;
	bool button1Pressed;
	bool button2Pressed;
	bool button3Pressed;
	bool joystickButtonPressed;

	// Convenience methods for directional input
	bool isUp() const { return joystickY > JOYSTICK_DOWN_THRESHOLD; }
	bool isDown() const { return joystickY < JOYSTICK_UP_THRESHOLD; }
	bool isLeft() const { return joystickX < JOYSTICK_LEFT_THRESHOLD; }
	bool isRight() const { return joystickX > JOYSTICK_RIGHT_THRESHOLD; }
};

// =============================================================================
// GAME SYSTEM CLASS
// =============================================================================
class GameSystem
{
private:
	TFT_eSPI tft;
	InputState currentInput;
	InputState previousInput;

public:
	// Initialization
	void initialize();
	void showLoadingScreen();

	// Display Management
	TFT_eSPI &getDisplay() { return tft; }
	void clearScreen(uint16_t color = TFT_BLACK);
	void setTextProperties(uint16_t color, uint8_t size);

	// Input Management
	void updateInput();
	const InputState &getInput() const { return currentInput; }
	const InputState &getPreviousInput() const { return previousInput; }

	// Button edge detection (for single press detection)
	bool isButton1JustPressed() const;
	bool isButton2JustPressed() const;
	bool isButton3JustPressed() const;

	// Sound Management
	void playTone(int frequency, int duration);
	void playMenuSound();
	void playSelectSound();
	void playErrorSound();
	void playSuccessSound();
	void playGameOverSound();
	void playLevelUpSound();
	void playShootSound();
	void playHitSound();

	// Timing utilities
	void delay(unsigned long ms);
	unsigned long millis();

	// Common drawing utilities
	void drawRect(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color);
	void fillRect(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color);
	void drawCircle(int32_t x, int32_t y, int32_t radius, uint16_t color);
	void fillCircle(int32_t x, int32_t y, int32_t radius, uint16_t color);
	void drawString(const String &text, int32_t x, int32_t y);
	void drawString(const char *text, int32_t x, int32_t y);

	// Sprite drawing
	void pushImage(int32_t x, int32_t y, int32_t width, int32_t height, const uint16_t *image);

private:
	void initializeButtons();
	void initializeDisplay();
	void playLoadingAnimation();
};

// Global system instance
extern GameSystem gameSystem;

#endif // GAME_SYSTEM_H