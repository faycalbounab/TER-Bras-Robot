 #include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

uint8_t servonum = 5;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
class Servo {

  private : 
    int numServo; //port sur lequel est branché le Servo
    int mini; //valeur minumum du Servo
    int maxi; //valeur maximum du Servo
    float coeffDir; //coefficient directeur de la fonction calculeMoveDegre
    int valeurPos; //valeur en position initiale
    int initAngle; //angle minimum du Servo
    int vitesse; //vitesse de rotation du Servo

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

      // déplace le Servo en position valeur passée en paramètre
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


// indique la position que doit prendre le Servo5 (la pince) pour s'ouvrir selon la taille cm passée en paramètre
int cmTValeurServo5(float cm){
  if(cm >= 0 || cm <= 15.5) return 100*cm/9 + 200;
  return 200;
}

//converti des radian en degré
int radianToDegre(float radian){
  return radian /PI*180 ;
}


float degreToRadian(float degre){
    return degre * PI / 180;
}





int* calculeAngleVariateur42(int x, float y, int z){
    int AS0 = 0;
    int AS1 = 0;
    int AS2 = 0;
    int AS3 = 0;

    float distance;

    //distance entre les Servos
    float r0 = 2;
    float r1 = 10.4;
    float r2 = 9.8;
    float r3 = 14;


    float S0toP = sqrt(x * x + y * y);
    float S1toP = sqrt(S0toP * S0toP - r0 * r0);
    float radianS0substr = acos(S1toP / S0toP);
    float radianS0add = acos(x / S0toP);
    float radianS0 =radianS0add - radianS0substr;
    int angleS0 = radianToDegre(radianS0);


    //position du Servo1
    float S1x = cos((PI / 2)+ radianS0) * r0;
    float S1y = sin((PI / 2) + radianS0) * r0;
    float S1z = 9.4;

    // +2 pour le decalage de la pince
    
    y = sqrt( (x - S1x) * (x - S1x) + (y - S1y) * (y - S1y)) + 2;

    distance = 0;



    S1y = 0;



    int angleS1, angleS2, angleS3;
    float alpha,beta,gamma;

    for (float Dalpha = 130 ; Dalpha > 5 ; Dalpha -= 5) {

        //Calcule des angles

        float Dy = abs(y - S1y);
        float Dz = abs(z - S1z);
        float r = sqrt(Dy * Dy + Dz * Dz);

        float alpha1;
        if(z <= S1z){ alpha1 = asin(Dy / r);}
        if(z > S1z){ alpha1 = (PI / 2) + asin(Dz / r);}

        alpha = degreToRadian(Dalpha);

        float alpha2 = alpha + (PI / 2) - alpha1;

        float r4 = sqrt(r1 * r1 + r * r - 2 * r * r1 * cos(alpha2));
        float beta1 = acos((r1 * r1 + r4 * r4 - r * r) / (2 * r1 * r4));
        float beta2 = acos((r2 * r2 + r4 * r4 - r3 * r3) / (2 * r2 * r4));

        beta = beta1 + beta2;
        gamma = acos((r2 * r2 + r3 * r3 - r4 * r4) / (2 * r2 * r3));

        angleS1 =  radianToDegre(alpha);
        angleS2 =  radianToDegre(beta);
        angleS3 =  radianToDegre(gamma);



        float S3y;
        float r5;


        r5 = sqrt(r1*r1 + r2*r2 - 2 * r1 * r2 * cos(beta));
        
        float zeta;
        zeta = acos(((r1*r1+r5*r5 -  r2*r2)/(2*r1*r5)));



        S3y = cos(alpha - zeta) * r5;



        if(abs(S3y - y) < abs(distance - y)  && angleS2 > 10 && angleS2 < 200 && angleS3 > 10 && angleS3 < 200){

            distance = S3y;
            AS0 = angleS0;
            AS1 = angleS1;
            AS2 = angleS2;
            AS3 = angleS3;
        }

    }

    int* tab = new int[5];
    tab[0] = AS0;
    tab[1] = AS1;
    tab[2] = AS2;
    tab[3] = AS3;

    return tab;
}




