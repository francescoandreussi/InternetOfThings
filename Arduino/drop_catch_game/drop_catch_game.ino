#include <Adafruit_Microbit.h>

Adafruit_Microbit_Matrix microbit;

const int buttonB = 11;     // the number of the pushbutton pin
const int buttonA = 5;     // the number of the pushbutton pin

int dropPos[2] = {};
int dir;
int catchPos = 2;
int scoreCount = 0;
int gameSpeed = 1200;
long nextTimeFrame = 0;

const uint8_t
sad_bmp[] =
{ B00000,
  B01010,
  B00000,
  B01110,
  B10001,
};

void setup() {
  // put your setup code here, to run once:
  microbit.begin();
  pinMode(buttonB, INPUT);
  pinMode(buttonA, INPUT);

  initGame();
}

void loop() {
  // put your main code here, to run repeatedly:  
  if (! digitalRead(buttonA)) { // on pressure
    //while (! digitalRead(buttonA)) {} //wait for release
    delay(200);
    catchPos--;
    microbit.clear();
    microbit.drawPixel(catchPos, 4, LED_ON);
    microbit.drawPixel(dropPos[0], dropPos[1], LED_ON);
  }
  if (! digitalRead(buttonB)) { // on pressure
    //while (! digitalRead(buttonB)) {} //wait for release
    delay(200);
    catchPos++;
    microbit.clear();
    microbit.drawPixel(catchPos, 4, LED_ON);
    microbit.drawPixel(dropPos[0], dropPos[1], LED_ON);
  }

  //microbit.drawPixel(catchPos, 4, LED_ON);
  //microbit.drawPixel(dropPos[0], dropPos[1], LED_ON);
  //delay(gameSpeed);
  //microbit.clear();

  //check for borders
  if (catchPos < 0) {
    catchPos = 4;
  } else if (catchPos > 4) {
    catchPos = 0;
  }

  if ((dropPos[0] == 0 && dir == -1) || (dropPos[0] == 4 && dir == 1)) {
    dir *= -1;
  }

  if(millis() > nextTimeFrame){//change positions
    nextTimeFrame += gameSpeed;
    dropPos[1]++;
    dropPos[0] += dir;
    microbit.clear();
    microbit.drawPixel(catchPos, 4, LED_ON);
    microbit.drawPixel(dropPos[0], dropPos[1], LED_ON);
  }

  //check for catch
  if (dropPos[1] == 4 && dropPos[0] == catchPos) { //CATCH! CLAP CLAP!
    scoreCount++;
    gameSpeed -= 50;
    microbit.print(scoreCount);
    delay(200);
    microbit.clear();
    delay(200);
    microbit.print(scoreCount);
    delay(200);
    microbit.clear();
    delay(200);
    microbit.print(scoreCount);
    delay(500);
    microbit.clear();
    initGame();
  } else if (dropPos[1] == 4 && dropPos[0] != catchPos) { //next time!
    microbit.drawPixel(catchPos, 4, LED_ON);
    microbit.drawPixel(dropPos[0], dropPos[1], LED_ON);
    delay(1000);
    microbit.clear();
    microbit.show(sad_bmp);
    delay(1000);
    microbit.clear();
    initGame();
  }

}

void initGame() {
  microbit.drawPixel(catchPos, 4, LED_ON);
  dropPos[0] = (int) random(0, 5);
  dropPos[1] = 0;
  microbit.drawPixel(dropPos[0], dropPos[1], LED_ON);
  dir = (int) random(-1, 2);
  delay(gameSpeed);
  microbit.clear();
  nextTimeFrame += gameSpeed;
}
