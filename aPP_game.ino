#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Призначення 4 кнопок
#define BTN_UP    14 // D5 - Вгору
#define BTN_DOWN  12 // D6 - Вниз
#define BTN_LEFT  13 // D7 - Вліво (В меню: OK)
#define BTN_RIGHT  2 // D4 - Вправо (GPIO2 замість GPIO0)

int menuIndex = 0;
const int TOTAL_GAMES = 5;

const char* gameNames[TOTAL_GAMES] = {
  "1. Flappy Bird",
  "2. Dino Run",
  "3. Pong",
  "4. Space Invader",
  "5. Dodge"
};

void setup() {
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); 
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  showMenu();
}

void loop() {
  // Навігація в меню
  if (digitalRead(BTN_UP) == LOW) {
    menuIndex = (menuIndex - 1 + TOTAL_GAMES) % TOTAL_GAMES;
    showMenu();
    delay(200);
  }
  
  if (digitalRead(BTN_DOWN) == LOW) {
    menuIndex = (menuIndex + 1) % TOTAL_GAMES;
    showMenu();
    delay(200);
  }

  // Запуск гри на ВЛІВО (D7)
  if (digitalRead(BTN_LEFT) == LOW) {
    if (menuIndex == 0) playFlappy();
    if (menuIndex == 1) playDino();
    if (menuIndex == 2) playPong();
    if (menuIndex == 3) playSpace();
    if (menuIndex == 4) playDodge();
    showMenu();
    delay(200);
  }
}

void showMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(25, 0);
  display.println("=== aPPgame ===");
  
  for (int i = 0; i < TOTAL_GAMES; i++) {
    display.setCursor(5, 14 + (i * 10));
    if (menuIndex == i) display.print("> "); else display.print("  ");
    display.println(gameNames[i]);
  }

  display.display();
}

// Вихід у меню: Одночасно Вгору + Вниз
bool checkExitCombo() {
  if (digitalRead(BTN_UP) == LOW && digitalRead(BTN_DOWN) == LOW) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(30, 25);
    display.println("EXITING...");
    display.display();
    delay(800);
    return true;
  }
  return false;
}

void showGameOver(int score) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(32, 20);
  display.println("GAME OVER");
  display.setCursor(32, 35);
  display.print("Score: "); display.println(score);
  display.display();
  delay(1500);
}

// ==================== 1. FLAPPY BIRD ====================
void playFlappy() {
  float birdY = 32;
  float velocity = 0;
  float gravity = 0.35;
  int pipeX = 128;
  int pipeGapY = random(10, 35);
  int gapSize = 24;
  int score = 0;

  while(true) {
    if (checkExitCombo()) return;

    if (digitalRead(BTN_UP) == LOW) {
      velocity = -2.5;
    }

    velocity += gravity;
    birdY += velocity;

    pipeX -= 2;
    if (pipeX < -12) {
      pipeX = 128;
      pipeGapY = random(10, 35);
      score++;
    }

    if (birdY < 0 || birdY > 60) { showGameOver(score); return; }
    if (pipeX < 20 && pipeX > 5) {
      if (birdY < pipeGapY || birdY > pipeGapY + gapSize) {
        showGameOver(score);
        return;
      }
    }

    display.clearDisplay();
    display.fillRect(12, (int)birdY, 6, 6, SSD1306_WHITE);
    display.fillRect(pipeX, 0, 12, pipeGapY, SSD1306_WHITE);
    display.fillRect(pipeX, pipeGapY + gapSize, 12, 64 - (pipeGapY + gapSize), SSD1306_WHITE);
    
    display.setCursor(0, 0); display.print(score);
    display.display();
    delay(25);
  }
}

// ==================== 2. DINO RUN ====================
void playDino() {
  int dinoY = 48;
  int jumpVelocity = 0;
  bool isJumping = false;
  int obsX = 128;
  int score = 0;

  while(true) {
    if (checkExitCombo()) return;

    if (digitalRead(BTN_UP) == LOW && !isJumping) {
      jumpVelocity = -7;
      isJumping = true;
    }

    if (isJumping) {
      dinoY += jumpVelocity;
      jumpVelocity += 1;
      if (dinoY >= 48) {
        dinoY = 48;
        isJumping = false;
      }
    }

    obsX -= 3;
    if (obsX < -6) {
      obsX = 128;
      score++;
    }

    if (obsX >= 10 && obsX <= 18 && dinoY >= 40) {
      showGameOver(score);
      return;
    }

    display.clearDisplay();
    display.drawLine(0, 56, 128, 56, SSD1306_WHITE);
    display.fillRect(12, dinoY, 8, 8, SSD1306_WHITE);
    display.fillRect(obsX, 44, 6, 12, SSD1306_WHITE);

    display.setCursor(0, 0); display.print(score);
    display.display();
    delay(20);
  }
}

