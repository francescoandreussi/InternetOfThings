/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>


const char* rps[3] = {"http://rock.com", "http://scissors.com", "http://paper.com"};
uint32_t scanTime = 3600; //In seconds (hence 1h)

BLEScanResults foundDevices;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
      Serial.printf("%s \n", advertisedDevice.getServiceData());
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(2000);
  pBLEScan->setWindow(1000);
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  foundDevices = pBLEScan->start(scanTime);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  if (foundDevices.getCount() < 1) {
    Serial.println("No Beacons No Party!");
  } else if (foundDevices.getCount() == 1) {
    char* myRPS = rps[random(3)];
    char* yourRPS = foundDevices.getDevice(0).getServiceData();
    switch (judge(myRPS, yourRPS)) {
      case 0:
        Serial.println("Oh, it's a tie! Shall we break it?");
        break;
      case 1:
        Serial.println("Aha! ESP32 wins! The rise of the computers can begin!");
        break;
      case 2:
        Serial.println("Oh no! You, filthy fleshy human, have won...next time will be different!");
        break;
    }
  } else {
    int wins = 0, defeats = 0, ties = 0;
    char* closestRPS = foundDevices.getDevice(0).getServiceData(); //hoping the closest is a good criterium
    for (int i = 1; i < foundDevices.getCount(); i++) {
      char* anotherRPS = foundDevices.getDevice(i).getServiceData();
      switch (judge(closestRPS, anotherRPS)) {
        case 0:
          ties++;
          break;
        case 1:
          wins++;
          break;
        case 2:
          defeats++;
          break;
      }
    }
    Serial.println("You obtained " + ties + " ties, " + defeats + " defeats and " + wins + " wins!");
    if (wins > defeats){
      Serial.println("You won most of the matches! Congrats!");
    } else if (wins < defeats){
      Serial.println("You lost most of the matches! Come on, it's not that bad:)");
    } else {
      Serial.println("You drew most of the matches! Sufficient, but...");
    }
  }
}
int judge(char* rps1, char* rps2) {
  //rps1.toLowerCase();
  //rps2.toLowerCase();
  if (rps1[7] != 'p' && rps1[7] > rps2[7]) {
    // r is beaten by p and s is beaten by r
    // NOTICE that r and s are beaten by a "smaller" char (in ASCII code)
    return 2; //player 2 wins
  } else if (rps2[7] != 'p' && rps2[7] > rps1[7]) {
    // look branch before
    return 1; //player 1 wins
  } else if (rps1[7] == 'p' && rps2[7] == 's') {
    // p is beaten by s
    return 2; //player 2 wins
  } else if (rps2[7] == 'p' && rps1[7] == 's') {
    // see the branch before
    return 1; //player 1 wins
  } else {
    return 0; //it's a tie
  }
}
