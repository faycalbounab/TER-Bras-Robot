#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Die eingestellen Minimal- und Maximalwerte können, je nach Motor variieren
#define SERVOMIN  0 // Minimale-Pulslänge
#define SERVOMAX  100 // Maximale-Pulslänge

// Servozähler
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analoge Servomotoren haben eine Aktualisierungsrate von 60Hz

  yield();
}

void loop() {
  // jeden Motor einzelnd ansteuern
  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(1000);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
    
  }

  delay(2000);

  //servonum ++;
  //if (servonum > 15) servonum = 0;
}
