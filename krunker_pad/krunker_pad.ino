/*
  Krunker Pad using Arduino Nano R4 Modulino (krunker.io)
  - Uses ModulinoMovement to control mouse movement
  - Uses ModulinoButtons to map buttons to W, S, and mouse click
  - Uses ModulinoKnob to simulate A/D lateral movement for smooth gameplay
*/

#include <Arduino_Modulino.h>
#include "Mouse.h"
#include "Keyboard.h"

ModulinoMovement movement;
ModulinoButtons buttons;
ModulinoKnob knob; 

// Variables to store accelerometer data
float x, y, z;
int lastKnobPos = 0;

void setup() {
  Serial.begin(115200);
  while(!Serial) { }

  Modulino.begin();

  movement.begin();
  buttons.begin();
  knob.begin();        

  buttons.setLeds(true, true, true);

  delay(2000);

  Mouse.begin();
  Keyboard.begin();
  
  Serial.println("Nano R4: Krunker Pad");

  lastKnobPos = knob.get();
}

void loop() {
  /* ----------------------- MOVIMENTO MOUSE con MODULINO MOVEMENT ----------------------- */
  movement.update();
  x = movement.getX();
  y = movement.getY();
  z = movement.getZ();

  const float threshold = 0.15;
  const float sensitivity = 100.0;

  int moveX = 0;
  int moveY = 0;

  if (fabs(x) > threshold) moveX = int(-x * sensitivity);
  if (fabs(y) > threshold) moveY = int(-y * sensitivity);

  if (moveX != 0 || moveY != 0) {
    Mouse.move(moveX, moveY);
  }

  /* ----------------------- TASTI W-S e CLICK MOUSE con MODULINO BUTTONS --------------------------- */

  if (buttons.update()) {

    if (buttons.isPressed('A')) Keyboard.press('W');
    else Keyboard.release('W');

    if (buttons.isPressed('B')) Mouse.press(MOUSE_LEFT);
    else Mouse.release(MOUSE_LEFT);

    if (buttons.isPressed('C')) Keyboard.press('S');
    else Keyboard.release('S');
  }

  /* ----------------------- GESTIONE KNOB → A / D ---------------------------- */

  int pos = knob.get();
  int delta = pos - lastKnobPos;
  lastKnobPos = pos;

  if (delta != 0) {
    if (delta > 0) {
      // Rotazione destra → D
      Keyboard.press('D');
      Keyboard.release('A');
      Serial.println("Knob → Right (D)");
    }
    else {
      // Rotazione sinistra → A
      Keyboard.press('A');
      Keyboard.release('D');
      Serial.println("Knob → Left (A)");
    }
  } else {
    Keyboard.release('A');
    Keyboard.release('D');
  }

}