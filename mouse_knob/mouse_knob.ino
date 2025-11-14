/*
  Nano R4 HID Mouse controlled by a Modulino Knob
  Rotate the knob to move the mouse left or right
  Press the knob to perform a left-click
*/

#include <Arduino_Modulino.h>
#include "Mouse.h"

ModulinoKnob knob;

int lastPosition = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { }
  
  // Initialize the knob module
  Modulino.begin();
  knob.begin();
  
  // Wait 2 seconds for safety
  delay(2000);

  // Initialize mouse HID
  Mouse.begin();
  Serial.println("- Nano R4 Mouse via Knob ready!");
  
  // Read initial knob position
  lastPosition = knob.get();
}

void loop() {
  int position = knob.get();
  bool click = knob.isPressed();

  // Calculate difference
  int delta = position - lastPosition;

  // If the knob is rotated right or left, move the mouse
  if (delta != 0) {
    Mouse.move(delta > 0 ? 100 : -100, 0); // horizontal movement
    Serial.print("Mouse moved: ");
    Serial.println(delta > 0 ? "right" : "left");
    
    lastPosition = position; // update the position
  }

  // If the knob is pressed, perform a mouse click
  if (click) {
    Mouse.click(MOUSE_LEFT);
    Serial.println("Mouse clicked!");
    
    // Wait until release to avoid repeated clicks
    while (knob.isPressed()) {
      delay(10);
    }
  }
}