#include <Servo.h>

// Flex sensor pins
int flex1 = A0;
int flex2 = A1;
int flex3 = A2;
int flex4 = A3;
int flex5 = A4;

// Output pins
int bulbPin = 8;
int motorPin = 9;
int servo1Pin = 10;
int servo2Pin = 11;

// RGB pins (common cathode)
int rPin = 3;
int gPin = 5;
int bPin = 6;

Servo servo1, servo2;

int thresholdVal = 150;  // threshold where bent gives LOWER value

void setup() {
  Serial.begin(9600);

  pinMode(bulbPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  digitalWrite(bulbPin, LOW);
  digitalWrite(motorPin, LOW);
  servo1.write(0);
  servo2.write(0);
  setRGB(0, 0, 0);
}

void setRGB(int r, int g, int b) {
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
}

void loop() {
  int v1 = analogRead(flex1);
  int v2 = analogRead(flex2);
  int v3 = analogRead(flex3);
  int v4 = analogRead(flex4);
  int v5 = analogRead(flex5);

  // Print
  Serial.print("F1:"); Serial.print(v1);
  Serial.print("  F2:"); Serial.print(v2);
  Serial.print("  F3:"); Serial.print(v3);
  Serial.print("  F4:"); Serial.print(v4);
  Serial.print("  F5:"); Serial.println(v5);

  // FLEX 1 → Bulb  (bent = LOW value)
  digitalWrite(bulbPin, (v1 < thresholdVal) ? HIGH : LOW);

  // FLEX 2 → Motor  (bent = LOW)
  digitalWrite(motorPin, (v2 < thresholdVal) ? HIGH : LOW);

  // FLEX 3 → Servo 1 (bent = LOW)
  servo1.write((v3 < thresholdVal) ? 90 : 0);

  // FLEX 4 → Servo 2 (bent = LOW)
  servo2.write((v4 < thresholdVal) ? 90 : 0);

  // FLEX 5 → RGB  (bent = LOW)
  // Range is still based on full value
  if (v5 <= 51) {
    setRGB(255, 0, 0);       // RED
  }
  else if (v5 <= 102) {
    setRGB(0, 255, 0);       // GREEN
  }
  else if (v5 <= 153) {
    setRGB(0, 0, 255);       // BLUE
  }
  else if (v5 <= 204) {
    setRGB(255, 255, 0);     // YELLOW
  }
  else {
    setRGB(128, 0, 128);     // PURPLE
  }

  delay(150);
}