#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


uint8_t servonum = 5;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
class Servo {

  private : 
    int numServo;
    int mini;
    int maxi;
    float coeffDir;
    int valeurPos = 0;
    int initAngle;

    public:
      Servo(int numServo, int mini,int maxi,float coeffDir, int initAngle){
        this->numServo = numServo;
        this->mini = mini;
        this->maxi = maxi;
        this->coeffDir = coeffDir;
        this->initAngle = initAngle;
      }
      

      //prend un angle en parametre et calcule la valeur du déplacement du servo
      int calculeMoveDegre(int angle){
        if(numServo == 1){
          return coeffDir * (initAngle - angle) + mini;
        }
        else{
          return coeffDir * (angle - initAngle) + mini ;
        } 
      }

      void moveValeur(int valeur){
          if(valeur > valeurPos){
            for (uint16_t pulselen = valeurPos; pulselen < valeur; pulselen++) {
            pwm.setPWM(numServo, 0, pulselen);
            delay(10);
            }
          }
          else{
            for (uint16_t pulselen = valeurPos; pulselen > valeur; pulselen--) {
              pwm.setPWM(numServo, 0, pulselen);
              delay(10);
            }
          }
          this->valeurPos = valeur;
      }

      //vérifie si la valeur de déplacement est correct
      bool isMoveValid(int x){
        if(x >= mini && x <= maxi){
          return true;
        }
        return false;
      }
};

int radianToDegre(float radian){
  return radian /(PI*180) ;
}

void calculeDesAngles(int x, int y, int z){

  //distance entre les Servos
  float distance1 = 10.4;
  float distance2 = 9.8;
  float distance3 = 14;

  //position du Servo1
  int S1y=0;
  int S1z=12;

  //Calcule des angles
  
  float radianS0 = acos(x/sqrt(x * x + y * y));
  int angleS0 =  radianToDegre(radianS0);

  //pour l'instant cet angle est prédéfini
  float radianS1 = PI / 4;
  int angleS1 = radianToDegre(radianS1);
  
  float S2y = cos(radianS1) * distance2 + S1y;
  float S2z = sin(radianS1) * distance2 + S1z;
  
  float S2toS4g = y-S2y;
  float S2toS4d = z-S2z;
  float S2toS4 = sqrt(S2toS4g*S2toS4g+S2toS4d*S2toS4d);
  float S1toS4g = y-S1y;
  float S1toS4d = z-S1z;
  float S1toS4 = sqrt(S1toS4g*S1toS4g+S1toS4d*S1toS4d);
  
  float radianS3 = acos(((distance1*distance1+distance3*distance3-S2toS4*S2toS4)/(2*distance1*distance3)));
  float radianTriangle1 = acos(((S2toS4*S2toS4+distance2*distance2-S1toS4*S1toS4)/(2*S2toS4*distance2)));
  float radianTriangle2 = acos(((S2toS4*S2toS4+distance1*distance1-distance3*distance3)/(2*S2toS4*distance1)));
  float radianS2 = radianTriangle1 + radianTriangle2;

  int angleS3 = radianToDegre(radianS3);
  int angleS2 = radianToDegre(radianS2);
  
}
