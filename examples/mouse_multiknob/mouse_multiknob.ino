#include <Arduino_Modulino.h>
#include "Mouse.h"

ModulinoKnob knobX(0x3A);
ModulinoKnob knobY(0x4A);

int lastPosX = 0;
int lastPosY = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  Modulino.begin();
  knobX.begin();
  knobY.begin();

  delay(2000);

  Mouse.begin();
  Serial.println("Nano R4: Dual Knob Mouse ready!");

  lastPosX = knobX.get();
  lastPosY = knobY.get();
}

void loop() {
  int posX = knobX.get();
  int posY = knobY.get();

  // Delta X → movimento orizzontale
  int deltaX = posX - lastPosX;
  if (deltaX != 0) {
    Mouse.move(deltaX > 0 ? 100 : -100, 0); // dx / sx
    Serial.print("Mouse moved: ");
    Serial.println(deltaX > 0 ? "right" : "left");
    lastPosX = posX;
  }

  // Delta Y → movimento verticale
  int deltaY = posY - lastPosY;
  if (deltaY != 0) {
    Mouse.move(0, deltaY > 0 ? 100 : -100); // giù / su
    Serial.print("Mouse moved: ");
    Serial.println(deltaY > 0 ? "down" : "up");
    lastPosY = posY;
  }

  // Click con pressione dei knob
  if (knobX.isPressed() || knobY.isPressed()) {
    Mouse.click(MOUSE_LEFT);
    Serial.println("Mouse clicked!");
    while (knobX.isPressed() || knobY.isPressed()) {
      delay(10);
    }
  }
}