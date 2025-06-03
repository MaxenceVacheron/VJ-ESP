#include <ESP32Encoder.h>
#include "driver/ledc.h"

#define GREEN_PIN  25
#define RED_PIN  26
#define BLUE_PIN    33
#define WHITE_PIN   32

int LAST_RED_INTENSITY = 0;
int LAST_GREEN_INTENSITY = 0;
int LAST_BLUE_INTENSITY = 0;
int LAST_WHITE_INTENSITY = 0;

// === Pin Assignments ===
// Encoder 1
#define CLK1 4
#define DT1  2
#define SW1  15

// Encoder 2
#define CLK2 19
#define DT2  18
#define SW2  5

// Encoder 3
#define CLK3 23
#define DT3  22
#define SW3  21

// Encoder 4
#define CLK4 14
#define DT4  27
#define SW4  13

// === Encoder instances ===
ESP32Encoder enc1;
ESP32Encoder enc2;
ESP32Encoder enc3;
ESP32Encoder enc4;

// === State tracking ===
long lastPos1 = 0, lastPos2 = 0, lastPos3 = 0, lastPos4 = 0;
bool lastSW1 = HIGH, lastSW2 = HIGH, lastSW3 = HIGH, lastSW4 = HIGH;

void setup() {
  Serial.begin(9600);

  ledcAttach(RED_PIN,     5000, 8);  // 5kHz, 8-bit
  ledcAttach(GREEN_PIN,   5000, 8);
  ledcAttach(BLUE_PIN,    5000, 8);
  ledcAttach(WHITE_PIN,   5000, 8);
  // Enable the encoder hardware
  // ESP32Encoder::useInternalWeakPullResistors = false;

  // Attach encoders
  enc1.attachHalfQuad(DT1, CLK1);
  enc2.attachHalfQuad(DT2, CLK2);
  enc3.attachHalfQuad(DT3, CLK3);
  enc4.attachHalfQuad(DT4, CLK4);

  enc1.setCount(0);
  enc2.setCount(0);
  enc3.setCount(0);
  enc4.setCount(0);

  // Set button pins
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);

  ledcWrite(RED_PIN,   0); 
  ledcWrite(GREEN_PIN, 0);
  ledcWrite(BLUE_PIN,  0);
  ledcWrite(WHITE_PIN, 0);
}

void loop() {
  // --- Encoder 1 --- RRRRRRR
  long pos1 = enc1.getCount();
  if (pos1 != lastPos1) {
    Serial.print("Encoder 1: "); Serial.println(pos1);
    if (pos1 < lastPos1) {
      if (LAST_RED_INTENSITY > 24) {
        LAST_RED_INTENSITY = LAST_RED_INTENSITY - 24;
      } else {
        LAST_RED_INTENSITY = 0;
      }
      ledcWrite(RED_PIN,   LAST_RED_INTENSITY);
    }
    if (pos1 > lastPos1) {
      if (LAST_RED_INTENSITY < 231) {
        LAST_RED_INTENSITY = LAST_RED_INTENSITY + 24;
      } else {
        LAST_RED_INTENSITY = 255;
      }
      ledcWrite(RED_PIN,   LAST_RED_INTENSITY);
    }
    Serial.print("RED : "); Serial.println(LAST_RED_INTENSITY);
    lastPos1 = pos1;
  }
  if (digitalRead(SW1) == LOW && lastSW1 == HIGH) {
    Serial.println("Encoder 1111 Button Pressed");
    delay(50);
  }
  lastSW1 = digitalRead(SW1);

  // --- Encoder 2 --- GGGGGG
  long pos2 = enc2.getCount();
  if (pos2 != lastPos2) {
    Serial.print("Encoder 2222: "); Serial.println(pos2);
    if (pos2 < lastPos2) {
      if (LAST_GREEN_INTENSITY > 24) {
        LAST_GREEN_INTENSITY = LAST_GREEN_INTENSITY - 24;
      } else {
        LAST_GREEN_INTENSITY = 0;
      }
      ledcWrite(GREEN_PIN,   LAST_GREEN_INTENSITY);
    }
    if (pos2 > lastPos2) {
      if (LAST_GREEN_INTENSITY < 231) {
        LAST_GREEN_INTENSITY = LAST_GREEN_INTENSITY + 24;
      } else {
        LAST_GREEN_INTENSITY = 255;
      }
      ledcWrite(GREEN_PIN,   LAST_GREEN_INTENSITY);
    }
    Serial.print("GREEN : "); Serial.println(LAST_GREEN_INTENSITY);
    lastPos2 = pos2;
  }
  if (digitalRead(SW2) == LOW && lastSW2 == HIGH) {
    Serial.println("Encoder 2 Button Pressed");
    delay(50);
  }
  lastSW2 = digitalRead(SW2);

  // --- Encoder 3 --- BBBBB
  long pos3 = enc3.getCount();
  if (pos3 != lastPos3) {
    Serial.print("Encoder 3: "); Serial.println(pos3);
    if (pos3 < lastPos3) {
      if (LAST_BLUE_INTENSITY > 24) {
        LAST_BLUE_INTENSITY = LAST_BLUE_INTENSITY - 24;
      } else {
        LAST_BLUE_INTENSITY = 0;
      }
      ledcWrite(BLUE_PIN,   LAST_BLUE_INTENSITY);
    }
    if (pos3 > lastPos3) {
      if (LAST_BLUE_INTENSITY < 231) {
        LAST_BLUE_INTENSITY = LAST_BLUE_INTENSITY + 24;
      } else {
        LAST_BLUE_INTENSITY = 255;
      }
      ledcWrite(BLUE_PIN,   LAST_BLUE_INTENSITY);
    }
    Serial.print("BLUE : "); Serial.println(LAST_BLUE_INTENSITY);
    lastPos3 = pos3;
  }
  if (digitalRead(SW3) == LOW && lastSW3 == HIGH) {
    Serial.println("Encoder 3 Button Pressed");
    delay(50);
  }
  lastSW3 = digitalRead(SW3);

  // --- Encoder 4 --- WWWWW
  long pos4 = enc4.getCount();
  if (pos4 != lastPos4) {
    Serial.print("Encoder 4: "); Serial.println(pos4);
    if (pos4 < lastPos4) {
      if (LAST_WHITE_INTENSITY > 24) {
        LAST_WHITE_INTENSITY = LAST_WHITE_INTENSITY - 24;
      } else {
        LAST_WHITE_INTENSITY = 0;
      }
      ledcWrite(WHITE_PIN,   LAST_WHITE_INTENSITY);
    }
    if (pos4 > lastPos4) {
      if (LAST_WHITE_INTENSITY < 231) {
        LAST_WHITE_INTENSITY = LAST_WHITE_INTENSITY + 24;
      } else {
        LAST_WHITE_INTENSITY = 255;
      }
      ledcWrite(WHITE_PIN,   LAST_WHITE_INTENSITY);
    }
    Serial.print("WHITE : "); Serial.println(LAST_WHITE_INTENSITY);
    lastPos4 = pos4;
  }
  if (digitalRead(SW4) == LOW && lastSW4 == HIGH) {
    Serial.println("Encoder 4 Button Pressed");
    delay(50);
  }
  lastSW4 = digitalRead(SW4);

  delay(10);  // Short delay to avoid flooding serial
}
