 
#include <EEPROM.h>
#include <Wire.h>

long duration, inches;
int set_val, percentage;
bool state, pump;

void setup() {


  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  // pinMode(10, INPUT_PULLUP);
  // pinMode(11, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  set_val = EEPROM.read(0);
  if (set_val > 150) set_val = 150;
}
void loop() {

  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  duration = pulseIn(3, HIGH);
  inches = microsecondsToInches(duration);

  percentage = (set_val - inches) * 100 / set_val;
  Serial.print(percentage); 
  // Serial.print("\n");


  if (percentage < -200 & digitalRead(11)) pump = 1;
  if (percentage < -200) pump = 1;
  if (percentage > 60) pump = 0;
  // digitalWrite(13, !pump);
  // Serial.print(pump);
  // Serial.print("\n");

  if (pump == 1) {  
    Serial.print("Motor is on");
    Serial.print("\n");
    digitalWrite(13, LOW);


  } else {
    Serial.print("Motor is off");
    Serial.print("\n");
        digitalWrite(13, HIGH);

  }

  if (!digitalRead(10) & !state & digitalRead(11)) {
    state = 1;
    set_val = inches;
    EEPROM.write(0, set_val);
  }

  if (!digitalRead(10) & !state & !digitalRead(11)) {
    state = 1;
    pump = !pump;
  }

  if (digitalRead(10)) state = 0;


  delay(500);
}
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}
