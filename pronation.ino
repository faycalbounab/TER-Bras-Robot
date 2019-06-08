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


//calcule la position en degré des Servos 0, 1, 2 et 3 selon les coordonnées x, y, z de la position d'arrivé du bras
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

    float radianS3 = PI/2;/*
    for (float i = 11*PI/20 ; i < PI; i += PI / 40){
      float tmpS1toS3 = sqrt(distance1*distance1 + distance2 * distance2 - 2 * distance1*distance2*cos(i));

        float tmpc1 = acos((distance2*distance2 + tmpS1toS3 * tmpS1toS3 - (distance1*distance1)) / (2 * tmpS1toS3*distance2));
      float tmpc2 = acos((distance3*distance3 + tmpS1toS3 * tmpS1toS3 - (S1toS4*S1toS4)) / (2 * tmpS1toS3*distance3));

      float tmpc = tmpc1 + tmpc2;
      if (radianS3 < tmpc) { radianS3 = tmpc;

      }

    }

    if (radianS3 < PI / 2) { radianS3 = 0;  }//si le mouvement n'est pas possible
    */

    float S2toS4 = sqrt(distance3*distance3 + distance2 * distance2 - 2 * distance2*distance3*cos(radianS3));

    float angleB2 = acos((distance2*distance2 + S2toS4 * S2toS4 - (distance3*distance3)) / (2 * S2toS4*distance2));

    float angleB1 = acos((distance1*distance1 + S2toS4 * S2toS4 - (S1toS4*S1toS4)) / (2 * S2toS4*distance1));

    float angleB = angleB1 + angleB2;

    float S1toS3 = sqrt(distance1*distance1 + distance2 * distance2 - 2 * distance1*distance2*cos(angleB));

    float angleA1 = acos((distance1*distance1 + S1toS3 * S1toS3 - (distance2*distance2)) / (2 * S1toS3*distance1));

    float angleA2 = acos((y - S1y) / S1toS4);


    float angleA3 = acos((S1toS4*S1toS4 + S1toS3 * S1toS3 - (distance3*distance3)) / (2 * S1toS3*S1toS4));
    float angleA = 0;
    if (z < S1z){
       angleA = angleA1 + angleA3 - angleA2;
    }
    else{
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





//calcule la position en degré des Servos 0, 1, 2 et 3 selon les coordonnées x, y, z de la position d'arrivé du bras
int* calculeAngleVariateur(int x, int y, int z){
  int AS0 = 0;
  int AS1 = 0;
  int AS2 = 0;
  int AS3 = 0;

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

    if(abs(90 - angleS3) < abs(90 - AS3)){
      AS0 = angleS0;
      AS1 = angleS1;
      AS2 = angleS2;
      AS3 = angleS3; 
    }

   

  }
   
  int* tab =new int[5];
  tab[0] = AS0;
  tab[1] = AS1;
  tab[2] = AS2;
  tab[3] = AS3;

  return tab; 
}


  int* calculeDesAnglesFINAL(int x, int y, int z, int appel) {

    //distance entre les Servos
    float distance1 = 10.4;
    float distance2 = 9.8;
    float distance3 = 14;

    float dist4=sqrt(x*x+y*y);
  
    //position du Servo1
    int S1y = 0;
    float S1z = 9.5;

    //Calcule des angles

    float radianS0 = acos(x / sqrt(x * x + y * y));
    int angleS0 = radianToDegre(radianS0);

    //pour l'instant cet angle est prÈdÈfini
    float radianS4 = PI / (2+appel*0.2);
    int angleS4 = radianToDegre(radianS4);

    float S3y = dist4 - cos(radianS4) * distance3;
    float S3z = z + sin(radianS4) * distance3;

    float S3toS1g = S1y - S3y;
    float S3toS1d = S1z - S3z;
    float S3toS1 = sqrt(S3toS1g*S3toS1g + S3toS1d * S3toS1d);
    float S1toS4g = dist4 - S1y;
    float S1toS4d = z - S1z;
    float S1toS4 = sqrt(S1toS4g*S1toS4g + S1toS4d * S1toS4d);

    float radianS2 = acos(((distance1*distance1 + distance2 * distance2 - S3toS1 * S3toS1) / (2 * distance1*distance2)));
    float radianTriangle1 = acos(((S3toS1*S3toS1 + distance2 * distance2 - distance1 * distance1) / (2 * S3toS1*distance2)));
    float radianTriangle2 = acos(((S3toS1*S3toS1 + distance3 * distance3 - S1toS4 * S1toS4) / (2 * S3toS1*distance3)));
    float radianS3 = radianTriangle1 + radianTriangle2;


    float angleA1 = acos((distance1*distance1 + S3toS1 * S3toS1 - (distance2*distance2)) / (2 * S3toS1*distance1));

    float angleA2 = acos((dist4 - S1y) / S1toS4);


    float angleA3 = acos((S1toS4*S1toS4 + S3toS1 * S3toS1 - (distance3*distance3)) / (2 * S3toS1*S1toS4));
    float radianS1 = 0;
    if (z < S1z)
    {
      radianS1 = angleA1 + angleA3 - angleA2;
    }
    else
    {
      radianS1 = angleA1 + angleA3 + angleA2;
    }

    int angleS3 = radianToDegre(radianS3);
    int angleS2 = radianToDegre(radianS2);
    int angleS1 = radianToDegre(radianS1);

    if(!angleS1 && !angleS2 && !angleS3)
    {
        return calculeDesAnglesFINAL(x,y,z,appel+1);
    }

    int* tab = new int[4];
    tab[0] = angleS0;
    tab[1] = angleS1;
    tab[2] = angleS2;
    tab[3] = angleS3;

    return tab;

  }
