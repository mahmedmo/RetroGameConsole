#include "GameSystem.h"
#include <Arduino.h>

// Global system instance
GameSystem gameSystem;

// =============================================================================
// INITIALIZATION METHODS
// =============================================================================
void GameSystem::initialize()
{
	Serial.begin(9600);
	initializeButtons();
	initializeDisplay();
	showLoadingScreen();
}

void GameSystem::initializeButtons()
{
	pinMode(JOYSTICK_BUTTON_PIN, INPUT);
	digitalWrite(JOYSTICK_BUTTON_PIN, HIGH);
	pinMode(BUTTON_1, INPUT_PULLUP);
	pinMode(BUTTON_2, INPUT_PULLUP);
	pinMode(BUTTON_3, INPUT_PULLUP);
}

void GameSystem::initializeDisplay()
{
	tft.begin();
	tft.setRotation(1);
	tft.setSwapBytes(false);
}

void GameSystem::showLoadingScreen()
{
	// MOSOWO loading screen
	tft.fillScreen(TFT_BLUE);
	tft.setTextColor(TFT_WHITE);
	tft.setTextSize(20);
	tft.drawString("MOSOWOH", 100, 120);
	tft.setTextSize(3);
	tft.drawString("game studios", 240, 175);

	// Loading music
	playTone(NOTE_B3, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_G3, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_E3, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_D3, DEFAULT_REST_DURATION * 2 - 10);
	delay(DEFAULT_REST_DURATION * 2);

	playLoadingAnimation();

	// Controller layout display
	tft.fillRect(100, 120, 480, 150, TFT_BLUE);
	tft.setTextSize(20);
	tft.fillCircle(140, 120, 50, TFT_RED);
	tft.drawString("B", 125, 95);
	tft.fillCircle(240, 120, 50, TFT_YELLOW);
	tft.drawString("Y", 223, 95);
	tft.fillCircle(340, 120, 50, TFT_GREEN);
	tft.drawString("A", 323, 95);

	// Loading completion music
	playTone(NOTE_D3, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_E3, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_G3, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_B3, DEFAULT_REST_DURATION * 2 - 10);
	delay(DEFAULT_REST_DURATION * 2);
}

void GameSystem::playLoadingAnimation()
{
	int x = 0;
	int count = 0;

	while (true)
	{
		tft.fillCircle(x, 240, 20, TFT_WHITE);
		tft.fillCircle(x - 40, 240, 20, TFT_BLUE);
		x += 5;
		if (x >= 530)
		{
			x = 0;
			count++;
		}
		if (count == 1)
		{
			break;
		}
	}
}

// =============================================================================
// INPUT MANAGEMENT
// =============================================================================
void GameSystem::updateInput()
{
	previousInput = currentInput;

	currentInput.joystickX = analogRead(JOYSTICK_X_PIN);
	currentInput.joystickY = analogRead(JOYSTICK_Y_PIN);
	currentInput.button1Pressed = digitalRead(BUTTON_1) == LOW;
	currentInput.button2Pressed = digitalRead(BUTTON_2) == LOW;
	currentInput.button3Pressed = digitalRead(BUTTON_3) == LOW;
	currentInput.joystickButtonPressed = digitalRead(JOYSTICK_BUTTON_PIN) == LOW;
}

bool GameSystem::isButton1JustPressed() const
{
	return currentInput.button1Pressed && !previousInput.button1Pressed;
}

bool GameSystem::isButton2JustPressed() const
{
	return currentInput.button2Pressed && !previousInput.button2Pressed;
}

bool GameSystem::isButton3JustPressed() const
{
	return currentInput.button3Pressed && !previousInput.button3Pressed;
}

// =============================================================================
// SOUND MANAGEMENT
// =============================================================================
void GameSystem::playTone(int frequency, int duration)
{
	tone(BUZZER_PIN, frequency, duration);
}

void GameSystem::playMenuSound()
{
	playTone(NOTE_A2, 100);
}

void GameSystem::playSelectSound()
{
	playTone(NOTE_C4, DEFAULT_REST_DURATION);
}

void GameSystem::playErrorSound()
{
	playTone(NOTE_C1, DEFAULT_REST_DURATION);
}

void GameSystem::playSuccessSound()
{
	playTone(NOTE_C6, DEFAULT_REST_DURATION);
}

void GameSystem::playGameOverSound()
{
	playTone(NOTE_F2, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_E2, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_DS2, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_D2, 1000);
	delay(1000);
}

void GameSystem::playLevelUpSound()
{
	playTone(NOTE_F5, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_G5, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
	playTone(NOTE_A5, DEFAULT_REST_DURATION - 10);
	delay(DEFAULT_REST_DURATION);
}

void GameSystem::playShootSound()
{
	playTone(NOTE_G1, 100);
}

void GameSystem::playHitSound()
{
	playTone(NOTE_B4, 100);
}

// =============================================================================
// DISPLAY WRAPPER METHODS
// =============================================================================
void GameSystem::clearScreen(uint16_t color)
{
	tft.fillScreen(color);
}

void GameSystem::setTextProperties(uint16_t color, uint8_t size)
{
	tft.setTextColor(color);
	tft.setTextSize(size);
}

void GameSystem::drawRect(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color)
{
	tft.drawRect(x, y, width, height, color);
}

void GameSystem::fillRect(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color)
{
	tft.fillRect(x, y, width, height, color);
}

void GameSystem::drawCircle(int32_t x, int32_t y, int32_t radius, uint16_t color)
{
	tft.drawCircle(x, y, radius, color);
}

void GameSystem::fillCircle(int32_t x, int32_t y, int32_t radius, uint16_t color)
{
	tft.fillCircle(x, y, radius, color);
}

void GameSystem::drawString(const String &text, int32_t x, int32_t y)
{
	tft.drawString(text, x, y);
}

void GameSystem::drawString(const char *text, int32_t x, int32_t y)
{
	tft.drawString(text, x, y);
}

void GameSystem::pushImage(int32_t x, int32_t y, int32_t width, int32_t height, const uint16_t *image)
{
	tft.pushImage(x, y, width, height, image);
}

// =============================================================================
// TIMING UTILITIES
// =============================================================================
void GameSystem::delay(unsigned long ms)
{
	::delay(ms);
}

unsigned long GameSystem::millis()
{
	return ::millis();
}