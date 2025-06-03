// Define GPIOs for RGBW
#include "driver/ledc.h"

#define RED_PIN     25
#define GREEN_PIN   33
#define BLUE_PIN    32
#define WHITE_PIN   35

void fadeExample() {
  // Fade RED from 0 to 255 in 2 seconds
  ledcFade(RED_PIN, 0, 255, 2000);
  delay(2500); // Wait until fade completes

  // Fade RED back down
  ledcFade(RED_PIN, 255, 0, 2000);
  delay(2500);
}



void setup() {
  // Attach pins using new LEDC API (channel is assigned automatically)
  ledcAttach(RED_PIN,     5000, 8);  // 5kHz, 8-bit
  ledcAttach(GREEN_PIN,   5000, 8);
  ledcAttach(BLUE_PIN,    5000, 8);
  ledcAttach(WHITE_PIN,   5000, 8);
}

void loop() {
  // Manual write
  ledcWrite(RED_PIN,   255);  // Full red
  ledcWrite(GREEN_PIN, 0);
  ledcWrite(BLUE_PIN,  0);
  ledcWrite(WHITE_PIN, 64);  // Low white
  delay(1000);

  ledcWrite(RED_PIN,   0);
  ledcWrite(GREEN_PIN, 255);  // Full green
  ledcWrite(BLUE_PIN,  0);
  ledcWrite(WHITE_PIN, 128);  // Medium white
  delay(1000);

  ledcWrite(RED_PIN,   0);
  ledcWrite(GREEN_PIN, 0);
  ledcWrite(BLUE_PIN,  255);  // Full blue
  ledcWrite(WHITE_PIN, 255);  // Full white
  delay(1000);
  fadeExample();

}
