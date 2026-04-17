#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C
display(U8G2_R0, U8X8_PIN_NONE);
// ===================================== // Settings // =====================================
unsigned long lastBlink = 0;
unsigned long lastMovement = 0;
unsigned long lastExpressionChange = 0;
unsigned long idleTimer = 0;
unsigned long lastMoodChange = 0;
unsigned long moodInterval = 5000;

bool isBlinking = false;
int yOffset = 0;
int direction = 1;
int eyeOffsetX = 0;  // Expressions

enum Mood {
  NEUTRAL,
  HAPPY,
  SAD,
  LOVE,
  EXCITED,
  SLEEP
};
Mood mood = NEUTRAL;
// =====================================
// Eye drawing function
// =====================================

void drawEyes(bool blinkState) {
  int leftEyeX = 35 + eyeOffsetX;
  int rightEyeX = 75 + eyeOffsetX;

  if (blinkState) {
    display.drawBox(leftEyeX, 22 + yOffset, 18, 4);
    display.drawBox(rightEyeX, 22 + yOffset, 18, 4);
    return;
  }
  // // Open cute rounded eyes
  display.drawRBox(leftEyeX, 12 + yOffset, 18, 24, 5);
  display.drawRBox(rightEyeX, 12 + yOffset, 18, 24, 5);
}

void drawHeart(int x, int y) {
  // Upper curves (bigger)
  display.drawRBox(x + 2, y + 5, 11, 10, 5);
  display.drawRBox(x + 12, y + 5, 11, 10, 5);

  // Lower triangle fill (bigger)
  display.drawTriangle(
    x + 2, y + 12,   // left corner under curve
    x + 22, y + 12,  // right corner
    x + 12, y + 24   // bottom point
  );
}

void drawSurprisedMouth(int x, int y) {
  display.drawCircle(x, y, 6);  // 6 pixel radius
}


void drawHeartVector(bool blinkState) {
  bool loveMode = true;
  int leftEyeX = 35 + eyeOffsetX;
  int rightEyeX = 75 + eyeOffsetX;

  // Dua lingkaran
  if (blinkState) {
    display.drawBox(leftEyeX, 25, 18, 4);
    display.drawBox(rightEyeX, 25, 18, 4);
    return;
  }

  if (loveMode) {
    drawHeart(leftEyeX, 10);
    drawHeart(rightEyeX, 10);
  } else {
    display.drawRBox(leftEyeX, 12, 18, 24, 5);
    display.drawRBox(rightEyeX, 12, 18, 24, 5);
  }
}


// =====================================
// Mouth expressions
// =====================================

void drawMouth() {
  int x0 = 50, y0 = 50;
  int x1 = 64, y1 = 70;
  int x2 = 78, y2 = 50;

  int x3 = 50, y3 = 60;
  int x4 = 64, y4 = 60;
  int x5 = 78, y5 = 60;

  int x6 = 50, y6 = 60;
  int x7 = 64, y7 = 50;
  int x8 = 78, y8 = 60;

  int x9 = 50, y9 = 50;
  int x10 = 64, y10 = 60;
  int x11 = 78, y11 = 50;


  switch (mood) {
    case NEUTRAL:
      drawEyes(isBlinking);
      for (int t = 0; t < 3; t++) {
        display.drawLine(50, 50 + t, 78, 50 + t);
      }
      break;

    case LOVE:
      drawHeartVector(isBlinking);
       for (float t = 0; t <= 1; t += 0.001) {
        int x = (1 - t) * (1 - t) * x9 + 2 * (1 - t) * t * x10 + t * t * x11;
        int y = (1 - t) * (1 - t) * y9 + 2 * (1 - t) * t * y10 + t * t * y11;
        display.drawBox(x, y, 3, 3);
      }
      break;

    case EXCITED:
      drawEyes(isBlinking);
      for (int t = 0; t < 3; t++) {
        display.drawLine(50, 50 + t, 78, 50 + t);
      }

      for (float t = 0; t <= 1; t += 0.001) {
        int x = (1 - t) * (1 - t) * x0 + 2 * (1 - t) * t * x1 + t * t * x2;
        int y = (1 - t) * (1 - t) * y0 + 2 * (1 - t) * t * y1 + t * t * y2;
        display.drawBox(x, y, 3, 3);
      }
      break;

    case HAPPY:
      drawEyes(isBlinking);
      for (float t = 0; t <= 1; t += 0.001) {
        int x = (1 - t) * (1 - t) * x9 + 2 * (1 - t) * t * x10 + t * t * x11;
        int y = (1 - t) * (1 - t) * y9 + 2 * (1 - t) * t * y10 + t * t * y11;
        display.drawBox(x, y, 3, 3);
      }
      break;

    case SAD:
      drawEyes(isBlinking);
      for (float t = 0; t <= 1; t += 0.0001) {
        int x = (1 - t) * (1 - t) * x6 + 2 * (1 - t) * t * x7 + t * t * x8;
        int y = (1 - t) * (1 - t) * y6 + 2 * (1 - t) * t * y7 + t * t * y8;
        display.drawBox(x, y, 3, 3);
      }
      break;

    case SLEEP:
      int leftEyeX = 35 + eyeOffsetX;
      int rightEyeX = 75 + eyeOffsetX;

      display.drawBox(leftEyeX, 22 + yOffset, 18, 4);
      display.drawBox(rightEyeX, 22 + yOffset, 18, 4);
      break;
  }
}

// =====================================
// Animation mood
// =====================================

void updateMood() {
  unsigned long now = millis();

  if (now - lastMoodChange > moodInterval) {
    mood = (Mood)random(0, 4);  // 0-3 enum random: NEUTRAL, HAPPY, SAD, SLEEP

    // Set interval berikutnya random antara 5 - 20 detik
    moodInterval = random(5000, 20000);

    lastMoodChange = now;
  }
}

// =====================================
// Animation logic
// =====================================

void updateAnimation() {
  // Floating movement
  yOffset += direction;
  if (yOffset > 3 || yOffset < -3) direction *= -1;
  // Blink logic
  if (!isBlinking && millis() - lastBlink > random(2000, 6000)) {
    isBlinking = true;
    lastBlink = millis();
  }
  if (isBlinking && millis() - lastBlink > 150) {
    isBlinking = false;
    lastBlink = millis();
  }

  // Eye movement random
  if (millis() - lastMovement > random(1500, 3000)) {
    eyeOffsetX = random(-3, 4);
    lastMovement = millis();
  }
}

// =====================================
// Draw frame
// =====================================

void render() {
  display.clearBuffer();
  drawMouth();
  display.sendBuffer();
}

// =====================================
// Setup
// =====================================

void setup() {
  display.begin();
  display.clearBuffer();
  idleTimer = millis();
  render();
}

// =====================================
// Loop
// =====================================

void loop() {
  updateMood();
  updateAnimation();
  render();
  delay(50);
}
