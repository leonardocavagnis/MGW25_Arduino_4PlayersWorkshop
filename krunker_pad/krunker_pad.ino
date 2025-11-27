/*
  Pad per Krunker (krunker.io), utilizza Arduino Nano R4 e vari Arduino Modulino (Buttons, Knob e Movement)
  - Utilizza Modulino Movement per controllare il movimento del mouse tramite Tastiera (per avanti/indietro) e Mouse (sinistra/destra)
  - Utilizza Modulino Buttons per mappare i pulsanti al click del mouse (sparo) e ai tasti Spazio (salto) e Shift (accovacciarsi) della Tastiera
  - Utilizza Modulino Knob per simulare il movimento laterale A/D (destra/sinistra) per un gameplay fluido
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
const float knowbSensitivity = 50.0;
const float threshold = 0.15;
const float sensitivity = 100.0;

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
  x = movement.getX(); // x is for turning left/right via Mouse left/right
  y = movement.getY(); // y is for moving forward/back via Keyboard W/S
  z = movement.getZ(); // z 


  int moveX = 0;
  int moveY = 0;
  int moveZ = 0;

  if (fabs(x) > threshold) moveX = int(-x * sensitivity);
  if (fabs(y) > threshold) moveY = int(-y * sensitivity);

  if (moveX != 0) {
    Mouse.move(moveX, 0);
  }

  if (moveY > 0) {
    Keyboard.press('W');
    Keyboard.release('S');
  } else if (moveY < 0) {
    Keyboard.press('S');
    Keyboard.release('W');
  } else {
    Keyboard.release('S');
    Keyboard.release('W');
  }



  /* ----------------------- TASTI SPACE AND SHIFT e CLICK MOUSE con MODULINO BUTTONS --------------------------- */

  if (buttons.update()) {

    // shooting
    if (buttons.isPressed('B')) Mouse.press(MOUSE_LEFT);
    else Mouse.release(MOUSE_LEFT);

    // jumping
    if (buttons.isPressed('A')) Keyboard.press(' ');
    else Keyboard.release(' ');

    // crouching
    if (buttons.isPressed('C')) Keyboard.press(KEY_RIGHT_SHIFT);
    else Keyboard.release(KEY_RIGHT_SHIFT);

  }

  /* ----------------------- GESTIONE KNOB → A / D ---------------------------- */

  int pos = knob.get();
  int delta = (pos - lastKnobPos) * knowbSensitivity;
  lastKnobPos = pos;

  if (delta != 0) {
      Serial.print("Moving mouse");
      Serial.println(delta);
      Mouse.move(0, delta);
  }

  // use knob click to change weapon
  if (knob.isPressed()) {
      Keyboard.press('E');
      delay(50);
      Keyboard.release('E');
  }

}