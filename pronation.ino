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
        if(numServo == 1) return coeffDir * (initAngle - angle) + mini;
        else return coeffDir * (angle - initAngle) + mini ;
        
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


int cmTValeurServo5(float cm){
  if(cm >= 0 || cm <= 15.5) return 100*cm/9 + 200;
  return 200;
}

int radianToDegre(float radian){
  return radian /PI*180 ;
}





int* calculeDesAngles(int x, int y, int z){

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
  float radianS1 = PI / 2.5;
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


  int* tab =new int[5];
  tab[0] = angleS0;
  tab[1] = angleS1;
  tab[2] = angleS2;
  tab[3] = angleS3;

  return tab; 
}




int* calculeDesAnglesApartirDuServo3(int x, int y, int z){

  //distance entre les Servos
  float distance1 = 10.4;
  float distance2 = 9.8;
  float distance3 = 14;

  //position du Servo1
  int S1y=0;
  int S1z=12;

  //position du Servo3

  int S3y=0;
  int S3z=21;
  int S3x = -3;

  //position du Servo4
  int S4y = 0;
  
  //Calcule des angles
  
  float radianS0 = acos(x/sqrt(x * x + y * y));
  int angleS0 =  radianToDegre(radianS0);

  //pour l'instant cet angle est prÈdÈfini
  float radianS3 = PI / 2;
  int angleS3 = radianToDegre(radianS3);
  
  float S2toS4 = sqrt(distance3*distance3+distance2*distance2-2*distance2*distance3*cos(angleS3));

  float angleB2 = acos((distance2*distance2+S2toS4*S2toS4-(distance3*distance3))/(2*S2toS4*distance2));
  
  
  float S1toS4g = y-S1y;
  float S1toS4d = z-S1z;
  float S1toS4 = sqrt(S1toS4g*S1toS4g+S1toS4d*S1toS4d);


  float angleB1=acos((distance1*distance1+S2toS4*S2toS4-(S1toS4*S1toS4))/(2*S2toS4*distance1));
  
  float angleB =angleB1+angleB2;
// A modif 
  float S1toS3g = S3y-S1y;
  float S1toS3d = S3z-S1z;
  float S1toS3 = sqrt(S1toS3g*S1toS3g+S1toS3d*S1toS3d);

  float angleA1 = acos((distance1*distance1+S1toS3*S1toS3-(distance2*distance2))/(2*S1toS3*distance1));

  float angleA2 = acos((S4y-S1y)/S1toS4);
  
  float angleA = PI - (angleA1+angleA2); 

  int angleS1 = radianToDegre(angleA);
  int angleS2 = radianToDegre(angleB);


  int* tab =new int[5];
  tab[0] = angleS0;
  tab[1] = angleS1;
  tab[2] = angleS2;
  tab[3] = angleS3;

  return tab; 

}
