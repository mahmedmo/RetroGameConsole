//LIBRARIES
  #include <TFT_eSPI.h>
  #include "sprites.h"
//MUSIC
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
//COMPONENTS
  #define JOYSTICK_Y_PIN A15
  #define JOYSTICK_X_PIN A14
  #define JOYSTICK_BUTTON_PIN 47
  #define button1 8
  #define button2 9
  #define button3 10

//RUSH HOUR
  uint16_t playerCarColor = TFT_YELLOW;
  uint16_t playerWindowTint = TFT_SKYBLUE;
  bool enemyCars[6]={false,false,false,false,false,false};
  uint16_t enemyCarSpeed[6]={5,5,5,5,5,5};
  int32_t enemyCarPosY[6]={-160,-160,-160,-160,-160,-160};
  uint16_t enemyCarPosX[6]={186,250,142,294,98,338};
  uint16_t enemyCarColor[6]={0,0,0,0,0,0};
  uint16_t enemyCarTimers[6]={0,0,0,0,0,0};
  //POWER UPS
    int pointMulti = 1;
    int invinc = 0;
    int slowTime = 0;
    int flameBarr = 0;
    int powerUp = 0;
    int powerUpTimer = 0;

    char pointMultiStr[10];
    char invincStr[10];
    char slowTimeStr[10];
    char flameBarrStr[10];
    int carSpawnTimer =0;
    //Prices
      int pointMultiPrice = 500;
      int invincPrice = 800;
      int slowTimePrice = 200;
      int flameBarrPrice = 1000;

      char pointMultiPriceStr[10];
      char invincPriceStr[10];
      char slowTimePriceStr[10];
      char flameBarrPriceStr[10];
  int16_t colorWheel[21] = {TFT_BLACK,TFT_NAVY,TFT_DARKGREEN,TFT_DARKCYAN,TFT_MAROON,TFT_PURPLE,TFT_OLIVE,TFT_BLUE,TFT_GREEN,TFT_CYAN,TFT_RED,TFT_MAGENTA,TFT_YELLOW,TFT_WHITE,TFT_ORANGE,TFT_GREENYELLOW,TFT_PINK,TFT_BROWN,TFT_GOLD,TFT_SILVER,TFT_VIOLET};
  int16_t colorIndex = 0;
  int rh_highScore = 0;
  char rh_highScoreStr[10];
  int level = 1;
  int carLeftEnd;
  int carRightEnd;
  int64_t score = 0;
  int endGameTimer = 0;
  int updateScore =0;
  char scoreStr[10];
  char currencyStr[10];
  int gameTimer = 0;
  int maxCars = 2;
  int rh_currency = 8000;
  int playerCarPosX = 250;
  int playerCarPosY = 240;
  int enemySpeed = 2;
  int enemyPosY = 0;
  bool levelChanged = false;
  int rh_speed = 1;

//JOHNNY GUN
  bool shootActive = false;
  int johnnyX = 0;
  int johnnyY = 0;
  int bulletX = 0;
  int bulletY = 0;
  int bulletVelocity = 20;
  int enemyTimer[10]={0,0,0,0,0,0,0,0,0,0};
  bool enemies[10]={false,false,false,false,false,false,false,false,false,false};
  int enemiesX[10]={0,0,0,0,0,0,0,0,0,0};
  int enemiesY[10]={0,0,0,0,0,0,0,0,0,0};
  int enemyCount =0;
  int johnnyGameTimer = 0;
  uint16_t skyBackground  = TFT_RED;
  uint16_t groundColor  = TFT_DARKGREEN;
  uint16_t platformColor  = TFT_DARKGREEN;
  int jgScore = 0;
  char jgScoreStr[10];
  char jgHighScoreStr[10];
  int jgHighScore = 0;
  int jgScoreCount = 0;
  int spawnTimer = 0;
  int randomSpawn = 0;
  int lightsOut = false;
  int bloodMoon = false;
//SYSTEM
  TFT_eSPI tft = TFT_eSPI();
  bool reset = false;
  int currentMenuSelect = 0;
  int playerSpeed = 0;
  int x = 0;
  int count = 0;
  int screen = 1;
  int gameSelected = 0;
  int rest = 500;
  bool stayScreen = true;
  int joystickx = 0;
  int joysticky = 0;
  int selectedX = 30;
  int selectedY = 70;




