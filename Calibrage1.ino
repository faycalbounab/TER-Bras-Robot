#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//moteur 1 de 0 à 450
//moteur 5 de 220 à 400

#define SERVOMIN  210 
#define SERVOMAX  400 

// Servozähler
uint8_t servonum = 5;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);

  yield();
}

void loop() {
//baisser le bras
  Serial.println(servonum);
  for (uint16_t pulselen = 0; pulselen < 300; pulselen++) {
    pwm.setPWM(0, 0, pulselen); //servo 0
    delay(10);
  }


  delay(1500);

  for (uint16_t pulselen = 150; pulselen < 250; pulselen++) {
    pwm.setPWM(1, 0, pulselen); //servo 1
    delay(10);
  }


  delay(1500);

  for (uint16_t pulselen = 440; pulselen > 0; pulselen--) {
    pwm.setPWM(2, 0, pulselen);//servo 2
    delay(10);
  }

  delay(1500);

  for (uint16_t pulselen = 250; pulselen > 0; pulselen--) {
    pwm.setPWM(3, 0, pulselen);//servo 3
    delay(10);
  }

  delay(1500);

  for (uint16_t pulselen = 190; pulselen < 300; pulselen++) {
    pwm.setPWM(5, 0, pulselen); //servo 5
    delay(10);
  }

  delay(1500);

//remonter le bras
  for (uint16_t pulselen = 300; pulselen > 190; pulselen--) {
    pwm.setPWM(5, 0, pulselen);//servo 5
    delay(10);
  }


  delay(1500);

  for (uint16_t pulselen = 0; pulselen < 250; pulselen++) {
    pwm.setPWM(3, 0, pulselen); //servo 3
    delay(10);
  }

  delay(1500);

  for (uint16_t pulselen = 0; pulselen < 440; pulselen++) {
    pwm.setPWM(2, 0, pulselen); //servo 2
    delay(10);
  }

  delay(1500);

  for (uint16_t pulselen = 250; pulselen > 150; pulselen--) {
    pwm.setPWM(1, 0, pulselen);//servo 1
    delay(10);
  }

  delay(1500);

  for (uint16_t pulselen = 300; pulselen > 0; pulselen--) {
    pwm.setPWM(0, 0, pulselen);//servo 0
    delay(10);
  }

  delay(1500);  

}
