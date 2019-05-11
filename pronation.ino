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
    int valeurPos;
    int initAngle;
    int vitesse;

    public:
      Servo(int numServo, int mini,int maxi,int valeurPos, float coeffDir, int initAngle, int vitesse){
        this->numServo = numServo;
        this->mini = mini;
        this->maxi = maxi;
        this->valeurPos = valeurPos;
        this->coeffDir = coeffDir;
        this->initAngle = initAngle;
        this->vitesse = vitesse;
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
            delay(vitesse);
            }
          }
          else{
            for (uint16_t pulselen = valeurPos; pulselen > valeur; pulselen--) {
              pwm.setPWM(numServo, 0, pulselen);
              delay(vitesse);
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




int* calculeDesAngles(int x, int y, int z) {

    //distance entre les Servos
    float distance1 = 10.4;
    float distance2 = 9.8;
    float distance3 = 14;

    //position du Servo1
    int S1y = 0;
    int S1z = 12;

    float S1toS4g = y - S1y;
    float S1toS4d = z - S1z;
    float S1toS4 = sqrt(S1toS4g*S1toS4g + S1toS4d * S1toS4d);


    //Calcule des angles

    float radianS0 = acos(x / sqrt(x * x + y * y));
    int angleS0 = radianToDegre(radianS0);

    float radianS3 = 0;
    for (float i = 11*PI/20 ; i < PI; i += PI / 40)
    {
      float tmpS1toS3 = sqrt(distance1*distance1 + distance2 * distance2 - 2 * distance1*distance2*cos(i));

        float tmpc1 = acos((distance2*distance2 + tmpS1toS3 * tmpS1toS3 - (distance1*distance1)) / (2 * tmpS1toS3*distance2));
      float tmpc2 = acos((distance3*distance3 + tmpS1toS3 * tmpS1toS3 - (S1toS4*S1toS4)) / (2 * tmpS1toS3*distance3));

      float tmpc = tmpc1 + tmpc2;
      if (radianS3 < tmpc) { radianS3 = tmpc;

      }

    }

    if (radianS3 < PI / 2) { radianS3 = 0;  }//si le mouvement n'est pas possible


    float S2toS4 = sqrt(distance3*distance3 + distance2 * distance2 - 2 * distance2*distance3*cos(radianS3));

    float angleB2 = acos((distance2*distance2 + S2toS4 * S2toS4 - (distance3*distance3)) / (2 * S2toS4*distance2));

    float angleB1 = acos((distance1*distance1 + S2toS4 * S2toS4 - (S1toS4*S1toS4)) / (2 * S2toS4*distance1));

    float angleB = angleB1 + angleB2;

    float S1toS3 = sqrt(distance1*distance1 + distance2 * distance2 - 2 * distance1*distance2*cos(angleB));

    float angleA1 = acos((distance1*distance1 + S1toS3 * S1toS3 - (distance2*distance2)) / (2 * S1toS3*distance1));

    float angleA2 = acos((y - S1y) / S1toS4);


    float angleA3 = acos((S1toS4*S1toS4 + S1toS3 * S1toS3 - (distance3*distance3)) / (2 * S1toS3*S1toS4));
    float angleA = 0;
    if (z < S1z)
    {
       angleA = angleA1 + angleA3 - angleA2;
    }
    else
    {
       angleA = angleA1 + angleA3 + angleA2;
    }

    Serial.println(angleA);
    Serial.println(angleB);
    Serial.println(radianS3);

    int angleS1 = radianToDegre(angleA);
    int angleS2 = radianToDegre(angleB);
    int angleS3 = radianToDegre(radianS3);

    int* tab = new int[4];
    tab[0] = angleS0;
    tab[1] = angleS1;
    tab[2] = angleS2;
    tab[3] = angleS3;

    return tab;

  }






int* calculeAngleVariateur(int x, int y, int z){

  //distance entre les Servos
  float r1 = 10.4;
  float r2 = 9.8;
  float r3 = 14;

  //position du Servo1
  float S1y = 0;
  float S1z = 9;

  float Zy = S1y;
  float Zz = z;

  float radianS0 = acos(x/sqrt(x * x + y * y));
  int angleS0 =  radianToDegre(radianS0);
  int angleS1, angleS2, angleS3;
  float alpha,beta,gamma;

  for (float k = 0.1 ; k < 1 ; k += 0.1) {

  //Calcule des angles
  
    float Dy = abs(y - S1y);
    float Dz = abs(z - S1z);
    float r = sqrt(Dy * Dy + Dz * Dz);
    float alpha1;
    if(z <= S1z){ alpha1 = asin(Dy / r);}
    if(z > S1z){ alpha1 = (PI / 2) + asin(Dz / r);}
    float Dalpha = acos( (r1 * r1 + r * r - (r2 + r3) * (r2 + r3)) / (2 * r1 * r));
    float alpha2 = k * Dalpha;
    
    alpha = alpha1 + alpha2 - PI / 2;
    
    float r4 = sqrt(r1 * r1 + r * r - 2 * r * r1 * cos(alpha2));
    float beta1 = acos((r1 * r1 + r4 * r4 - r * r) / (2 * r1 * r4));
    float beta2 = acos((r2 * r2 + r4 * r4 - r3 * r3) / (2 * r2 * r4));

    beta = beta1 + beta2;
    gamma = acos((r2 * r2 + r3 * r3 - r4 * r4) / (2 * r2 * r3));
    
    angleS1 =  radianToDegre(alpha);
    angleS2 =  radianToDegre(beta);
    angleS3 =  radianToDegre(gamma);
    if(angleS1 > 0 && angleS1 < 150 && angleS2 > 89 && angleS2 < 180 && angleS3 > 89 && angleS3 < 180  ){break;}

  }
   
  int* tab =new int[5];
  tab[0] = angleS0;
  tab[1] = angleS1;
  tab[2] = angleS2;
  tab[3] = angleS3;

  return tab; 
}