void setup() {
  Serial.begin(9600);
  //buttons+joystick
  pinMode(JOYSTICK_BUTTON_PIN, INPUT);
  digitalWrite(JOYSTICK_BUTTON_PIN, HIGH);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  //initialization
  tft.begin();
  tft.setRotation(1);
  tft.setSwapBytes(false);
  //loading screen
  tft.fillScreen(TFT_BLUE);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(20);
  tft.drawString("MOSOWOH", 100, 120);
  tft.setTextSize(3);
  tft.drawString("game studios", 240, 175);
    rest = 500;
    tone(3,NOTE_B3,rest-10);
    delay(rest);
    tone(3,NOTE_G3,rest-10);
    delay(rest);
    tone(3,NOTE_E3,rest-10);
    delay(rest);
    tone(3,NOTE_D3,rest*2-10);
    delay(rest*2);

  

  while (true) {
    tft.fillCircle(x, 240, 20, TFT_WHITE);
    tft.fillCircle(x - 40, 240, 20, TFT_BLUE);
    x = x + 5;
    if (x >= 530) {
      x = 0;
      count++;
    };
    if (count == 1) {
      break;
    }
  }
  tft.fillRect(100,120,480,150,TFT_BLUE);
  tft.setTextSize(20);
  tft.fillCircle(140,120,50,TFT_RED);
  tft.drawString("B",125,95);
  tft.fillCircle(240,120,50,TFT_YELLOW);;
  tft.drawString("Y",223,95);
  tft.fillCircle(340,120,50,TFT_GREEN);
  tft.drawString("A",323,95);
  
    rest = 500;
    tone(3,NOTE_D3,rest-10);
    delay(rest);
    tone(3,NOTE_E3,rest-10);
    delay(rest);
    tone(3,NOTE_G3,rest-10);
    delay(rest);
    tone(3,NOTE_B3,rest*2-10);
    delay(rest*2);
}
void selectedGame(int32_t x, int32_t y, int thickness, uint16_t color) {
  count = 0;
  while (thickness > 0) {
    tft.drawRect(x + count, y + count, 200 - (2 * count), 200 - (2 * count), color);
    count++;
    thickness--;
  }
}
void gameMenu() {
  //all the games essentially the home screen
  if (stayScreen == true) {
    tft.fillScreen(TFT_BLUE);
    tft.fillRect(30, 70, 200, 200, TFT_DARKGREY);
    tft.pushImage(107, 110,44,100,bossCar);
    tft.pushImage(63, 110,44,100,orangeCar);
    tft.pushImage(151, 110,44,100,purpleCar);
    tft.setTextSize(5);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("GAME SELECT", 30, 10);
    //RUSH HOUR COVER
    tft.setTextSize(3);
    tft.setTextColor(TFT_YELLOW);
    tft.drawString("RUSH HOUR", 50, 100);
    stayScreen = false;
    //GAME 2 COVER
    tft.fillRect(250, 70, 200, 200, TFT_BLACK);
    tft.setTextSize(3);
    tft.setTextColor(TFT_RED);
    tft.drawString("JOHNNY GUN", 260, 100);
    johnnyX = 335;
    johnnyY = 150;
    createJohnny();
  }
  //selectedGame(selectedX,selectedY,16);
  if (joystickx > 700) {
    //selectedX =
    //selectedY =
    tone(3,NOTE_A2,100);
    gameSelected = 1;
  }
  
  if (joystickx < 300) {
    //selectedGame(30,70,16);
    tone(3,NOTE_A2,100);
    gameSelected = 0;
    count =0;
  }
  if (gameSelected == 1) {
    selectedGame(250, 70, 12,TFT_WHITE);
    selectedGame(30, 70, 12,TFT_NAVY);
  }
  if (gameSelected == 0) {
    selectedGame(30, 70, 12,TFT_WHITE);
    selectedGame(250, 70, 12,TFT_NAVY);
  }
  if (digitalRead(button1) == LOW) {
    if (gameSelected == 0) {
      tone(3,NOTE_C4,rest);
      delay(rest);
      screen = 3;
      stayScreen = true;
    }
    if (gameSelected == 1) {
      tone(3,NOTE_C4,rest);
      delay(rest);
      screen = 8;
      stayScreen = true;
    }
  }
}
void createJohnny(){
  tft.fillRect(johnnyX,johnnyY,30,40,TFT_MAROON);  
  tft.fillRect(johnnyX,johnnyY-5,30,5,TFT_SKYBLUE);  
  tft.fillRect(johnnyX,johnnyY,35,5,TFT_SKYBLUE);  
  tft.fillRect(johnnyX+5,johnnyY+5,5,10,TFT_WHITE);  
  tft.fillRect(johnnyX+15,johnnyY+5,5,10,TFT_WHITE);  
}
void createEnemy(int x,int y){
  tft.fillRect(x,y,30,40,TFT_BLACK);  
  tft.fillRect(x+5,y+5,5,10,TFT_RED);  
  tft.fillRect(x+15,y+5,5,10,TFT_RED);  
}
void johnnyShadow(){
  tft.fillRect(johnnyX,johnnyY-5,50,85,skyBackground);  
  
}
void johnnyGunMenu(){
   if (stayScreen == true) {
     bloodMoon = false;
     lightsOut = false;
     currentMenuSelect =0;
     tft.fillScreen(TFT_BLACK);
     tft.setTextSize(2);
     tft.setTextColor(TFT_RED);
     tft.drawString("HIGH SCORE:",100,30);
     sprintf(jgHighScoreStr, "%d", jgHighScore);
     tft.drawString(jgHighScoreStr,235,30);
     tft.setTextColor(TFT_BLACK);
     tft.setTextSize(5);
     tft.fillRect(90,60,300,75,TFT_RED);
     tft.drawRect(90,60,300,75,TFT_MAROON);
     tft.drawString("JOHNNY GUN",90,80);
     tft.setTextSize(3);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("PLAY",205,160);
     tft.drawString("HOW TO PLAY",145,200);
     tft.drawString("EXIT",205,240);
     stayScreen = false;
  }
  if(joysticky>550 && currentMenuSelect!= 0){
      
      currentMenuSelect--;
      tone(3,NOTE_A2,100);
  }
  if(joysticky<450 && currentMenuSelect!= 2){
      currentMenuSelect++;
      tone(3,NOTE_A2,100);
  }
  if(currentMenuSelect == 0){
   tft.fillCircle(115, 210, 10, TFT_BLACK);
   tft.fillCircle(180, 250, 10, TFT_BLACK);
   
   
   tft.fillCircle(180, 170, 10, TFT_RED);
  }
  if(currentMenuSelect == 1){
    tft.fillCircle(180, 170, 10, TFT_BLACK);
    tft.fillCircle(180, 250, 10, TFT_BLACK);
    

    tft.fillCircle(115, 210, 10, TFT_RED);
  }
  if(currentMenuSelect == 2){
    tft.fillCircle(115, 210, 10, TFT_BLACK);
    tft.fillCircle(180, 170, 10, TFT_BLACK);
    

    tft.fillCircle(180, 250, 10, TFT_RED);
  }
 
  if(currentMenuSelect == 0 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    stayScreen = true;
    screen = 7;
  }
  if(currentMenuSelect == 1 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    stayScreen = true;
    currentMenuSelect = 0;
    screen = 9;
    return;
  }
  if(currentMenuSelect == 2 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    stayScreen = true;
    screen = 1;
    
  }
  delay(150);
}
void howToPlayJG(){
  if (stayScreen == true) {
     tft.fillScreen(TFT_BLACK);
     tft.setTextSize(5);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("HOW TO PLAY",75,60);
     tft.setTextSize(2);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("Oh no! Johnny is TRAPPED in the woods..",0,120);
     tft.drawString("DODGE the HEX or SHOOT them to survive",0,150);
     tft.drawString("and gain points!",0,180);
     tft.setTextColor(TFT_RED);
     tft.drawString("Press A to return to game menu.",50,220);
    
     stayScreen = false;
  }  
  if(digitalRead(button1) == LOW){
    tone(3,NOTE_C4,rest);
    delay(rest);
    screen = 8;
    stayScreen = true;
  }
}
void johnnyGunGame() {
  if (stayScreen == true) {
    johnnyX = 20;
    johnnyY=200;
    if(lightsOut == false ){
      jgScore = 0;
    }
    
    johnnyGameTimer = 0;
    spawnTimer = 500;
    shootActive = false;
    enemyCount = -1;
    for(int i = 0; i <10; i++){
      enemyTimer[i]= (rand() %
          (spawnTimer - 0 + 1)) + 0;
    }
    tft.fillScreen(skyBackground);
    //tft.fillRect(0,280,480,40,groundColor);
    createJohnny();      
    tft.setTextSize(2);
    tft.fillRect(0,0,60,40,skyBackground);
    sprintf(jgScoreStr, "%d", jgScore);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("SCORE:",0,0);
    tft.drawString(jgScoreStr,0,20);
    
    stayScreen = false;
    
  } 
    //SCORE
      if(jgScore >= 500 && lightsOut == false){
        skyBackground = TFT_BLACK;
        lightsOut = true;
        stayScreen = true;
      }
      if(jgScore >= 1000 && bloodMoon == false){
        skyBackground = TFT_MAROON;
        bloodMoon = true;
        stayScreen = true;
      }
  
    
    if(johnnyGameTimer >= 500){
      johnnyGameTimer = 0;
    }
    for(int i = 0; i <10; i++){
      if(johnnyGameTimer == enemyTimer[i]){
        enemies[i] = true;        
        enemiesX[i] = 510;
        enemiesY[i] = (rand() % (320 - 0 + 1)) + 0;
      }       
      if(enemies[i]==true){
        tft.fillRect(enemiesX[i],enemiesY[i],30,40,skyBackground);  
        tft.fillRect(enemiesX[i]+5,enemiesY[i]+5,5,10,skyBackground);  
        tft.fillRect(enemiesX[i]+15,enemiesY[i]+5,5,10,skyBackground);  
        enemiesX[i] = enemiesX[i] - 10;
        tft.fillRect(enemiesX[i],enemiesY[i],30,40,TFT_BLACK);  
        tft.fillRect(enemiesX[i]+5,enemiesY[i]+5,5,10,TFT_RED);  
        tft.fillRect(enemiesX[i]+15,enemiesY[i]+5,5,10,TFT_RED);  
        
      } 
      if(enemiesX[i]<-30){
        enemies[i]= false;
        
      } 
      if(enemies[i]== false){
          enemyTimer[i]= (rand() %
          (spawnTimer - 0 + 1)) + 0;        
      }
      if(enemies[i] == true && johnnyX < enemiesX[i] && enemiesX[i]< johnnyX+30 && johnnyY < enemiesY[i] && enemiesY[i] < johnnyY+40){
          rest=500;
          tone(3,NOTE_F2,rest-10);
          delay(rest);
          tone(3,NOTE_E2,rest-10);
          delay(rest);
          tone(3,NOTE_DS2,rest-10);
          delay(rest);
          tone(3,NOTE_D2,1000);
          delay(1000);
          tft.fillScreen(TFT_BLACK);
          // you lose 
          if(jgScore>=jgHighScore){
            jgHighScore = jgScore;
            tft.setTextSize(3);
            tft.setTextColor(TFT_GREEN);
            tft.drawString("NEW HIGH SCORE!",110,30);
          }
          tft.setTextColor(TFT_RED);
          tft.setTextSize(5);
          tft.drawString("You LOSE!",110,90);
          //purge all enemy cars
          for(uint16_t i =0; i<10; i++){
            enemies[i]=false;
            enemiesX[i]=510;
          }    
          //reset johnny
           johnnyX = 20;
           johnnyY=200;
        
          //MENU OPTIONS returns to menu
          tft.setTextSize(3);
          sprintf(jgScoreStr, "%d", jgScore);
          tft.setTextSize(2);
          tft.drawString("Score:",180,140);
          tft.drawString(jgScoreStr,255,140);
          tft.setTextColor(TFT_RED);
          tft.drawString("Returning to Main Menu...",100,220);
          delay(5000);  
          screen = 8;
          stayScreen = true;
          
      }
      if(enemies[i]== true && enemiesX[i] < bulletX && bulletX < enemiesX[i]+30 && enemiesY[i] < bulletY && bulletY < enemiesY[i]+40 && shootActive == true){
        shootActive = false;
        tone(3,NOTE_C4,rest);
        tft.setTextSize(2);
        tft.fillRect(0,0,60,40,skyBackground);
        jgScore = jgScore + 50;
        sprintf(jgScoreStr, "%d", jgScore);
        tft.setTextColor(TFT_WHITE);
        tft.drawString("SCORE:",0,0);
        tft.drawString(jgScoreStr,0,20);
        tft.fillRect(bulletX,bulletY,10,5,skyBackground);
        tft.fillRect(bulletX,bulletY,10,5,skyBackground);
        tft.fillRect(enemiesX[i],enemiesY[i],30,40,skyBackground);  
        tft.fillRect(enemiesX[i]+5,enemiesY[i]+5,5,10,skyBackground);  
        tft.fillRect(enemiesX[i]+15,enemiesY[i]+5,5,10,skyBackground);  
        enemies[i] = false;
        enemiesX[i] = 0;
        enemiesY[i] = 0;
      }
    }
    //SHOOTING
    if(digitalRead(button1) == LOW && shootActive == false){
      tone(3,NOTE_G1,100);
      bulletX = johnnyX +30;
      bulletY = johnnyY+10;
      shootActive = true;
    }
    if(shootActive == true){
      tft.fillRect(bulletX,bulletY,10,5,skyBackground);
      bulletX = bulletX+bulletVelocity;  
      tft.fillRect(bulletX,bulletY,10,5,TFT_YELLOW);
    }
    if(bulletX>=480){
      shootActive = false;
    }
     //MULTI DIRECTIONAL
     if (joysticky > 550 && johnnyY-35 >=0 && joystickx > 550 && johnnyX+25 <= 480) {
      johnnyShadow(); 
      johnnyY=johnnyY-10;
      johnnyX=johnnyX+10;
      createJohnny();
     
    }
    if (joysticky > 550 && johnnyY-35 >= 0 && joystickx < 450 && johnnyX-25 >= 0) {
      johnnyShadow(); 
      johnnyY=johnnyY-10;
      johnnyX=johnnyX-10;
      createJohnny();
    }
    if (joysticky < 450 && johnnyY+35 <= 320 && joystickx > 550 && johnnyX+25 <= 480) {
      johnnyShadow(); 
      johnnyY=johnnyY+10;
      johnnyX=johnnyX+10;
      createJohnny();
     
    }
    if (joysticky < 450 && johnnyY+35 <= 320 && joystickx < 450 && johnnyX-25 >= 0) {
      johnnyShadow(); 
      johnnyY=johnnyY+10;
      johnnyX=johnnyX-10;
      createJohnny();
    }
    //ONE DIRECTIONAL
     if (joystickx < 450 && johnnyX-25 >= 0) {
      johnnyShadow(); 
      johnnyX=johnnyX-10;
      createJohnny();      
     
    }
     if (joystickx > 550 && johnnyX+25 <= 480) {
      johnnyShadow(); 
      johnnyX=johnnyX+10;
      createJohnny();
     
    }
    if (joysticky < 450 && johnnyY-35 >= 0) {
      johnnyShadow(); 
      johnnyY=johnnyY+10;
      createJohnny();
     
    }
    if (joysticky > 550 && johnnyY+35 <= 320) {
      johnnyShadow(); 
      johnnyY=johnnyY-10;
      createJohnny();
     
    }
    
    
    johnnyGameTimer++;
}

