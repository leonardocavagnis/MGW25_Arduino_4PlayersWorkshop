/*
  Nano R4 HID Keyboard controlled by Modulino Buttons
  Press buttons A, B, or C to send predefined keystrokes to the computer
*/

#include "Keyboard.h"
#include <Arduino_Modulino.h>

// Create a ModulinoButtons object
ModulinoButtons buttons;

// State variables for LEDs
bool led_a = true;
bool led_b = true;
bool led_c = true;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  while(!Serial) ;

  // Initialize Modulino and buttons
  Modulino.begin();
  buttons.begin();

  // Turn on all LEDs initially
  buttons.setLeds(true, true, true);

  // Wait 2 seconds before starting Keyboard
  delay(2000);
  Keyboard.begin();
  Serial.println("Keyboard HID initialized.");
}

void loop() {
  // Check for new button events
  if (buttons.update()) {
    if (buttons.isPressed('A')) {
      Serial.println("Button A pressed!");

      // Send HID message for Button A
      Keyboard.print("Hello from Button A");
      Keyboard.press(KEY_RETURN);
      delay(50);
      Keyboard.releaseAll();
    } 
    else if (buttons.isPressed('B')) {
      Serial.println("Button B pressed!");

      // Send HID message for Button B
      Keyboard.print("Hello from Button B");
      Keyboard.press(KEY_RETURN);
      delay(50);
      Keyboard.releaseAll();
    } 
    else if (buttons.isPressed('C')) {
      Serial.println("Button C pressed!");
      
      // Send HID message for Button C
      Keyboard.print("Hello from Button C");
      Keyboard.press(KEY_RETURN);
      delay(50);
      Keyboard.releaseAll();
    }
  }
}