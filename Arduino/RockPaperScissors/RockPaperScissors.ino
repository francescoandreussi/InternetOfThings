#include <Adafruit_Microbit.h>
#include <SPI.h>
#include <EddystoneBeacon.h>
#include <Wire.h>
#include <MMA8653.h>

Adafruit_Microbit_Matrix microbit;
EddystoneBeacon eddystoneBeacon = EddystoneBeacon();
// Accelerometer
// MMA8653 accel;

const int buttonB = 11;     // the number of the right pushbutton pin
const int buttonA = 5;     // the number of the left pushbutton pin

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

// Eddystone characteristics
const char power = -18; // taken from Eddystone example
// "URLs"
const char* rps[3] = {"http://rock.com", "http://scissors.com", "http://paper.com"};

void setup() {
  // accel.begin(false, 2); // 8-bit mode, 2g range
  
  Serial.begin(9600);
  
  eddystoneBeacon.begin(power, rps[0]); // power, URI
  
  microbit.begin();
  pinMode(buttonB, INPUT);
  pinMode(buttonA, INPUT);
}

void loop() {
  // broadcast every loop
  eddystoneBeacon.loop();

  // accel.update();
  
  // show currently selected symbol
  microbit.show(stateSymbol[currentState]);
  if (! digitalRead(buttonA)) { // on pressure
    delay(200);
    currentState--; // previous symbol
    if (currentState < 0) { // wrap around
      currentState = 2;
    }
    microbit.clear();
    // broadcast new symbol
    // eddystoneBeacon.begin(power, rps[currentState]);
  }
  
  if (! digitalRead(buttonB)) { // on pressure
    delay(200);
    currentState++; // next symbol
    if (currentState > 2) { // wrap around
      currentState = 0;
    }
    microbit.clear();
    // broadcast new symbol
    // eddystoneBeacon.begin(power, rps[currentState]);
  }
  /*
  if ((accel.getX() > 10) || (accel.getY() > 10) || (accel.getZ() > 10)) {
    Serial.println("Shake detected");
  }
  */
}
