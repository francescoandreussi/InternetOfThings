int VRx = 4;
int VRy = 2;
int SW  = 15;

int switchValue;

int lastSwitchState = LOW;

int delayMs = 500;
int elapsedTime = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW,  INPUT);

  //digitalWrite(VRx, HIGH);
  //digitalWrite(VRy, HIGH);
  digitalWrite(SW,  HIGH);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  switchValue = analogRead(SW);
  
  if (switchValue == 0) {
    Serial.println("Switch pressed, value " + (String) switchValue);
    Serial.println("Digital switch value " + (String) digitalRead(SW));
  }
  */
  if (millis() > elapsedTime) {
    elapsedTime += delayMs;
    Serial.println("X: " + (String) analogRead(VRx));
    Serial.println("Y: " + (String) analogRead(VRy));
  }
}