// ==================== 3. PONG ====================
void playPong() {
  int paddleY = 24, botY = 24;
  int ballX = 64, ballY = 32;
  int ballSpeedX = 2, ballSpeedY = 2;
  int playerScore = 0, botScore = 0;

  while(true) {
    if (checkExitCombo()) return;

    if (digitalRead(BTN_UP) == LOW && paddleY > 12) paddleY -= 3;
    if (digitalRead(BTN_DOWN) == LOW && paddleY < 46) paddleY += 3;

    if (botY + 8 < ballY && botY < 46) botY += 2;
    if (botY + 8 > ballY && botY > 12) botY -= 2;

    ballX += ballSpeedX; ballY += ballSpeedY;

    if (ballY <= 12 || ballY >= 60) ballSpeedY = -ballSpeedY;
    if (ballX >= 120 && ballY >= botY && ballY <= botY + 16) ballSpeedX = -ballSpeedX;
    if (ballX <= 6 && ballY >= paddleY && ballY <= paddleY + 16) ballSpeedX = -ballSpeedX;

    if (ballX > 124) { playerScore++; ballX = 64; ballY = 32; ballSpeedX = -2; delay(300); }
    if (ballX < 2) { botScore++; ballX = 64; ballY = 32; ballSpeedX = 2; delay(300); }

    display.clearDisplay();
    display.setCursor(35, 0); display.print("P1 "); display.print(playerScore); display.print(" : "); display.print(botScore); display.print(" BOT");
    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);
    display.fillRect(2, paddleY, 4, 16, SSD1306_WHITE);
    display.fillRect(122, botY, 4, 16, SSD1306_WHITE);
    display.fillRect(ballX, ballY, 3, 3, SSD1306_WHITE);
    display.display();
    delay(20);
  }
}

// ==================== 4. SPACE INVADERS ====================
void playSpace() {
  int playerX = 60;
  int bulletX = -1, bulletY = -1;
  int enemyX = random(10, 110), enemyY = 5;
  int score = 0;

  while(true) {
    if (checkExitCombo()) return;

    if (digitalRead(BTN_LEFT) == LOW && playerX > 0) playerX -= 4;
    if (digitalRead(BTN_RIGHT) == LOW && playerX < 120) playerX += 4;
    
    if (digitalRead(BTN_UP) == LOW && bulletY < 0) {
      bulletX = playerX + 3;
      bulletY = 50;
    }

    if (bulletY >= 0) bulletY -= 4;

    enemyY += 1;
    if (enemyY > 55) { showGameOver(score); return; }

    if (bulletY >= 0 && bulletX >= enemyX && bulletX <= enemyX + 8 && bulletY <= enemyY + 6) {
      score += 10;
      bulletY = -1;
      enemyX = random(10, 110);
      enemyY = 5;
    }

    display.clearDisplay();
    display.fillRect(playerX, 56, 8, 4, SSD1306_WHITE);
    display.fillRect(enemyX, enemyY, 8, 6, SSD1306_WHITE);
    if (bulletY >= 0) display.fillRect(bulletX, bulletY, 2, 4, SSD1306_WHITE);

    display.setCursor(0, 0); display.print(score);
    display.display();
    delay(20);
  }
}

// ==================== 5. DODGE ====================
void playDodge() {
  int playerX = 60;
  int blockX = random(0, 120);
  int blockY = 0;
  int score = 0;

  while(true) {
    if (checkExitCombo()) return;

    if (digitalRead(BTN_LEFT) == LOW && playerX > 0) playerX -= 4;
    if (digitalRead(BTN_RIGHT) == LOW && playerX < 120) playerX += 4;

    blockY += 3;
    if (blockY > 64) {
      blockY = 0;
      blockX = random(0, 120);
      score += 5;
    }

    if (blockY >= 50 && blockY <= 58 && blockX + 10 >= playerX && blockX <= playerX + 8) {
      showGameOver(score);
      return;
    }

    display.clearDisplay();
    display.fillRect(playerX, 54, 8, 8, SSD1306_WHITE);
    display.fillRect(blockX, blockY, 10, 6, SSD1306_WHITE);

    display.setCursor(0, 0); display.print(score);
    display.display();
    delay(20);
  }
}