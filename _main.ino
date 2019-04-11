
Servo servo0 = Servo(0,90,580,0.0,0.0,8.0,2.45,0);
Servo servo1 = Servo(1,90,450,0.0,0.0,9.5,100.0/45.0,155);
Servo servo2 = Servo(2,100,580,-10.0,0.0,14,5.0/2.0,90);
Servo servo3 = Servo(3,90,390,-3.0,0.0,21,200.0/75,90);
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
  for (uint16_t pulselen = 90; pulselen < 570; pulselen++) {
    pwm.setPWM(4, 0, pulselen); //servo 0
    delay(10);
  }
  servo0.moveValeur(300);
delay(1500);
  servo0.moveValeur(servo0.calculeMoveDegre(90));
delay(1500);
  servo1.moveValeur(servo1.calculeMoveDegre(38));
  delay(1500);
  servo2.moveValeur(servo2.calculeMoveDegre(136));
delay(1500);

servo3.moveValeur(servo3.calculeMoveDegre(95));
delay(1500);


}
