/*
 ******************************************************************************
 * 
 * Copyright (c) 2019 Groupe : Berriri Mehdi, Bounab Fayçal, Djema Sofiane, Doglio Arthur
 * All rights reserved.
 * 
 * Ce projet s'inscrit dans le cadre d'un Travail d'Etude et de Recherche de Master 1 Informatique.
 *
 ******************************************************************************
 */


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//******************************************** Les variables globales ********************************************//

float r0 = 2; // distance sur le plan(x,y) entre le Servo0 et le Servo1
float r1 = 10.4; // distance sur le plan(y,z) entre le Servo1 et le Servo2
float r2 = 9.8; // distance sur le plan(y,z) entre le Servo2 et le Servo3
float r3 = 14; // distance sur le plan(y,z) entre le Servo3 et la prise de la pince
float S1z = 9.4; // hauteur du Servo 1 en centimètre


//******************************************** Les classes ********************************************//

class Servo {

  private : 
    int numServo; // port de la carte Arduino sur lequel est branché le Servo
    int mini; // valeur minumum du Servo
    int maxi; // valeur maximum du Servo
    float coeffDir; // coefficient directeur de la fonction calculMoveDegre
    int valeurPos; // valeur en position initiale
    int initAngle; // angle minimum du Servo
    int vitesse; // vitesse de rotation du Servo

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

      void setVitesse(int v){
        if(v >= 0 && v < 12){
          vitesse = v;
        }
      }
      
      //prend un angle en paramètre et calcul la valeur du déplacement du servo
      int calculMoveDegre(int angle){
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
};


class Plateau {
  private : 
    // L'echiquier est orienté pour que le bras joue les noir
    int echiquier[8][8]; // 1 = pion, 2 = tour, 3 = cavalier, 4 = fou, 5 = reine et roi
    int n; // nombre de pièce adverse prise

    public :
      Plateau(){
        resetPlateau();
      }

      int getEchiquier(int x, int y){ return echiquier[x][y]; }
      void setEchiquier(int x, int y, int val){ echiquier[x][y] = val; }
      int getN(){ return n; }
      void setN(int x){ n = x; }

      void resetPlateau(){
        n = 0;
        for(int i = 0; i < 8; i++){
          echiquier[1][i] = 1;
          echiquier[6][i] = 1;
        }
        echiquier[0][0] = 2;
        echiquier[0][7] = 2;
        echiquier[7][0] = 2;
        echiquier[7][7] = 2;
        
        echiquier[0][1] = 3;
        echiquier[0][6] = 3;
        echiquier[7][1] = 3;
        echiquier[7][6] = 3;

        echiquier[0][2] = 4;
        echiquier[0][5] = 4;
        echiquier[7][2] = 4;
        echiquier[7][5] = 4;

        echiquier[0][3] = 5;
        echiquier[0][4] = 5;
        echiquier[7][3] = 5;
        echiquier[7][4] = 5;
     }
};

//******************************************** Les méthodes de calculs ********************************************//

// indique la position que doit prendre le Servo5 (la pince) pour s'ouvrir selon la taille cm passée en paramètre
int cmTValeurServo5(float cm){
  if(cm >= 0.5 && cm < 2) return 10*(cm-0.5) + 190;
  if(cm >= 2 && cm <= 10) return 10*(cm-2) + 215;
  return 220;
}

//converti des radian en degré
int radianToDegre(float radian){
  return radian /PI*180 ;
}

//converti des degrés en radian
float degreToRadian(float degre){
    return degre * PI / 180;
}

// prend en paramètre les coordonnées (x, y, z) de la pièce à prendre et un tableau ou l'ont sauvegarde les angles de rotation
void calculAnglesArticulation(float x, float y, float z, int* tab){
  
  //***************** les variables *****************//
  
  int AS0 = 0, AS1 = 0,  AS2 = 0, AS3 = 0; // meilleurs angles en degré
  int angleS0, angleS1, angleS2, angleS3; // angles en degré
  float r, r4, r5, distance, r6, r7, Dy, Dz; // longueurs
  float omega, omega1, omega2, alpha, alpha1, alpha2, beta, beta1, beta2, gamma, zeta; // angles en radian
  float S1x, S1y, S3y; //coordonnées
  

  //***************** calcul de l'orientation *****************//

  //Sur un plan (x, y)
  
  r6 = sqrt(x * x + y * y);
  r7 = sqrt(r6 * r6 - r0 * r0);
  omega1 = acos(x / r6);
  omega2 = (PI / 2) - acos(r0 / r6);
  omega = omega1 - (omega2 / 2);
  
  angleS0 = radianToDegre(omega);

  // On actualise les valeurs pour les calculs dans un plan (y, z)
  S1x = cos((PI / 2)+ omega) * r0; // position du Servo1 en x
  S1y = sin((PI / 2) + omega) * r0; // position du Servo1 en y
  y = sqrt( (x - S1x) * (x - S1x) + (y - S1y) * (y - S1y)) + 2; // +2 pour le decalage de la pince
  distance = 0;
  S1y = 0;

  for (float Dalpha = 130 ; Dalpha > 5 ; Dalpha -= 5) {
    
    //***************** calcul de l'articulation *****************//
    
    Dy = abs(y - S1y);
    Dz = abs(z - S1z);
    r = sqrt(Dy * Dy + Dz * Dz);

    if(z <= S1z){ alpha1 = asin(Dy / r);}
    if(z > S1z){ alpha1 = (PI / 2) + asin(Dz / r);}
    alpha = degreToRadian(Dalpha);
    alpha2 = alpha + (PI / 2) - alpha1;

    r4 = sqrt(r1 * r1 + r * r - 2 * r * r1 * cos(alpha2));
    beta1 = acos((r1 * r1 + r4 * r4 - r * r) / (2 * r1 * r4));
    beta2 = acos((r2 * r2 + r4 * r4 - r3 * r3) / (2 * r2 * r4));
    beta = beta1 + beta2;
    gamma = acos((r2 * r2 + r3 * r3 - r4 * r4) / (2 * r2 * r3));

    angleS1 =  radianToDegre(alpha);
    angleS2 =  radianToDegre(beta);
    angleS3 =  radianToDegre(gamma);


    //***************** choix de la combinaison d'angle pour l'articulation *****************//
    
    r5 = sqrt(r1*r1 + r2*r2 - 2 * r1 * r2 * cos(beta));
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

  //***************** affectation des valeurs choisies *****************//
  
  tab[0] = AS0;
  tab[1] = AS1;
  tab[2] = AS2;
  tab[3] = AS3;
}