void levelCreate(){
    if(level == 1){
      gameTimer = 0;
      tft.fillScreen(TFT_DARKGREEN);
      tft.fillRect(166, 0, 20, 320, TFT_WHITE);
      tft.fillRect(186, 0, 108, 320, TFT_DARKGREY);
      tft.fillRect(294, 0, 20, 320, TFT_WHITE);
      carSpawnTimer = 500;
      carRightEnd = 250;
      carLeftEnd = 186;
      maxCars = 2;
      for(int i = 0; i<maxCars;i++){
        enemyCarSpeed[i]=5;
        enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }else if(level == 2){
      gameTimer = 0;
      tft.fillScreen(TFT_DARKGREEN);
      tft.fillRect(122, 0, 20, 320, TFT_WHITE);
      tft.fillRect(142, 0, 196, 320, TFT_DARKGREY);
      tft.fillRect(338, 0, 20, 320, TFT_WHITE);
      carSpawnTimer = 300;
      carRightEnd = 294;
      carLeftEnd = 142;
      maxCars = 4;
      for(int i = 0; i<maxCars;i++){
        enemyCarSpeed[i]=8;
        enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }else if(level == 3){
      gameTimer = 0;
      tft.fillScreen(TFT_DARKGREEN);
      tft.fillRect(78, 0, 20, 320, TFT_WHITE);
      tft.fillRect(98, 0, 284, 320, TFT_DARKGREY);
      tft.fillRect(382, 0, 20, 320, TFT_WHITE);
      carSpawnTimer = 200;
      carRightEnd = 338;
      carLeftEnd = 98;
      maxCars = 6;
      for(int i = 0; i<maxCars;i++){
        enemyCarSpeed[i]=10;
        enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }else if(level == 4){
      gameTimer = 0;
      tft.fillScreen(TFT_DARKGREEN);
      tft.fillRect(78, 0, 20, 320, TFT_BLUE);
      tft.fillRect(98, 0, 284, 320, TFT_DARKGREY);
      tft.fillRect(382, 0, 20, 320, TFT_BLUE);
      for(int i = 0; i<maxCars;i++){
        enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }else if(level == 5){
      gameTimer = 0;
      tft.fillScreen(TFT_DARKGREEN);
      tft.fillRect(78, 0, 20, 320, TFT_MAROON);
      tft.fillRect(98, 0, 284, 320, TFT_DARKGREY);
      tft.fillRect(382, 0, 20, 320, TFT_MAROON);
      for(int i = 0; i<maxCars;i++){
        enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }else if(level == 6){
      gameTimer = 0;
      tft.fillScreen(TFT_DARKGREEN);
      tft.fillRect(78, 0, 20, 320, TFT_PURPLE);
      tft.fillRect(98, 0, 284, 320, TFT_DARKGREY);
      tft.fillRect(382, 0, 20, 320, TFT_PURPLE);
      for(int i = 0; i<maxCars;i++){
        enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }else if(level == 7){
      gameTimer = 0;
      tft.fillScreen(TFT_DARKGREEN);
      tft.fillRect(78, 0, 20, 320, TFT_CYAN);
      tft.fillRect(98, 0, 284, 320, TFT_DARKGREY);
      tft.fillRect(382, 0, 20, 320, TFT_CYAN);
      for(int i = 0; i<maxCars;i++){
        enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }else if(level == 8){
      gameTimer = 0;
      tft.fillScreen(TFT_DARKGREEN);
      tft.fillRect(78, 0, 20, 320, TFT_SILVER);
      tft.fillRect(98, 0, 284, 320, TFT_DARKGREY);
      tft.fillRect(382, 0, 20, 320, TFT_SILVER);
      for(int i = 0; i<maxCars;i++){
        enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }else if(level == 9){
      tft.fillScreen(TFT_DARKGREEN);
      tft.fillRect(78, 0, 20, 320, TFT_GOLD);
      tft.fillRect(98, 0, 284, 320, TFT_DARKGREY);
      tft.fillRect(382, 0, 20, 320, TFT_GOLD);
      gameTimer = 0;
      for(int i = 0; i<maxCars;i++){
        enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }
  }
void loadCars(uint16_t posX, uint16_t posY, uint16_t color){
  if(color ==1){
            tft.pushImage(posX,posY,44,100,purpleCar);
            }else if(color ==2){
                tft.pushImage(posX,posY,44,100,orangeCar);
            }
            else if(color ==3){
                tft.pushImage(posX,posY,44,100,purpleCar);
            }
            else if(color ==4){
                tft.pushImage(posX,posY,44,100,purpleCar);
            }
            else if(color ==5){
                tft.pushImage(posX,posY,44,100,orangeCar);
            }
            else if(color ==6){
                tft.pushImage(posX,posY,44,100,orangeCar);
            }
            else if(color ==7){
                tft.pushImage(posX,posY,44,100,bossCar);
  }   
}
void rushHourMenu(){
   if (stayScreen == true) {
     
     currentMenuSelect =0;
     tft.fillScreen(TFT_DARKGREY);
     tft.setTextSize(2);
     tft.setTextColor(TFT_YELLOW);
     tft.drawString("HIGH SCORE:",100,30);
     sprintf(rh_highScoreStr, "%d", rh_highScore);
     tft.drawString(rh_highScoreStr,235,30);
     tft.setTextColor(TFT_WHITE);
     tft.setTextSize(5);
     tft.fillRect(100,60,290,75,TFT_YELLOW);
     tft.drawRect(100,60,290,75,TFT_WHITE);
     tft.drawString("RUSH HOUR",110,80);
     tft.setTextSize(3);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("PLAY",205,160);
     tft.drawString("SHOP",205,200);
     tft.drawString("HOW TO PLAY",145,240);
     tft.drawString("EXIT",205,280);
     stayScreen = false;
  }
  if(joysticky>550 && currentMenuSelect!= 0){
      
      currentMenuSelect--;
      tone(3,NOTE_A2,100);
  }
  if(joysticky<450 && currentMenuSelect!= 3){
      currentMenuSelect++;
      tone(3,NOTE_A2,100);
  }
  if(currentMenuSelect == 0){
   tft.fillCircle(180, 210, 10, TFT_DARKGREY);
   tft.fillCircle(115, 250, 10, TFT_DARKGREY);
   tft.fillCircle(180, 290, 10, TFT_DARKGREY);
   
   tft.fillCircle(180, 170, 10, TFT_YELLOW);
  }
  if(currentMenuSelect == 1){
    tft.fillCircle(180, 170, 10, TFT_DARKGREY);
    tft.fillCircle(115, 250, 10, TFT_DARKGREY);
    tft.fillCircle(180, 290, 10, TFT_DARKGREY);

    tft.fillCircle(180, 210, 10, TFT_YELLOW);
  }
  if(currentMenuSelect == 2){
    tft.fillCircle(180, 210, 10, TFT_DARKGREY);
    tft.fillCircle(180, 170, 10, TFT_DARKGREY);
    tft.fillCircle(180, 290, 10, TFT_DARKGREY);

    tft.fillCircle(115, 250, 10, TFT_YELLOW);
  }
  if(currentMenuSelect == 3){
    tft.fillCircle(180, 210, 10, TFT_DARKGREY);
    tft.fillCircle(180, 170, 10, TFT_DARKGREY);
    tft.fillCircle(115, 250, 10, TFT_DARKGREY);

    tft.fillCircle(180, 290, 10, TFT_YELLOW);
  }
  if(currentMenuSelect == 0 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    stayScreen = true;
    screen = 2;
  }
  if(currentMenuSelect == 1 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    stayScreen = true;
    currentMenuSelect = 0;
    screen = 4;
    return;
  }
  if(currentMenuSelect == 2 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    stayScreen = true;
    screen = 6;
    
  }
  if(currentMenuSelect == 3 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    stayScreen = true;
    screen = 1;
  }
  delay(150);
}
void howToPlayRH(){
  if (stayScreen == true) {
     tft.fillScreen(TFT_DARKGREY);
     tft.setTextSize(5);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("HOW TO PLAY",75,60);
     tft.setTextSize(2);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("Oh no! You've turned into the wrong lane!",0,120);
     tft.drawString("Avoid oncoming traffic during Rush Hour.",0,150);
     tft.drawString("Survive and gain points to spend in the",0,180);
     tft.drawString("shop for power-ups and more!",0,210);
     tft.setTextColor(TFT_YELLOW);
     tft.drawString("Press A to return to game menu.",50,250);
    
     stayScreen = false;
  }  
  if(digitalRead(button1) == LOW){
    tone(3,NOTE_C4,rest);
    delay(rest);
    screen = 3;
    stayScreen = true;
  }
}
void rushHourShop(){
    if(stayScreen == true) {
     reset = true;
     currentMenuSelect =0;
     tft.fillScreen(TFT_DARKGREY);
     tft.setTextSize(5);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("SHOP",10,10);
     tft.setTextSize(3);
     tft.fillRect(0,80,480,55,TFT_BLACK);
     tft.setTextColor(TFT_BLUE);
     tft.drawString("Tints/Sprays...",40,140);
     tft.setTextColor(TFT_YELLOW);
     tft.drawString("Point Multiplier",40,170);
     sprintf(pointMultiPriceStr, "%d", pointMultiPrice);
     tft.setTextColor(TFT_GREEN);
     tft.drawString("$",380,170);
     tft.drawString(pointMultiPriceStr,400,170);

     tft.setTextColor(TFT_BLACK);
     tft.drawString("Invincibility",40,200);
     tft.fillCircle(300,210,16,TFT_BLACK);
     tft.fillCircle(300,210,8,TFT_WHITE);
     sprintf(invincPriceStr, "%d", invincPrice);
     tft.setTextColor(TFT_GREEN);
     tft.drawString("$",380,200);
     tft.drawString(invincPriceStr,400,200);


     tft.setTextColor(TFT_SKYBLUE);
     tft.drawString("Slow Time",40,230);
     tft.fillCircle(230,240,16,TFT_SKYBLUE);
     tft.fillRect(230,236,16,5,TFT_WHITE);
     sprintf(slowTimePriceStr, "%d", slowTimePrice);
     tft.setTextColor(TFT_GREEN);
     tft.drawString("$",380,230);
     tft.drawString(slowTimePriceStr,400,230);

     tft.setTextColor(TFT_ORANGE);
     tft.drawString("Flame Barrier",40,260);   
     tft.fillCircle(300,270,16,TFT_RED);
     tft.fillCircle(300,278,8,TFT_ORANGE);
     sprintf(flameBarrPriceStr, "%d", flameBarrPrice);
     tft.setTextColor(TFT_GREEN);
     tft.drawString("$",380,260);
     tft.drawString(flameBarrPriceStr,400,260);
     
     tft.setTextColor(TFT_WHITE);  
     tft.drawString("<- MENU",40,290);     
    //loadout hotbar
    
     tft.setTextSize(3);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("RUSH BUCKS:",10,50);
     tft.setTextColor(TFT_GREEN);
     tft.drawString("$",210,50);
     sprintf(currencyStr, "%d", rh_currency);
     tft.setTextColor(TFT_GREEN);
     tft.drawString(currencyStr,230,50);
     stayScreen = false;
  }
  if(joysticky>550 && currentMenuSelect!= 0){
    tft.fillRect(0,80,480,55,TFT_BLACK);
      currentMenuSelect--;
      tone(3,NOTE_A2,100);
  }
  if(joysticky<450 && currentMenuSelect!= 5){
    tft.fillRect(0,80,480,55,TFT_BLACK);
      currentMenuSelect++;
      tone(3,NOTE_A2,100);
  }
  if(currentMenuSelect == 0){
   tft.setTextSize(2);
   tft.setTextColor(TFT_BLUE);
   tft.drawString("Change the colour of your car.",10,90);
   tft.fillCircle(15, 180, 5, TFT_DARKGREY);
   tft.fillCircle(15, 210, 5, TFT_DARKGREY);
   tft.fillCircle(15, 240, 5, TFT_DARKGREY);
   tft.fillCircle(15, 270, 5, TFT_DARKGREY); 
   tft.fillCircle(15, 300, 5, TFT_DARKGREY);
   
   tft.fillCircle(15, 150, 5, TFT_WHITE);
  }
  if(currentMenuSelect == 1){
   tft.setTextSize(2);
   tft.setTextColor(TFT_YELLOW);
   tft.drawString("Gain more points per second.",10,90);
   if(pointMulti != 3){
    tft.drawString("Current multiplier is: ",10,110);
    sprintf(pointMultiStr, "%d", pointMulti);
    tft.drawString(pointMultiStr,275,110);
    tft.drawString("X",290,110);
   }else{
     tft.drawString("Points Mulitplier is MAXED (3X): ",10,110);
   }
   tft.fillCircle(15, 150, 5, TFT_DARKGREY);
   tft.fillCircle(15, 210, 5, TFT_DARKGREY);
   tft.fillCircle(15, 240, 5, TFT_DARKGREY);
   tft.fillCircle(15, 270, 5, TFT_DARKGREY);
   tft.fillCircle(15, 300, 5, TFT_DARKGREY);
    

   tft.fillCircle(15, 180, 5, TFT_WHITE);

  }
  if(currentMenuSelect == 2){
   tft.setTextSize(1);
   tft.setTextColor(TFT_DARKGREY);
   tft.drawString("Powerup! Phase through oncoming cars for 5 seconds.",10,90);
   tft.drawString("Amount: ",10,110);
   sprintf(invincStr, "%d", invinc);
   tft.drawString(invincStr,70,110);
   tft.fillCircle(15, 150, 5, TFT_DARKGREY);
   tft.fillCircle(15, 180, 5, TFT_DARKGREY);
   tft.fillCircle(15, 240, 5, TFT_DARKGREY);
   tft.fillCircle(15, 270, 5, TFT_DARKGREY);
   tft.fillCircle(15, 300, 5, TFT_DARKGREY);
   


   tft.fillCircle(15, 210, 5, TFT_WHITE);
  }
  if(currentMenuSelect == 3){
   tft.setTextSize(1);
   tft.setTextColor(TFT_SKYBLUE);
   tft.drawString("Powerup! Slows time for oncoming cars 10 seconds.",10,90);
   tft.drawString("Amount: ",10,110);
   sprintf(slowTimeStr, "%d", slowTime);
   tft.drawString(slowTimeStr,70,110);
   tft.fillCircle(15, 150, 5, TFT_DARKGREY);
   tft.fillCircle(15, 180, 5, TFT_DARKGREY);
   tft.fillCircle(15, 210, 5, TFT_DARKGREY);
   tft.fillCircle(15, 270, 5, TFT_DARKGREY);
   tft.fillCircle(15, 300, 5, TFT_DARKGREY);

   tft.fillCircle(15, 240, 5, TFT_WHITE);

  }
  if(currentMenuSelect == 4){
   tft.setTextSize(1);
   tft.setTextColor(TFT_ORANGE);
   tft.drawString("Powerup! Casts a flame around your car for 10 seconds.",10,90);
   tft.drawString("Incinerates incoming cars and gives 100 points.",10,105);
   tft.drawString("Amount: ",10,120);
   sprintf(flameBarrStr, "%d", flameBarr);
   tft.drawString(flameBarrStr,70,120);
   tft.fillCircle(15, 150, 5, TFT_DARKGREY);
   tft.fillCircle(15, 180, 5, TFT_DARKGREY);
   tft.fillCircle(15, 210, 5, TFT_DARKGREY);
   tft.fillCircle(15, 240, 5, TFT_DARKGREY);
   tft.fillCircle(15, 300, 5, TFT_DARKGREY);
   

   tft.fillCircle(15, 270, 5, TFT_WHITE);
  }
  if(currentMenuSelect == 5){
   tft.setTextSize(3);
   tft.setTextColor(TFT_WHITE);
   tft.drawString("Leave shop?",10,90);
   tft.fillCircle(15, 150, 5, TFT_DARKGREY);
   tft.fillCircle(15, 180, 5, TFT_DARKGREY);
   tft.fillCircle(15, 210, 5, TFT_DARKGREY);
   tft.fillCircle(15, 240, 5, TFT_DARKGREY);
   tft.fillCircle(15, 270, 5, TFT_DARKGREY);
   

   tft.fillCircle(15, 300, 5, TFT_WHITE);
  }

  if(currentMenuSelect == 0 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    screen = 5;
    stayScreen = true;
  }
  if(pointMulti == 3 && reset == true){ 
    tft.fillRect(380,170,100,25,TFT_DARKGREY);
    tft.setTextSize(3);
    tft.setTextColor(TFT_RED);
    tft.drawString("MAXED",380,170);  
    reset = false;

    
  }
  if(currentMenuSelect == 1 && digitalRead(button1) == LOW && pointMulti<3){
    if(rh_currency>=pointMultiPrice){
       rh_currency = rh_currency - pointMultiPrice;
       pointMulti++;
       pointMultiPrice = pointMultiPrice +=3000;
       tft.setTextSize(3);
       sprintf(pointMultiPriceStr, "%d", pointMultiPrice);
       tft.setTextColor(TFT_GREEN);
       tft.fillRect(400,170,80,25,TFT_DARKGREY);
       tft.drawString(pointMultiPriceStr,400,170);  

       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.setTextSize(2);
       tft.setTextColor(TFT_GREEN);
       tft.drawString("Purchased!",10,90);
       
       tft.drawString("Current multiplier is: ",10,110);
       sprintf(pointMultiStr, "%d", pointMulti);
       tft.drawString(pointMultiStr,275,110);
       tft.drawString("X",290,110);
       tone(3,NOTE_C6,rest);
       delay(rest);
       delay(1000);

       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.fillRect(230,50,250,25,TFT_DARKGREY);
       sprintf(currencyStr, "%d", rh_currency);
       tft.setTextSize(3);
       tft.setTextColor(TFT_GREEN);
       tft.drawString(currencyStr,230,50);
    }else{
       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.setTextSize(2);
       tft.setTextColor(TFT_RED);
       tft.drawString("Not enough Rush Bucks!",10,90);
       tone(3,NOTE_C1,rest);
       delay(rest);
       delay(1000);
       tft.fillRect(0,80,480,55,TFT_BLACK);
    }

  }
  if(currentMenuSelect == 2 && digitalRead(button1) == LOW  ){
    if(rh_currency>=invincPrice){
       rh_currency = rh_currency - invincPrice;
       invinc++;
       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.setTextSize(2);
       tft.setTextColor(TFT_GREEN);
       tft.drawString("Purchased!",10,90);

       tft.drawString("Amount: ",10,110);
       sprintf(invincStr, "%d", invinc);
       tft.drawString(invincStr,150,110);
       tone(3,NOTE_C6,rest);
       delay(rest);
       delay(1000);

       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.fillRect(230,50,250,25,TFT_DARKGREY);
       sprintf(currencyStr, "%d", rh_currency);
       tft.setTextSize(3);
       tft.setTextColor(TFT_GREEN);
       tft.drawString(currencyStr,230,50);
    }else{
       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.setTextSize(2);
       tft.setTextColor(TFT_RED);
       tft.drawString("Not enough Rush Bucks!",10,90);
       tone(3,NOTE_C1,rest);
       delay(rest);
       delay(1000);
       tft.fillRect(0,80,480,55,TFT_BLACK);
    }
  }
  if(currentMenuSelect == 3 && digitalRead(button1) == LOW  ){
    if(rh_currency>=slowTimePrice){
       rh_currency = rh_currency - slowTimePrice;
       slowTime++;
       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.setTextSize(2);
       tft.setTextColor(TFT_GREEN);
       tft.drawString("Purchased!",10,90);
       tft.drawString("Amount: ",10,110);
       sprintf(slowTimeStr, "%d", slowTime);
       tft.drawString(slowTimeStr,150,110);
       tone(3,NOTE_C6,rest);
       delay(rest);
       delay(1000);

       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.fillRect(230,50,250,25,TFT_DARKGREY);
       sprintf(currencyStr, "%d", rh_currency);
       tft.setTextSize(3);
       tft.setTextColor(TFT_GREEN);
       tft.drawString(currencyStr,230,50);
    }else{
       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.setTextSize(2);
       tft.setTextColor(TFT_RED);
       tft.drawString("Not enough Rush Bucks!",10,90);
       tone(3,NOTE_C1,rest);
       delay(rest);
       delay(1000);
       tft.fillRect(0,80,480,55,TFT_BLACK);
    }
  }
  if(currentMenuSelect == 4 && digitalRead(button1) == LOW  ){
    if(rh_currency>=flameBarrPrice){
       rh_currency = rh_currency - flameBarrPrice;
       flameBarr++;
       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.setTextSize(2);
       tft.setTextColor(TFT_GREEN);
       tft.drawString("Purchased!",10,90);

       tft.drawString("Amount: ",10,110);
       sprintf(flameBarrStr, "%d", flameBarr);
       tft.drawString(flameBarrStr,150,110);
       tone(3,NOTE_C6,rest);
       delay(rest);
       delay(1000);
       

       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.fillRect(230,50,250,25,TFT_DARKGREY);
       sprintf(currencyStr, "%d", rh_currency);
       tft.setTextSize(3);
       tft.setTextColor(TFT_GREEN);
       tft.drawString(currencyStr,230,50);
    }else{
       tft.fillRect(0,80,480,55,TFT_BLACK);
       tft.setTextSize(2);
       tft.setTextColor(TFT_RED);
       tft.drawString("Not enough Rush Bucks!",10,90);
       tone(3,NOTE_C1,rest);
       delay(rest);
       delay(1000);
       tft.fillRect(0,80,480,55,TFT_BLACK);
    }
  }
  if(currentMenuSelect == 5 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    screen = 3;
    stayScreen = true;
  }
  
}
void paintCar(){
    if(powerUp == 1){
    //OUTLINE
    tft.fillRect(playerCarPosX+2,playerCarPosY+8,39,74,TFT_BLACK);  
    //CHASSIS
    tft.fillRect(playerCarPosX+4,playerCarPosY+13,35,67,TFT_BLACK);
    //WINGS
    tft.fillRect(playerCarPosX-1,playerCarPosY+70,45,5,TFT_WHITE);
    //MIRRORS
    tft.fillRect(playerCarPosX-1,playerCarPosY+36,5,2,TFT_BLACK);
    tft.fillRect(playerCarPosX+39,playerCarPosY+36,5,2,TFT_BLACK);
    //WINDOWS
    tft.fillRect(playerCarPosX+4,playerCarPosY+36,35,13,TFT_WHITE);
    tft.fillRect(playerCarPosX+4,playerCarPosY+40,4,25,TFT_WHITE);
    tft.fillRect(playerCarPosX+35,playerCarPosY+40,4,25,TFT_WHITE);
    }
    if(powerUp == 2){
    //OUTLINE
    tft.fillRect(playerCarPosX+2,playerCarPosY+8,39,74,TFT_BLACK);  
    //CHASSIS
    tft.fillRect(playerCarPosX+4,playerCarPosY+13,35,67,TFT_SKYBLUE);
    //WINGS
    tft.fillRect(playerCarPosX-1,playerCarPosY+70,45,5,TFT_WHITE);
    //MIRRORS
    tft.fillRect(playerCarPosX-1,playerCarPosY+36,5,2,TFT_SKYBLUE);
    tft.fillRect(playerCarPosX+39,playerCarPosY+36,5,2,TFT_SKYBLUE);
    //WINDOWS
    tft.fillRect(playerCarPosX+4,playerCarPosY+36,35,13,TFT_WHITE);
    tft.fillRect(playerCarPosX+4,playerCarPosY+40,4,25,TFT_WHITE);
    tft.fillRect(playerCarPosX+35,playerCarPosY+40,4,25,TFT_WHITE);
    }
    if(powerUp == 3){
    //OUTLINE
    tft.fillRect(playerCarPosX+2,playerCarPosY+8,39,74,TFT_BLACK);  
    //CHASSIS
    tft.fillRect(playerCarPosX+4,playerCarPosY+13,35,67,TFT_RED);
    //WINGS
    tft.fillRect(playerCarPosX-1,playerCarPosY+70,45,5,TFT_ORANGE);
    //MIRRORS
    tft.fillRect(playerCarPosX-1,playerCarPosY+36,5,2,TFT_RED);
    tft.fillRect(playerCarPosX+39,playerCarPosY+36,5,2,TFT_RED);
    //WINDOWS
    tft.fillRect(playerCarPosX+4,playerCarPosY+36,35,13,TFT_ORANGE);
    tft.fillRect(playerCarPosX+4,playerCarPosY+40,4,25,TFT_ORANGE);
    tft.fillRect(playerCarPosX+35,playerCarPosY+40,4,25,TFT_ORANGE);
    }
    if(powerUp==0){
      //OUTLINE
      tft.fillRect(playerCarPosX+2,playerCarPosY+8,39,74,TFT_BLACK);  
      //CHASSIS
      tft.fillRect(playerCarPosX+4,playerCarPosY+13,35,67,playerCarColor);
      //WINGS
      tft.fillRect(playerCarPosX-1,playerCarPosY+70,45,5,playerCarColor);
      //MIRRORS
      tft.fillRect(playerCarPosX-1,playerCarPosY+36,5,2,playerCarColor);
      tft.fillRect(playerCarPosX+39,playerCarPosY+36,5,2,playerCarColor);
      //WINDOWS
      tft.fillRect(playerCarPosX+4,playerCarPosY+36,35,13,playerWindowTint);
      tft.fillRect(playerCarPosX+4,playerCarPosY+40,4,25,playerWindowTint);
      tft.fillRect(playerCarPosX+35,playerCarPosY+40,4,25,playerWindowTint);
    }
    
    
   

    
}
void sprayCar(){
  if(stayScreen == true){
     colorIndex = 10;
     currentMenuSelect =0;
     playerCarPosX = 216;
     playerCarPosY = 50;
     tft.fillScreen(TFT_DARKGREY);
     tft.setTextSize(5);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("COLOUR",10,10);
     tft.setTextSize(3);
     tft.fillRect(0,60,480,200,TFT_LIGHTGREY);
     tft.setTextSize(5);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("<",140,200);
     tft.fillRect(190,160,100,100,colorWheel[colorIndex]);
     tft.drawRect(190,160,100,100,TFT_BLACK);
     tft.drawString(">",310,200);
     tft.setTextSize(2);
     tft.setTextColor(TFT_WHITE);
     tft.drawString("RUSH BUCKS:",240,40);
     tft.drawString("$",370,40);
     sprintf(currencyStr, "%d", rh_currency);
     tft.setTextColor(TFT_GREEN);
     tft.drawString(currencyStr,383,40);
     tft.setTextColor(TFT_WHITE);  
     tft.setTextSize(3);
     tft.drawString("<- SHOP",35,280);    
     tft.setTextSize(3);
     tft.drawString("SPRAY", 30,120);
     tft.drawString("TINT", 30,90);
     tft.setTextColor(TFT_GREEN);
     tft.drawString("$500",130,120);
     tft.drawString("$200",110,90);

     tft.setTextColor(TFT_WHITE);
      paintCar();
     stayScreen = false;
  }
  if(joystickx>550 && colorIndex!= 0){
      colorIndex--;
      tft.setTextSize(5);
      tft.setTextColor(TFT_DARKGREY);  
      tft.drawString(">",310,200);
      tone(3,NOTE_A2,100);
      delay(100);
      
      tft.fillRect(190,160,100,100,colorWheel[colorIndex]);
      tft.drawRect(190,160,100,100,TFT_BLACK);
      tft.setTextColor(TFT_WHITE);  
      tft.drawString(">",310,200);
  }
  if(joystickx<450 && colorIndex!= 21){
      colorIndex++;
      tft.setTextSize(5);
      tft.setTextColor(TFT_DARKGREY);  
      tft.drawString("<",140,200);
      tone(3,NOTE_A2,100);
      delay(100);
      tft.fillRect(190,160,100,100,colorWheel[colorIndex]);
      tft.drawRect(190,160,100,100,TFT_BLACK);
      tft.setTextColor(TFT_WHITE);  
      tft.drawString("<",140,200);
  }
  if(joysticky>550 && currentMenuSelect!= 0){
      
      currentMenuSelect--;
      tone(3,NOTE_A2,100);
  }
  if(joysticky<450 && currentMenuSelect!= 2){
    
      currentMenuSelect++;
      tone(3,NOTE_A2,100);
  }
  if(currentMenuSelect == 0){
   
   tft.fillCircle(15, 128, 5, TFT_DARKGREY);
   tft.fillCircle(15, 290, 5, TFT_DARKGREY);
   
   tft.fillCircle(15, 98, 5, TFT_WHITE);
  }
   if(currentMenuSelect == 1){
   
   tft.fillCircle(15, 98, 5, TFT_DARKGREY);
   tft.fillCircle(15, 290, 5, TFT_DARKGREY);
   
   tft.fillCircle(15, 128, 5, TFT_WHITE);
  }
  
  if(currentMenuSelect == 2){
    tft.fillCircle(15, 98, 5, TFT_DARKGREY);
   tft.fillCircle(15, 128, 5, TFT_DARKGREY);
  

   tft.fillCircle(15, 290, 5, TFT_WHITE);
  }

  if(currentMenuSelect == 0 && digitalRead(button1) == LOW && rh_currency>=200  ){
    playerWindowTint = colorWheel[colorIndex];
    rh_currency = rh_currency - 200;
    tft.setTextSize(2);
    tft.fillRect(370,40,120,20,TFT_DARKGREY);
    tft.setTextColor(TFT_GREEN);
    tft.drawString("PURCHASED",370,40);
    tone(3,NOTE_C6,rest);
    delay(rest);
    delay(1000);
    
    paintCar();
    tft.fillRect(370,40,120,20,TFT_DARKGREY);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("$",370,40);
    sprintf(currencyStr, "%d", rh_currency);
    tft.setTextColor(TFT_GREEN);
    tft.drawString(currencyStr,383,40);
    
  }else if(currentMenuSelect == 0 && digitalRead(button1) == LOW){
    tone(3,NOTE_C1,rest);
    delay(rest);
  }
  
  if(currentMenuSelect == 1 && digitalRead(button1) == LOW && rh_currency >=500 ){
    playerCarColor = colorWheel[colorIndex];
    rh_currency = rh_currency - 500;
    tft.setTextSize(2);
    tft.fillRect(370,40,120,20,TFT_DARKGREY);
    tft.setTextColor(TFT_GREEN);
    tft.drawString("PURCHASED",370,40);
    tone(3,NOTE_C6,rest);
    delay(rest);
    delay(1000);
    
    paintCar();
    tft.fillRect(370,40,120,20,TFT_DARKGREY);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("$",370,40);
    sprintf(currencyStr, "%d", rh_currency);
    tft.setTextColor(TFT_GREEN);
    tft.drawString(currencyStr,383,40);
  }else if(currentMenuSelect == 1 && digitalRead(button1) == LOW){
    tone(3,NOTE_C1,rest);
    delay(rest);
  }
  if(currentMenuSelect == 2 && digitalRead(button1) == LOW  ){
    tone(3,NOTE_C4,rest);
    delay(rest);
    screen = 4;
    stayScreen = true; 
  }
  delay(100);
}
void rushHourGame() {
  //Resetting game timer 
    if(gameTimer==carSpawnTimer){
      gameTimer = 0;
      for(uint16_t i =0; i<maxCars; i++){
          enemyCarTimers[i]=(rand() %
          (carSpawnTimer - 0 + 1)) + 0;
      }
    }
  //First LAUNCH OR LEVEL changed  
    if (stayScreen == true) {
      if(level == 1){
        score = 0;
      }
      powerUp = 0;
      
      //CREATE respective LEVEL;
      levelCreate();
      tft.setTextColor(TFT_GREEN);
      tft.setTextSize(3);
      tft.drawString("4:59PM",187,120);
      tft.setTextSize(5);
      tft.setTextColor(TFT_RED);
      tft.drawString("3",225,180);
      tone(3,NOTE_A2,500);
      delay(1000);
      
      tft.setTextColor(TFT_YELLOW);
      tft.fillRect(186,180,108,120,TFT_DARKGREY);       
      tft.drawString("2",225,180);
      tone(3,NOTE_A2,500);
      delay(1000);
      tft.setTextColor(TFT_GREEN);
      tft.fillRect(186,180,108,120,TFT_DARKGREY); 
      tft.drawString("1",225,180);
      tone(3,NOTE_A2,500);
      delay(1000);
      tft.fillRect(186,110,108,130,TFT_DARKGREY); 
      tft.setTextColor(TFT_RED);
      tft.setTextSize(2);
      tft.drawString("RUSH HOUR",187,180);
      tft.setTextSize(3);
      tft.drawString("5:00PM",187,120);
      tone(3,NOTE_C4,500);
      delay(1000);
      tft.fillRect(186,110,108,130,TFT_DARKGREY); 
      
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(2);
      //Invincibility
      tft.fillCircle(16,170,16,TFT_BLACK);
      tft.fillCircle(16,170,8,TFT_WHITE);
      
      tft.fillCircle(16,140,10,TFT_BLACK);
      tft.drawString("B",12,135);
      tft.setTextSize(2);
      sprintf(invincStr, "%d", invinc);
      tft.drawString(invincStr,37,164);
      //Slow Time
      tft.fillCircle(16,230,16,TFT_SKYBLUE);
      tft.fillRect(16,226,16,5,TFT_WHITE);

      tft.fillCircle(16,200,10,TFT_BLACK);
      tft.drawString("Y",12,195);
      tft.setTextSize(2);
      sprintf(slowTimeStr, "%d", slowTime);
      tft.drawString(slowTimeStr,37,224);

      //Flame Barrier
      tft.fillCircle(16,290,16,TFT_RED);
      tft.fillCircle(16,298,8,TFT_ORANGE);

      tft.fillCircle(16,262,10,TFT_BLACK);
      tft.drawString("A",11,256);
      tft.setTextSize(2);
      sprintf(flameBarrStr, "%d", flameBarr);
      tft.drawString(flameBarrStr,37,284);

      tft.fillRect(0,0,78,130,TFT_DARKGREEN);
      tft.setTextSize(2);
      tft.setTextColor(TFT_WHITE);
      tft.drawString("SCORE:",0,0);
      tft.drawString(scoreStr,0,20);
     
       playerCarPosX = 250;
       playerCarPosY = 240;
      paintCar();
      stayScreen = false;      
      delay(1000);
    }
  //PLAYER CAR
    //player car movement RIGHT
    if (joystickx > 550 && playerCarPosX!=carRightEnd) {
      tft.fillRect(playerCarPosX-1, 240, 45, 88, TFT_DARKGREY);
      if(playerCarPosX!=186){
          playerCarPosX = playerCarPosX + 44;
      }else{
          playerCarPosX = playerCarPosX + 64;
      }
      paintCar();
    }

      
    
    //player car movement LEFT
    if (joystickx < 450 && playerCarPosX!=carLeftEnd) {
      tft.fillRect(playerCarPosX-1, 240, 45, 88, TFT_DARKGREY);
      if(playerCarPosX!=250){
          playerCarPosX = playerCarPosX - 44;
      }else{
          playerCarPosX = playerCarPosX - 64;
      }
      paintCar();
    }
    
    
  //ENEMY CARS AND COLLISIONS (GAME OVER)
    //enemy car handler
    for(uint16_t i =0; i<maxCars; i++){
        //resetting enemy cars when reaching the end of the screen 
        if(enemyCarPosY[i]>=320){
          enemyCarPosY[i]= -160;
          enemyCars[i]=false;
          if(powerUp==1){
            paintCar();
          }

        }
        //spawn enemy car if timer is up
        if(enemyCars[i]==true){
          if(powerUp==2){
             enemyCarPosY[i] = enemyCarPosY[i] + 3;   
          }else{
            if(enemyCarColor[i]!=7){
               enemyCarPosY[i] = enemyCarPosY[i] + enemyCarSpeed[i];  
            }else{
               enemyCarPosY[i] = enemyCarPosY[i] + 20;
            }
          }
                     
          loadCars(enemyCarPosX[i],enemyCarPosY[i],enemyCarColor[i]);
        }
        //enemy car spawn timers
        if(enemyCarTimers[i]==gameTimer){
          enemyCars[i] = true;
          enemyCarPosY[i]= enemyCarPosY[i]-enemyCarSpeed[i];
          enemyCarColor[i] = (rand() %(7 - 1 + 1)) + 1;
          loadCars(enemyCarPosX[i],enemyCarPosY[i],enemyCarColor[i]);
          continue;
        }
        if(enemyCarPosY[i] >= 141 && enemyCarPosX[i]==playerCarPosX && powerUp == 3){
          enemyCars[i]=false;
          tft.fillRect(enemyCarPosX[i], enemyCarPosY[i], 44, 100, TFT_RED);
          delay(200);
          tft.fillRect(enemyCarPosX[i], enemyCarPosY[i], 44, 100, TFT_ORANGE);
          tft.setTextSize(2);
          tft.setTextColor(TFT_GREEN);
          if(enemyCarColor[i]!=7){
            score = score + 100;
            tone(3,NOTE_B4,100);
            delay(100);
            tft.drawString("+100",0,60);
            tft.drawString("NORMAL",0,80);
            tft.drawString("ENEMY!",0,100);
          }else{
            tone(3,NOTE_B4,100);
            delay(100);
            score = score + 500;
            tft.drawString("+500!",0,60);
            tft.drawString("BOSS",0,80);
            tft.drawString("ENEMY!",0,100);
          }
          delay(200);
          tft.fillRect(enemyCarPosX[i], enemyCarPosY[i], 44, 100, TFT_DARKGREY);
          delay(200);
          paintCar();
          tft.fillRect(0,20,78,130,TFT_DARKGREEN);
          enemyCarPosY[i]= -160;
        }
        //COLLISION -if enemy car hits the player car (GAME OVER)
        if(enemyCarPosY[i] >= 141 && enemyCarPosX[i]==playerCarPosX && powerUp != 1 && powerUp != 3){
          //fill screen red
          rest=500;
          tone(3,NOTE_F2,rest-10);
          delay(rest);
          tone(3,NOTE_E2,rest-10);
          delay(rest);
          tone(3,NOTE_DS2,rest-10);
          delay(rest);
          tone(3,NOTE_D2,1000);
          delay(1000);
          tft.fillScreen(TFT_RED);
          // you lose 
          if(score>=rh_highScore){
            rh_highScore = score;
            tft.setTextSize(3);
            tft.setTextColor(TFT_GREEN);
            tft.drawString("NEW HIGH SCORE!",110,30);
          }
          tft.setTextColor(TFT_WHITE);
          tft.setTextSize(5);
          tft.drawString("You LOSE!",110,90);
          //purge all enemy cars
          for(uint16_t i =0; i<maxCars; i++){
            enemyCars[i]=false;
            enemyCarPosY[i]= -160;
          }    
          //reset player car
          playerCarPosX = 250;
          //convert score to currency then reset score and level
          rh_currency = rh_currency + score;     
          level = 1;
          //MENU OPTIONS returns to menu
          tft.setTextSize(3);
          sprintf(scoreStr, "%d", score);
          tft.setTextSize(2);
          tft.drawString("Score:",180,140);
          tft.drawString(scoreStr,255,140);
          tft.setTextColor(TFT_GREEN);
          tft.drawString("Converted to RUSH BUCKS! $$ ",70,180);
          tft.setTextColor(TFT_WHITE);
          tft.drawString("RUSH BUCKS:",135,220);
          tft.setTextColor(TFT_GREEN);
          tft.drawString("$",275,220);
          sprintf(currencyStr, "%d", rh_currency);
          tft.setTextColor(TFT_GREEN);
          tft.drawString(currencyStr,290,220);
          tft.setTextColor(TFT_YELLOW);
          tft.drawString("Returning to Main Menu...",80,260);
          delay(5000);  
          
          score = 0;
          updateScore = 0;           
          stayScreen = true;
          screen = 3;
          break; 
        }
    }
  //LEVEL CHECK
    if (score >= 500 && !levelChanged && level < 2){
        tft.fillScreen(TFT_GREEN);
        tft.setTextSize(5);
        tft.drawString("Next Level!",90,140);
        
        tone(3,NOTE_F5,rest-10);
          delay(rest);
          tone(3,NOTE_G5,rest-10);
          delay(rest);
          tone(3,NOTE_A5,rest-10);
          delay(rest);
        tft.drawString("Next Level!",90,140);  
        level = 2;
        delay(2000);
        
        levelChanged = true;
        stayScreen = true;
    }else if(score >= 1000 && !levelChanged && level < 3){
      
        tft.fillScreen(TFT_GREEN);
        tft.setTextSize(5);
        tft.drawString("Next Level!",90,140);
         tone(3,NOTE_F5,rest-10);
          delay(rest);
          tone(3,NOTE_G5,rest-10);
          delay(rest);
          tone(3,NOTE_A5,rest-10);
          delay(rest);
        tft.drawString("Next Level!",90,140);          
        level = 3;
        delay(2000);
        
        levelChanged = true;
        stayScreen = true;
    }else if(score >= 2500 && !levelChanged && level < 4){
        tft.fillScreen(TFT_BLUE);
        tft.setTextSize(5);
        tft.drawString("Next Level!",90,140);
         tone(3,NOTE_F5,rest-10);
          delay(rest);
          tone(3,NOTE_G5,rest-10);
          delay(rest);
          tone(3,NOTE_A5,rest-10);
          delay(rest);
        tft.drawString("Next Level!",90,140);           
        level = 4;
        delay(2000);
        
        levelChanged = true;
        stayScreen = true;
    }else if(score >= 5000 && !levelChanged && level < 5){
        tft.fillScreen(TFT_MAROON);
        tft.setTextSize(5);
        tft.drawString("Next Level!",90,140);
         tone(3,NOTE_F5,rest-10);
          delay(rest);
          tone(3,NOTE_G5,rest-10);
          delay(rest);
          tone(3,NOTE_A5,rest-10);
          delay(rest);
        tft.drawString("Next Level!",90,140);  
        level = 5;
        delay(2000);
        
        levelChanged = true;
        stayScreen = true;
    }else if(score >= 10000 && !levelChanged && level < 6){
        tft.fillScreen(TFT_PURPLE);
        tft.setTextSize(5);
        tft.drawString("Next Level!",90,140);
         tone(3,NOTE_F5,rest-10);
          delay(rest);
          tone(3,NOTE_G5,rest-10);
          delay(rest);
          tone(3,NOTE_A5,rest-10);
          delay(rest);
        tft.drawString("Next Level!",90,140);          
        level = 6;
        delay(2000);
        
        levelChanged = true;
        stayScreen = true;
    }else if(score >= 15000 && !levelChanged && level < 7){
        tft.fillScreen(TFT_CYAN);
        tft.setTextSize(5);
        tft.drawString("Next Level!",90,140);
         tone(3,NOTE_F5,rest-10);
          delay(rest);
          tone(3,NOTE_G5,rest-10);
          delay(rest);
          tone(3,NOTE_A5,rest-10);
          delay(rest);
        tft.drawString("Next Level!",90,140);  
        level = 7;
        delay(2000);
        
        levelChanged = true;
        stayScreen = true;
    }else if(score >= 20000 && !levelChanged && level < 8){
        tft.fillScreen(TFT_SILVER);
        tft.setTextSize(5);
        tft.drawString("Next Level!",90,140);
         tone(3,NOTE_F5,rest-10);
          delay(rest);
          tone(3,NOTE_G5,rest-10);
          delay(rest);
          tone(3,NOTE_A5,rest-10);
          delay(rest);
        tft.drawString("Next Level!",90,140);  
        level = 8;
        delay(2000);
        
        levelChanged = true;
        stayScreen = true;
    }else if(score >= 25000 && !levelChanged && level < 9){
        tft.fillScreen(TFT_GOLD);
        tft.setTextSize(5);
        tft.drawString("Next Level!",90,140);
         tone(3,NOTE_F5,rest-10);
          delay(rest);
          tone(3,NOTE_G5,rest-10);
          delay(rest);
          tone(3,NOTE_A5,rest-10);
          delay(rest);
        tft.drawString("Next Level!",90,140);  
        level = 9;
        delay(2000);
        
        levelChanged = true;
        stayScreen = true;
    }
    
  //UPDATING SCORE
    if(updateScore==40){
        score= score + (10 * pointMulti);  
        tft.setTextColor(TFT_WHITE);
        tft.setTextSize(2);
        tft.fillRect(0,20,78,50,TFT_DARKGREEN);   
        sprintf(scoreStr, "%d", score);
        tft.drawString(scoreStr,0,20);
        levelChanged = false;      
        updateScore=0;
    } 
    if(score>=1000){
      endGameTimer++;
    }
    if(endGameTimer>=100 && enemyCarSpeed[0]!=20){
      for(int i = 0; i<maxCars;i++){
        enemyCarSpeed[i]=enemyCarSpeed[i]+1;
      }
      endGameTimer = 0;
    }
  //ADD TO TIMERS and COUNTS
    updateScore++;
    gameTimer++;
  //POWERUPS
    if(powerUp!=0){
      powerUpTimer++;
    }
    if(powerUp == 1 && powerUpTimer >= 500){
      powerUp = 0;
      powerUpTimer = -1;
    }
    if(powerUp == 2 && powerUpTimer >= 700){
      powerUp = 0;
      powerUpTimer = -1;
    }
    if(powerUp == 3 && powerUpTimer >= 500){
      powerUp = 0;
      powerUpTimer = -1;
    }
    if(digitalRead(button2) == LOW && powerUp == 0 && invinc >= 1){
      powerUp = 1;
      invinc--;
      tft.fillRect(37,164,20,20,TFT_DARKGREEN);
      sprintf(invincStr, "%d", invinc);
      tft.drawString(invincStr,37,164);
      powerUpTimer = 0;
      tone(3,NOTE_C4,rest);
      delay(rest);
      paintCar();
    }
    if(digitalRead(button3) == LOW && powerUp == 0 && slowTime >= 1){
      powerUp = 2;
      slowTime--;
      tft.fillRect(37,224,20,20,TFT_DARKGREEN);
      sprintf(slowTimeStr, "%d", slowTime);
      tft.drawString(slowTimeStr,37,224);
      powerUpTimer = 0;
      tone(3,NOTE_C4,rest);
      delay(rest);
      paintCar();
    }
    if(digitalRead(button1) == LOW && powerUp == 0 && flameBarr >= 1){
      powerUp = 3;
      flameBarr--;
      tft.fillRect(37,284,20,20,TFT_DARKGREEN);
      sprintf(flameBarrStr, "%d", flameBarr);
      tft.drawString(flameBarrStr,37,284);
      powerUpTimer = 0;
      tone(3,NOTE_C4,rest);
      delay(rest);
      paintCar();
    }


}

void selectScreen() {
  if (screen == 1) {
    gameMenu();
  }
  if (screen == 2) {
    rushHourGame();
  }
  if (screen == 3) {
    rushHourMenu();
  }
  if (screen == 4) {
    rushHourShop();
  }
  if (screen == 5) {
    sprayCar();
  }
  if (screen == 6) {
    howToPlayRH();
  }
  if(screen == 7){
    johnnyGunGame();
  }
  if(screen == 8){
    johnnyGunMenu();
  }
  if(screen == 9){
    howToPlayJG();
  }
}

void loop() {
  //Read Joysticks
    joystickx = analogRead(JOYSTICK_X_PIN);
    //greater than 520 is down less is up
    joysticky = analogRead(JOYSTICK_Y_PIN);
  selectScreen();
}