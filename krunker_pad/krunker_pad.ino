/*
  🎮 Krunker Pad con Arduino Nano R4 e Arduino Modulino
  
  Questo programma trasforma un Arduino Nano R4 con i moduli Modulino (Buttons, Knob e Movement) 
  in un controller USB per il gioco Krunker (krunker.io).

  Funzioni principali:
  - **Movement:** Simula il movimento del mouse (rotazione orizzontale) e i tasti W/S (movimento avanti/indietro).
  - **Buttons:** Mappa i pulsanti a 'Sparo' (Click Sinistro Mouse), 'Salto' (Spazio) e 'Accovacciarsi' (Shift).
  - **Knob:** Simula i movimenti del mouse Su/Giù per alzare/abbassare la visuale e il cambio arma (Click del Knob).
*/

#include <Arduino_Modulino.h>
#include "Mouse.h"
#include "Keyboard.h"

// 🔄 Oggetti per l'interazione con i moduli Modulino
ModulinoMovement movement;
ModulinoButtons buttons;
ModulinoKnob knob;

// 📊 Variabili per i dati dell'accelerometro (ModulinoMovement) e le impostazioni del Knob
float x, y, z; // Variazioni sull'asse x, y, z rilevate dal modulo Movement
int lastKnobPos = 0; // Posizione precedente del Knob per calcolare la differenza
const float knowbSensitivity = 50.0; // Sensibilità per la rotazione (strafe) controllata dal Knob
const float threshold = 0.15; // Soglia minima per considerare un movimento (per ignorare piccole variazioni)
const float sensitivity = 100.0; // Sensibilità generale per l'input da ModulinoMovement

void setup() {
  Serial.begin(115200);

  Modulino.begin(); // Inizializza la libreria Modulino

  // Inizializzazione dei singoli moduli Modulino
  movement.begin();
  buttons.begin();
  knob.begin();        

  // 💡 Accende i LED sui pulsanti (opzionale, per feedback visivo)
  buttons.setLeds(true, true, true);

  delay(1000); // Breve pausa per stabilizzare i moduli

  // 🖱️ Inizializzazione delle interfacce HID (Human Interface Device) USB
  Mouse.begin();
  Keyboard.begin();
  
  Serial.println("Arduino Nano R4: Krunker Pad - Controller Inizializzato");

  // Cattura la posizione iniziale del Knob
  lastKnobPos = knob.get();
}

void loop() {
  /* ----------------------- 🧭 MOVIMENTO VISUALE E BASE (MODULINO MOVEMENT) ----------------------- */
  movement.update();
  x = movement.getX(); // L'asse X del Modulino controlla la rotazione orizzontale (Mouse L/R)
  y = movement.getY(); // L'asse Y del Modulino controlla il movimento avanti/indietro (Tastiera W/S)
  z = movement.getZ(); // L'asse Z è disponibile, ma non usato in questo sketch per Krunker


  int moveX = 0; // Offset di movimento orizzontale del mouse (rotazione)
  int moveY = 0; // Segnale per il movimento avanti/indietro (W/S)

  // 📐 Calcolo del movimento: applichiamo soglia e sensibilità
  if (fabs(x) > threshold) moveX = int(-x * sensitivity); // Rotazione L/R del mouse
  if (fabs(y) > threshold) moveY = int(-y * sensitivity); // Movimento Avanti/Indietro

  // 🖱️ Rotazione del Mouse (Look)
  if (moveX != 0) {
    Mouse.move(moveX, 0); // Sposta il cursore solo sull'asse X
  }

  // ⌨️ Movimento Avanti (W) / Indietro (S)
  if (moveY > 0) {
    Keyboard.press('w');
    Keyboard.release('s');
  } else if (moveY < 0) {
    Keyboard.press('s');
    Keyboard.release('w');
  } else {
    // Rilascia entrambi se il movimento è nullo
    Keyboard.release('s');
    Keyboard.release('w');
  }


  /* ----------------------- 🕹️ GESTIONE PULSANTI (MODULINO BUTTONS) --------------------------- */
  // Aggiorna lo stato dei pulsanti solo se ci sono stati cambiamenti
  if (buttons.update()) {

    // 🔫 Pulsante 'B' (Solitamente il più accessibile) -> Sparo (Click Sinistro Mouse)
    if (buttons.isPressed('B')) Mouse.press(MOUSE_LEFT);
    else Mouse.release(MOUSE_LEFT);

    // ⏫ Pulsante 'A' -> Salto (Tasto Spazio)
    if (buttons.isPressed('A')) Keyboard.press(' ');
    else Keyboard.release(' ');

    // 🔽 Pulsante 'C' -> Accovacciarsi (Tasto Shift Destro, o Left Shift)
    if (buttons.isPressed('C')) Keyboard.press(KEY_RIGHT_SHIFT);
    else Keyboard.release(KEY_RIGHT_SHIFT);
  }

  /* ----------------------- ⚙️ GESTIONE KNOB → CAMBIO ARMA / STRAFE A/D ---------------------------- */

  int pos = knob.get(); // Legge la posizione attuale del Knob
  // Calcola la variazione (delta) moltiplicata per la sensibilità del Knob
  // Nota: Questo delta può essere usato per lo strafing (A/D) o per muovere il mouse sull'asse Y (Mouse.move(0, delta))
  // Lo lasciamo come Mouse.move(0, delta) per semplicità, ma andrebbe sostituito con A/D press/release per lo strafing.
  int delta = (pos - lastKnobPos) * knowbSensitivity; 
  lastKnobPos = pos; // Aggiorna l'ultima posizione

  if (delta != 0) {
      // ⚠️ ATTENZIONE: Se si desidera lo strafing (A/D) invece di muovere il mouse sull'asse Y, 
      // questa sezione andrebbe riscritta per premere 'A' o 'D' usando Keyboar.press()
      Mouse.move(0, delta); // Muove il mouse verticalmente (pitch). Potrebbe essere non ideale per Krunker.
  }

  // 🔁 Click del Knob → Cambio Arma (Tasto 'E')
  if (knob.isPressed()) {
      Keyboard.press('e');
      delay(50); // Breve ritardo per registrare la pressione
      Keyboard.release('e');
  }

}