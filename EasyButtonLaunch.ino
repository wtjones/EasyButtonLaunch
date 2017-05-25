/*
EasyButtonLaunch

A mod to make an "Easy Button" into a HID input.

The board is a Leonardo.
* 2k resistor in 5v
* attach the resistor to both: 
  * digital pin 2 
  * one side of the push button
* the other side of the push button to GND
* an LED in pin 13/GND

The push action will enable the LED

Created by W Travis Jones - All rights reversed http://www.unlicense.org/ (public domain)
*/
 
#include <HID-Project.h>
#include <HID-Settings.h>

//#define DEBUG 1

const int buttonPin = 2;      // the number of the pushbutton pin
const int ledPin = 13;        // the number of the LED pin

int ledState = HIGH;          // the current state of the output pin
int buttonState;              // the current reading from the input pin
int lastButtonState = LOW;    // the previous reading from the input pin
long lastDebounceTime = 0;    // the last time the output pin was toggled
long debounceDelay = 50;      // the debounce time; increase if the output flickers


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

   // set initial LED state
  digitalWrite(ledPin, ledState);

  
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  Gamepad.begin();
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState != HIGH) {
        ledState = HIGH;
        Gamepad.press(1);
      } else {
        ledState = !HIGH;
        Gamepad.releaseAll();
      }
      Gamepad.write();
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  lastButtonState = reading;
  
 
}
