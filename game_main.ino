#include <Arduino.h>
#include <U8g2lib.h>

#define BUTTON_UP     2
#define BUTTON_DOWN   3
#define BUTTON_LEFT   4
#define BUTTON_RIGHT  5
#define BUTTON_A      6
#define BUTTON_B      7
#define BUZZER_PIN    9

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

int x = 64;
int y = 32;

void setup() {
  u8g2.begin();
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  readInput();
  draw();
  delay(50);
}

void readInput() {
  if (digitalRead(BUTTON_UP) == LOW)    y -= 2;
  if (digitalRead(BUTTON_DOWN) == LOW)  y += 2;
  if (digitalRead(BUTTON_LEFT) == LOW)  x -= 2;
  if (digitalRead(BUTTON_RIGHT) == LOW) x += 2;

  if (digitalRead(BUTTON_A) == LOW) tone(BUZZER_PIN, 1000, 100);
  if (digitalRead(BUTTON_B) == LOW) tone(BUZZER_PIN, 1500, 100);

  // boundaries
  if (x < 0) x = 0;
  if (x > 128) x = 128;
  if (y < 0) y = 0;
  if (y > 64) y = 64;
}

void draw() {
  u8g2.clearBuffer();
  u8g2.drawStr(5, 10, "Arduino Game!");
  u8g2.drawBox(x, y, 8, 8);
  u8g2.sendBuffer();
}