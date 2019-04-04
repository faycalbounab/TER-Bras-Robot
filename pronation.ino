#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  210 
#define SERVOMAX  400 

#define distance1-2 10,4
#define distance2-3 9,8
#define distance3-5 14
uint8_t servonum = 5;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
class Servo {

  private : 
    int numServo;
    int mini;
    int maxi;
    float posX;
    float posY;
    float posZ;
    float coeffDir;

    int valeurPos = 0;

    public:
      Servo(int numServo, int mini,int maxi,float posX,float posY,float posZ,float coeffDir){
        this->mini = mini;
        this->maxi = maxi;
        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;
        this->coeffDir = coeffDir;
      }
      
      float getposX(){
        return posX;
      }

      float getposY(){
        return posY;
      }

      float getposZ(){
        return posZ;
      }

      //prend un angle en parametre et calcule la valeur du déplacement du servo
      int calculeMoveDegre(int angle){
        return coeffDir * angle + mini;
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
        if(x > mini && x < maxi){
          return true;
        }
        return false;
      }
};
