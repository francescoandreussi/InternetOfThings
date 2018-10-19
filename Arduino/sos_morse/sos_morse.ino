#include <Adafruit_Microbit.h>

Adafruit_Microbit_Matrix microbit;

const int buttonB = 11;     // the number of the pushbutton pin
const int buttonA = 5;     // the number of the pushbutton pin

int blink_count = 0;
int letter_count = 0;

const uint8_t
default_bmp[] =
{ B11111,
  B10001,
  B10101,
  B10001,
  B11111,
};

const uint8_t
hi_bmp[] =
{ B10001,
  B10000,
  B11101,
  B10101,
  B10101,
};

const uint8_t
full_bmp[] =
{ B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to IOT!");
  microbit.begin();
  pinMode(buttonB, INPUT);
  pinMode(buttonA, INPUT);
}

void loop() {
  // draw a custom made bitmap face
  if (blink_count < 3 && (letter_count == 0 || letter_count == 2)) {
    //short blink
    delay(250);
    microbit.show(full_bmp);
    delay(100);
    microbit.clear();
    delay(50);
    blink_count++;
  }else if(blink_count < 3 && letter_count == 1){
    //long blink
    delay(250);
    microbit.show(full_bmp);
    delay(500);
    microbit.clear();
    delay(50);
    blink_count++;
  }else if(blink_count >=3 && letter_count < 3){
    //next letter
    letter_count++;
    blink_count = 0;
  }else{
    //restart
    delay(500);
    letter_count = 0;
    blink_count = 0;
  }
}
