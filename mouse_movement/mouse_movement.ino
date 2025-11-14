/*
  Nano R4 HID Mouse controlled by Modulino Movement
  Tilt the Modulino to move the mouse horizontally (X) and vertically (Y)
*/

#include <Arduino_Modulino.h>
#include "Mouse.h"

// Create a ModulinoMovement
ModulinoMovement movement;

// Variables to store accelerometer data
float x, y, z;

void setup() {
  Serial.begin(115200);
  while(!Serial) { }

  // Initialize Modulino I2C communication
  Modulino.begin();

  // Detect and connect to movement sensor module
  movement.begin();

  // Wait 2 seconds for safety
  delay(2000);

  // Initialize mouse HID
  Mouse.begin();
  Serial.println("Nano R4 Mouse via Modulino Movement ready!");
}

void loop() {
  // Read new movement data from the sensor
  movement.update();

  // Get acceleration values
  x = movement.getX(); // X-axis tilt: horizontal
  y = movement.getY(); // Y-axis tilt: vertical
  z = movement.getZ();

  // Threshold to prevent small jitter
  const float threshold = 0.15;  

  // Calculate mouse movement with sensitivity factor
  int moveX = 0;
  int moveY = 0;
  const float sensitivity = 15.0; // adjust for speed

  if (x > threshold) {
    moveX = int(-x * sensitivity);
  } 
  else if (x < -threshold) {
    moveX = int(-x * sensitivity);
  }

  if (y > threshold) {
    moveY = int(-y * sensitivity); // negative because screen Y is inverted
  } 
  else if (y < -threshold) {
    moveY = int(-y * sensitivity);
  }

  // Move mouse if there is movement
  if (moveX != 0 || moveY != 0) {
    Mouse.move(moveX, moveY);
    Serial.print("Mouse moved X: ");
    Serial.print(moveX);
    Serial.print(", Y: ");
    Serial.println(moveY);
  }
}