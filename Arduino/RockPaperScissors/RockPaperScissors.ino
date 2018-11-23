#include <Adafruit_Microbit.h>
#include <Adafruit_BLEEddystone.h>

Adafruit_Microbit_Matrix microbit;

const int buttonB = 11;     // the number of the pushbutton pin
const int buttonA = 5;     // the number of the pushbutton pin

int currentState = 0;
const uint8_t stateSymbol[3][5] = {
  { B00100,
    B01110,
    B11111,
    B01110,
    B00100,
  },

  { B11001,
    B11010,
    B00100,
    B11010,
    B11001,
  },

  { B01110,
    B01110,
    B01110,
    B01110,
    B01110,
  }
};

void setup() {
  // put your setup code here, to run once:
  microbit.begin();
  pinMode(buttonB, INPUT);
  pinMode(buttonA, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  microbit.show(stateSymbol[currentState]);
  if (! digitalRead(buttonA)) { // on pressure
    delay(200);
    currentState--;
    if (currentState < 0) {
      currentState = 2;
    }
    microbit.clear();
  }
  if (! digitalRead(buttonB)) { // on pressure
    delay(200);
    currentState++;
    if (currentState > 2) {
      currentState = 0;
    }
    microbit.clear();
  }

  if (true) { //after shaking

  }

}
