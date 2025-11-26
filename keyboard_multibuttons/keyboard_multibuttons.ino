#include <Arduino_Modulino.h>
#include "Keyboard.h"

ModulinoButtons buttons1(0x3E);   
ModulinoButtons buttons2(0x4E);   // Use Address changer firmware to change address

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  Modulino.begin();

  buttons1.begin();
  buttons2.begin();

  buttons1.setLeds(true, true, true);
  buttons2.setLeds(true, true, true);

  Keyboard.begin();

  Serial.println("2 Modulino Buttons: 6 tasti");
}

void loop() {
  buttons1.update();
  buttons2.update();

  // --- Modulino 1 (0x3E) ---
  if (buttons1.isPressed('A')) Keyboard.press('W');
  else Keyboard.release('W');

  if (buttons1.isPressed('B')) Keyboard.press('A');
  else Keyboard.release('A');

  if (buttons1.isPressed('C')) Keyboard.press('S');
  else Keyboard.release('S');

  // --- Modulino 2 (0x4E) ---
  if (buttons2.isPressed('A')) Keyboard.press('D');
  else Keyboard.release('D');

  if (buttons2.isPressed('B')) Keyboard.press(' ');
  else Keyboard.release(' ');

  if (buttons2.isPressed('C')) Keyboard.press('E');
  else Keyboard.release('E');
}
