


Servo servo0 = Servo(0,90,580,0.0,0.0,8.0,2.45);
void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);

  yield();
}

void loop() {
//baisser le bras
//  Serial.println(servonum);
//  for (uint16_t pulselen = 0; pulselen < 300; pulselen++) {
//    pwm.setPWM(0, 0, pulselen); //servo 0
//    delay(10);
//  }
  servo0.moveValeur(300);
delay(1500);
  servo0.moveValeur(90);
delay(1500);

//  delay(1500);
//
//  for (uint16_t pulselen = 150; pulselen < 250; pulselen++) {
//    pwm.setPWM(1, 0, pulselen); //servo 1
//    delay(10);
//  }
//
//
//  delay(1500);
//
//  for (uint16_t pulselen = 440; pulselen > 0; pulselen--) {
//    pwm.setPWM(2, 0, pulselen);//servo 2
//    delay(10);
//  }
//
//  delay(1500);
//
//  for (uint16_t pulselen = 250; pulselen > 0; pulselen--) {
//    pwm.setPWM(3, 0, pulselen);//servo 3
//    delay(10);
//  }
//
//  delay(1500);
//
//  for (uint16_t pulselen = 190; pulselen < 300; pulselen++) {
//    pwm.setPWM(5, 0, pulselen); //servo 5
//    delay(10);
//  }
//
//  delay(1500);
//
////remonter le bras
//  for (uint16_t pulselen = 300; pulselen > 190; pulselen--) {
//    pwm.setPWM(5, 0, pulselen);//servo 5
//    delay(10);
//  }
//
//
//  delay(1500);
//
//  for (uint16_t pulselen = 0; pulselen < 250; pulselen++) {
//    pwm.setPWM(3, 0, pulselen); //servo 3
//    delay(10);
//  }
//
//  delay(1500);
//
//  for (uint16_t pulselen = 0; pulselen < 440; pulselen++) {
//    pwm.setPWM(2, 0, pulselen); //servo 2
//    delay(10);
//  }
//
//  delay(1500);
//
//  for (uint16_t pulselen = 250; pulselen > 150; pulselen--) {
//    pwm.setPWM(1, 0, pulselen);//servo 1
//    delay(10);
//  }
//
//  delay(1500);
//
//  for (uint16_t pulselen = 300; pulselen > 0; pulselen--) {
//    pwm.setPWM(0, 0, pulselen);//servo 0
//    delay(10);
//  }
//
//  delay(1500);  

}
