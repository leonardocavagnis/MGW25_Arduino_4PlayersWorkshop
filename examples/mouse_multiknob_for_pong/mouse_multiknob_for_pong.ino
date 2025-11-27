/**
Utilizzo di 2 knob per giocare in 2 giocatori a Pong online
https://freepong.org/
*/


#include <Arduino_Modulino.h>
#include "Keyboard.h"

ModulinoKnob knobPlayer1(0x3A);
ModulinoKnob knobPlayer2(0x4A);

int lastPosPlayer1 = 0;
int lastPosPlayer2 = 0;

void setup() {
  Serial.begin(115200);

  Modulino.begin();
  knobPlayer1.begin();
  knobPlayer2.begin();

  Keyboard.begin();
  delay(1000);

  Serial.println("Nano R4: Dual Knob Mouse ready!");

  lastPosPlayer1 = knobPlayer1.get();
  lastPosPlayer2 = knobPlayer2.get();
}

void loop() {
  int posPlayer1 = knobPlayer1.get();
  int posPlayer2 = knobPlayer2.get();
  // Delta X → movimento giocatore 1
  int deltaX = posPlayer1 - lastPosPlayer1;
  Serial.print(knobPlayer1.get());
  Serial.print(" - ");
  Serial.println(lastPosPlayer1);
  if (deltaX > 0) {
    Keyboard.press('s');
    Keyboard.release('x');
  } else if (deltaX < 0) {
    Keyboard.press('x');sxssxs
    Keyboard.release('s');
  } else {
    Keyboard.release('x');
    Keyboard.release('s');
  }

  // Delta Y → movimento giocatore 2
  int deltaY = posPlayer2 - lastPosPlayer2;
  if (deltaY > 0) {
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);
  } else if (deltaY < 0) {
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.release(KEY_UP_ARROW);

  } else {
    Keyboard.release(KEY_UP_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);
  }
  lastPosPlayer1 = posPlayer1;
  lastPosPlayer2 = posPlayer2;

}