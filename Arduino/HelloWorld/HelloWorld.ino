#include <Adafruit_Microbit.h>

Adafruit_Microbit_Matrix microbit;

const int buttonB = 11;     // the number of the pushbutton pin
const int buttonA = 5;     // the number of the pushbutton pin

int letter_count = 0;

const uint8_t
H_bmp[] =
{ B10001,
  B10001,
  B11111,
  B10001,
  B10001,
};

const uint8_t
e_bmp[] =
{ B01110,
  B10001,
  B11111,
  B10000,
  B01111,
};

const uint8_t
l_bmp[] =
{ B01100,
  B00100,
  B00100,
  B00100,
  B01110,
};

const uint8_t
o_bmp[] =
{ B01110,
  B10001,
  B10001,
  B10001,
  B01110,
};

const uint8_t
W_bmp[] =
{ B10001,
  B10001,
  B10101,
  B10101,
  B01010,
};

const uint8_t
r_bmp[] =
{ B10011,
  B10100,
  B11000,
  B10000,
  B10000,
};

const uint8_t
d_bmp[] =
{ B00001,
  B00001,
  B01111,
  B10001,
  B01111,
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World?");
  microbit.begin();
  pinMode(buttonB, INPUT);
  pinMode(buttonA, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  microbit.show(H_bmp);
  delay(500);
  microbit.clear();
  delay(50);
  microbit.show(e_bmp);
  delay(500);
  microbit.clear();
  delay(50);
  microbit.show(l_bmp);
  delay(500);
  microbit.clear();
  delay(50);
  microbit.show(l_bmp);
  delay(500);
  microbit.clear();
  delay(50);
  microbit.show(o_bmp);
  delay(500);
  microbit.clear();
  delay(500);
  microbit.show(W_bmp);
  delay(500);
  microbit.clear();
  delay(50);
  microbit.show(o_bmp);
  delay(500);
  microbit.clear();
  delay(50);
  microbit.show(r_bmp);
  delay(500);
  microbit.clear();
  delay(50);
  microbit.show(l_bmp);
  delay(500);
  microbit.clear();
  delay(50);
  microbit.show(d_bmp);
  delay(500);
  microbit.clear();
  delay(50);
  microbit.clear();
  delay(500);
}
