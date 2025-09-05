#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <stdint.h>

// =============================================================================
// MUSIC NOTE FREQUENCIES
// =============================================================================
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// =============================================================================
// HARDWARE PIN DEFINITIONS
// =============================================================================
#define JOYSTICK_Y_PIN A15
#define JOYSTICK_X_PIN A14
#define JOYSTICK_BUTTON_PIN 47
#define BUTTON_1 8
#define BUTTON_2 9
#define BUTTON_3 10
#define BUZZER_PIN 3

// =============================================================================
// JOYSTICK THRESHOLDS
// =============================================================================
#define JOYSTICK_UP_THRESHOLD 450
#define JOYSTICK_DOWN_THRESHOLD 550
#define JOYSTICK_LEFT_THRESHOLD 450
#define JOYSTICK_RIGHT_THRESHOLD 550

// =============================================================================
// GAME SCREEN CONSTANTS
// =============================================================================
#define SCREEN_MAIN_MENU 1
#define SCREEN_RUSH_HOUR_GAME 2
#define SCREEN_RUSH_HOUR_MENU 3
#define SCREEN_RUSH_HOUR_SHOP 4
#define SCREEN_SPRAY_CAR 5
#define SCREEN_HOW_TO_PLAY_RH 6
#define SCREEN_JOHNNY_GUN_GAME 7
#define SCREEN_JOHNNY_GUN_MENU 8
#define SCREEN_HOW_TO_PLAY_JG 9

// =============================================================================
// RUSH HOUR GAME CONSTANTS
// =============================================================================
#define MAX_ENEMY_CARS 6
#define DEFAULT_CAR_SPEED 5
#define PLAYER_CAR_START_X 250
#define PLAYER_CAR_START_Y 240
#define ENEMY_CAR_START_Y -160
#define CAR_WIDTH 44
#define CAR_HEIGHT 100
#define ROAD_LEFT_BOUNDARY 98
#define ROAD_RIGHT_BOUNDARY 338

// Level progression score thresholds
#define LEVEL_2_SCORE 500
#define LEVEL_3_SCORE 1000
#define LEVEL_4_SCORE 2500
#define LEVEL_5_SCORE 5000
#define LEVEL_6_SCORE 10000
#define LEVEL_7_SCORE 15000
#define LEVEL_8_SCORE 20000
#define LEVEL_9_SCORE 25000

// Power-up prices
#define POINT_MULTIPLIER_BASE_PRICE 500
#define INVINCIBILITY_PRICE 800
#define SLOW_TIME_PRICE 200
#define FLAME_BARRIER_PRICE 1000

// Power-up durations (in game frames)
#define INVINCIBILITY_DURATION 500
#define SLOW_TIME_DURATION 700
#define FLAME_BARRIER_DURATION 500

// Scoring
#define BASE_POINTS_PER_SECOND 10
#define NORMAL_ENEMY_POINTS 100
#define BOSS_ENEMY_POINTS 500

// =============================================================================
// JOHNNY GUN GAME CONSTANTS
// =============================================================================
#define MAX_ENEMIES 10
#define JOHNNY_START_X 20
#define JOHNNY_START_Y 200
#define JOHNNY_WIDTH 30
#define JOHNNY_HEIGHT 40
#define BULLET_VELOCITY 20
#define BULLET_WIDTH 10
#define BULLET_HEIGHT 5
#define ENEMY_WIDTH 30
#define ENEMY_HEIGHT 40
#define ENEMY_POINTS 50

// Environment changes
#define LIGHTS_OUT_SCORE 500
#define BLOOD_MOON_SCORE 1000

// =============================================================================
// TIMING CONSTANTS
// =============================================================================
#define DEFAULT_REST_DURATION 500
#define MENU_NAVIGATION_DELAY 150
#define GAME_OVER_DELAY 5000
#define LEVEL_TRANSITION_DELAY 2000
#define POWERUP_NOTIFICATION_DELAY 1000

// =============================================================================
// UI CONSTANTS
// =============================================================================
#define MENU_CURSOR_SIZE 10
#define TEXT_AREA_WIDTH 480
#define TEXT_AREA_HEIGHT 320
#define SCORE_DISPLAY_X 0
#define SCORE_DISPLAY_Y 0
#define HIGH_SCORE_DISPLAY_X 100
#define HIGH_SCORE_DISPLAY_Y 30

// =============================================================================
// STARTING VALUES
// =============================================================================
#define INITIAL_CURRENCY 8000
#define INITIAL_LEVEL 1
#define INITIAL_POINT_MULTIPLIER 1
#define MAX_POINT_MULTIPLIER 3

#endif // GAME_CONSTANTS_H