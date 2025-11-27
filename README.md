# 🎮 MGW25 - Arduino&4Players Workshop
Milano Games Week 2025 – 4 Players Workshop in collaborazione con Arduino

Questo repository contiene alcuni programmi di esempio per Arduino (chiamati anche sketch) e risorse per creare il tuo joystick USB personalizzato utilizzando Arduino Nano R4 e Modulino.

## ⚒️ Componenti
Nel workshop vengono utilizzati i seguenti componenti:
- 1 x Arduino Nano R4
- 3 x Modulino Buttons
- 2 x Modulino Knobs
- 1 x Modulino Movement

I partecipanti possono utilizzare tutti i componenti insieme o selezionarne solo alcuni per il proprio progetto.

## 🚀 Come iniziare subito

_Vuoi creare il tuo primo joystick Arduino in 5 minuti?_

👉 Leggi il file [INSTRUCTIONS.md](/INSTRUCTIONS.md) per seguire passo dopo passo il montaggio, la programmazione e il test del controller.

## 🎯 Cosa puoi fare dopo
Dopo il workshop, puoi continuare a sperimentare e personalizzare il tuo joystick:
- Creare joystick più complessi combinando uno o più Modulino tra loro.
- Modificare la mappatura dei tasti e la sensibilità dei controlli.
- Sperimentare nuove logiche HID e costruire controller per altri giochi online o applicazioni interattive.

## 📁 Esempi e progetti
Gli sketch di esempio sono presenti nella cartella [examples](/examples).

Ogni sketch rappresenta un punto di partenza per ispirare la creazione di joystick personalizzati, combinando uno o più Modulino tra loro.

## ⚠️ Troubleshooting

### Usare più Modulino della stessa tipologia

Per usare più Modulino uguali (es. due Modulino Buttons):

1. Cambia l’indirizzo di ciascun Modulino con il [Firmware Address Changer](https://github.com/arduino-libraries/Arduino_Modulino/blob/main/examples/Utilities/AddressChanger/AddressChanger.ino).

2. Dichiarali nello sketch con gli indirizzi scelti, ad esempio:

```
ModulinoButtons buttons1(0x3E);
ModulinoButtons buttons2(0x4E);
```

Ogni Modulino deve avere un indirizzo unico.

3. Usali nello sketch come normali Modulino:

```
buttons1.begin();
buttons2.begin();

buttons1.update();
buttons2.update();
```

## 📖 Riferimenti
- [Arduino Nano R4 - Documentazione Ufficiale](https://docs.arduino.cc/tutorials/nano-r4/user-manual/)
- [Modulino Libreria](https://docs.arduino.cc/libraries/arduino_modulino/)
- [Keyboard Libreria](https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/)
- [Mouse Libreria](https://docs.arduino.cc/libraries/mouse/)

## 👨🏻‍💻 Autori 
- [Leonardo Cavagnis](https://github.com/leonardocavagnis)
- [Christian Sarnataro](https://github.com/csarnataro)
