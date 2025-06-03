#include <ESP32Encoder.h>

#define CLK 4 // Encoder CLK
#define DT  2 // Encoder DT
#define SW 15 // Encoder button (SW)

ESP32Encoder encoder;

long lastPosition = 0;
bool lastButtonState = HIGH;

void setup () {
  Serial.begin(9600);

  // Encoder setup
  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(0);

  // Button setup
  pinMode(SW, INPUT_PULLUP);
}

void loop () {
  // --- Encoder position ---
  long newPosition = encoder.getCount();
  if (newPosition != lastPosition) {
    Serial.print("Encoder Position: ");
    Serial.println(newPosition);
    lastPosition = newPosition;
  }

  // --- Button press detection ---
  bool currentButtonState = digitalRead(SW);
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    Serial.println("Button Pressed!");
    delay(50); // Simple debounce
  }
  lastButtonState = currentButtonState;

  delay(10);  // Reduce CPU usage
}
