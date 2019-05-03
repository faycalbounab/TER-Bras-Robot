

Servo servo0 = Servo(0,90,580,2.45,0);
Servo servo1 = Servo(1,90,450,100.0/45.0,155);
Servo servo2 = Servo(2,100,580,5.0/2.0,90);
Servo servo3 = Servo(3,90,390,200.0/75,90);
Servo servo4 = Servo(4,90,570,100/45,0);
Servo servo5 = Servo(5,200,450,100/45,0);

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60);
  yield();
}

void loop(){
  int x,y,z,typeMouvement;

  Serial.println("Début lecture ");
  for (int i = 0; i < 4; i++) {
    while(Serial.available() == 0){
      // do nothing
    }
    if(i == 0){
      x = Serial.parseInt(); // Reading Serial Data and saving in data variable
      Serial.print("x = ");
      Serial.println(x); // Printing the Serial data
    }
    if(i == 1){
      y = Serial.parseInt(); // Reading Serial Data and saving in data variable
      Serial.print("y = ");
      Serial.println(y); // Printing the Serial data
    }
    if(i == 2){
      z = Serial.parseInt(); // Reading Serial Data and saving in data variable
      Serial.print("z = ");
      Serial.println(z); // Printing the Serial data
    }
    if(i == 3){
      typeMouvement = Serial.parseInt(); // Reading Serial Data and saving in data variable
      Serial.print("typeMouvement = ");
      Serial.println(typeMouvement); // Printing the Serial data
    }
  }
  Serial.println("Fin leture");
  
  int* tab = new int[5];

  tab = calculeDesAngles(x,y,z);
  //tab = calculeDesAnglesApartirDuServo3(x,y,z);

  Serial.print("angle0 ");
  Serial.println(tab[0]);
  Serial.print("angle1 ");
  Serial.println(tab[1]);
  Serial.print("angle2 ");
  Serial.println(tab[2]);
  Serial.print("angle3 ");
  Serial.println(tab[3]);


  servo4.moveValeur(servo4.calculeMoveDegre(90));
  delay(1500);

  if(typeMouvement == 0){
    servo5.moveValeur(260);
    delay(1500);
  }
  
  
  servo0.moveValeur(servo0.calculeMoveDegre(tab[0]));
  delay(1500);
  servo1.moveValeur(servo1.calculeMoveDegre(tab[1]));
  delay(1500);
  servo2.moveValeur(servo2.calculeMoveDegre(tab[2]));
  delay(1500);
  servo3.moveValeur(servo3.calculeMoveDegre(tab[3]));
  delay(1500);

  if(typeMouvement == 0){
    servo5.moveValeur(210);
    delay(1500);
  }
  else{
    servo5.moveValeur(250);
    delay(1500);
  }
  

  servo1.moveValeur(servo1.calculeMoveDegre( 90 ));
  delay(1500);
  servo2.moveValeur(servo2.calculeMoveDegre( 180 ));
  delay(1500);
  servo3.moveValeur(servo3.calculeMoveDegre( 160 ));
  delay(1500);
  

  Serial.println("");

}
