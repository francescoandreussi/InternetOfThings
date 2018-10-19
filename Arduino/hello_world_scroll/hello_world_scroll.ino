#include <Adafruit_Microbit.h>

Adafruit_Microbit_Matrix microbit;

const int buttonB = 11;     // the number of the pushbutton pin
    
void setup() {
  // Serial.begin(9600);
  // Serial.println("Welcome to IOT!");
  microbit.begin();
  pinMode(buttonB, INPUT);
}

void loop() {
  microbit.scrollText("Hello World");
}
